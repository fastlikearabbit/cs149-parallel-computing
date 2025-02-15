#include "tasksys.h"
#include "itasksys.h"
#include <atomic>
#include <mutex>
#include <thread>


IRunnable::~IRunnable() {}

ITaskSystem::ITaskSystem(int num_threads) {}
ITaskSystem::~ITaskSystem() {}

/*
 * ================================================================
 * Serial task system implementation
 * ================================================================
 */

const char* TaskSystemSerial::name() {
    return "Serial";
}

TaskSystemSerial::TaskSystemSerial(int num_threads): ITaskSystem(num_threads) {
}

TaskSystemSerial::~TaskSystemSerial() {}

void TaskSystemSerial::run(IRunnable* runnable, int num_total_tasks) {
    for (int i = 0; i < num_total_tasks; i++) {
        runnable->runTask(i, num_total_tasks);
    }
}

TaskID TaskSystemSerial::runAsyncWithDeps(IRunnable* runnable, int num_total_tasks,
                                          const std::vector<TaskID>& deps) {
    // You do not need to implement this method.
    return 0;
}

void TaskSystemSerial::sync() {
    // You do not need to implement this method.
    return;
}

/*
 * ================================================================
 * Parallel Task System Implementation
 * ================================================================
 */

const char* TaskSystemParallelSpawn::name() {
    return "Parallel + Always Spawn";
}

TaskSystemParallelSpawn::TaskSystemParallelSpawn(int num_threads): ITaskSystem(num_threads), num_threads(num_threads) {}

TaskSystemParallelSpawn::~TaskSystemParallelSpawn() {}

void TaskSystemParallelSpawn::run(IRunnable* runnable, int num_total_tasks) {
    std::atomic<int> task_id{0};

    for (int tid = 0; tid < num_threads; tid++) {
        workers.emplace_back(std::thread([runnable, num_total_tasks, &task_id] {
            while (true) {
                int current_task;
                {
                    current_task = task_id.fetch_add(1);

                    if (current_task >= num_total_tasks) {
                        return;
                    }
                    
                    runnable->runTask(current_task, num_total_tasks);
                }     
            }
        }));
    }

    for (auto& worker: workers) {
        worker.join();
    }

    workers.clear();
}

TaskID TaskSystemParallelSpawn::runAsyncWithDeps(IRunnable* runnable, int num_total_tasks,
                                                 const std::vector<TaskID>& deps) {
    // You do not need to implement this method.
    return 0;
}

void TaskSystemParallelSpawn::sync() {
    // You do not need to implement this method.
    return;
}

/*
 * ================================================================
 * Parallel Thread Pool Spinning Task System Implementation
 * ================================================================
 */

const char* TaskSystemParallelThreadPoolSpinning::name() {
    return "Parallel + Thread Pool + Spin";
}

TaskSystemParallelThreadPoolSpinning::TaskSystemParallelThreadPoolSpinning(int num_threads): ITaskSystem(num_threads) {
    for (int tid = 0; tid < num_threads; tid++) {
        workers.emplace_back(std::thread([this] {
            while (true) {
                {
                    std::unique_lock<std::mutex> lock(mux);

                    if (done.test()) return;

                    const int current_task = next_task.fetch_add(1);
                    if (current_task >= total_tasks.load()) {
                        next_task.fetch_sub(1); 
                        continue;
                    }
                    lock.unlock();

                    IRunnable* local_runnable = runnable.load();
                    if (local_runnable) {
                        local_runnable->runTask(current_task, total_tasks.load());
                    }

                    if (completed_tasks.fetch_add(1) + 1 == total_tasks.load()) {
                        done_bulk.test_and_set();
                    }
                }     
            }
        }));
    }    
}

// Destructor
TaskSystemParallelThreadPoolSpinning::~TaskSystemParallelThreadPoolSpinning() {
    done.test_and_set();

    for (auto& worker : workers) {
        worker.join();
    }
}

// Run Method
void TaskSystemParallelThreadPoolSpinning::run(IRunnable* runnable, int num_total_tasks) {
    std::unique_lock<std::mutex> guard(mux);
    this->next_task.store(0);
    this->completed_tasks.store(0);
    this->total_tasks.store(num_total_tasks);
    this->runnable.store(runnable);
    this->done_bulk.clear();

    guard.unlock();
    while (!this->done_bulk.test()) {
        
    }
    
    guard.lock();
    this->runnable.store(nullptr);
    this->total_tasks.store(-1);
}

TaskID TaskSystemParallelThreadPoolSpinning::runAsyncWithDeps(IRunnable* runnable, int num_total_tasks,
                                                              const std::vector<TaskID>& deps) {
    // You do not need to implement this method.
    return 0;
}

void TaskSystemParallelThreadPoolSpinning::sync() {
    // You do not need to implement this method.
    return;
}

/*
 * ================================================================
 * Parallel Thread Pool Sleeping Task System Implementation
 * ================================================================
 */

const char* TaskSystemParallelThreadPoolSleeping::name() {
    return "Parallel + Thread Pool + Sleep";
}

TaskSystemParallelThreadPoolSleeping::TaskSystemParallelThreadPoolSleeping(int num_threads) : ITaskSystem(num_threads) {
    for (int tid = 0; tid < num_threads; tid++) {
        workers.emplace_back([this] {
            while (true) {
                std::unique_lock<std::mutex> lock(mux);
                
                cv.wait(lock, [this] {
                    return done || (next_task.load() < total_tasks.load());
                });

                if (done) return;
                
                const int current_task = next_task.fetch_add(1);
                if (current_task >= total_tasks.load()) {
                    next_task.fetch_sub(1); 
                    cv.notify_all();
                    continue;
                }
                lock.unlock();

                IRunnable* local_runnable = runnable.load();
                if (local_runnable) {
                    local_runnable->runTask(current_task, total_tasks.load());
                }

                if (completed_tasks.fetch_add(1) + 1 == total_tasks.load()) {
                    std::unique_lock<std::mutex> lock(mux);
                    cv.notify_all();
                }
            }
        });
    }
}

    TaskSystemParallelThreadPoolSleeping::~TaskSystemParallelThreadPoolSleeping() {
        {
            std::lock_guard<std::mutex> lock(mux);
            done = true;
            cv.notify_all();
        }
        for (auto& worker : workers) {
            worker.join();
        }
    }

void TaskSystemParallelThreadPoolSleeping::run(IRunnable* runnable_ptr, int num_total_tasks) {
    std::unique_lock<std::mutex> lock(mux);
    runnable.store(runnable_ptr);
    total_tasks.store(num_total_tasks);
    next_task.store(0);
    completed_tasks.store(0);
    lock.unlock();

    cv.notify_all();

    lock.lock();
    cv.wait(lock, [this] {
        return (completed_tasks.load() >= total_tasks.load()) || done;
    });
    runnable.store(nullptr);
    total_tasks.store(-1);
}


TaskID TaskSystemParallelThreadPoolSleeping::runAsyncWithDeps(IRunnable* runnable, int num_total_tasks,
                                                    const std::vector<TaskID>& deps) {


    //
    // TODO: CS149 students will implement this method in Part B.
    //

    return 0;
}

void TaskSystemParallelThreadPoolSleeping::sync() {

    //
    // TODO: CS149 students will modify the implementation of this method in Part B.
    //

    return;
}
