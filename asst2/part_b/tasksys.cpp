#include "tasksys.h"
#include "itasksys.h"
#include <cassert>
#include <cstddef>
#include <mutex>
#include <thread>
#include <vector>

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
    for (int i = 0; i < num_total_tasks; i++) {
        runnable->runTask(i, num_total_tasks);
    }

    return 0;
}

void TaskSystemSerial::sync() {
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

TaskSystemParallelSpawn::TaskSystemParallelSpawn(int num_threads): ITaskSystem(num_threads) {
    // NOTE: CS149 students are not expected to implement TaskSystemParallelSpawn in Part B.
}

TaskSystemParallelSpawn::~TaskSystemParallelSpawn() {}

void TaskSystemParallelSpawn::run(IRunnable* runnable, int num_total_tasks) {
    // NOTE: CS149 students are not expected to implement TaskSystemParallelSpawn in Part B.
    for (int i = 0; i < num_total_tasks; i++) {
        runnable->runTask(i, num_total_tasks);
    }
}

TaskID TaskSystemParallelSpawn::runAsyncWithDeps(IRunnable* runnable, int num_total_tasks,
                                                 const std::vector<TaskID>& deps) {
    // NOTE: CS149 students are not expected to implement TaskSystemParallelSpawn in Part B.
    for (int i = 0; i < num_total_tasks; i++) {
        runnable->runTask(i, num_total_tasks);
    }

    return 0;
}

void TaskSystemParallelSpawn::sync() {
    // NOTE: CS149 students are not expected to implement TaskSystemParallelSpawn in Part B.
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
    // NOTE: CS149 students are not expected to implement TaskSystemParallelThreadPoolSpinning in Part B.
}

TaskSystemParallelThreadPoolSpinning::~TaskSystemParallelThreadPoolSpinning() {}

void TaskSystemParallelThreadPoolSpinning::run(IRunnable* runnable, int num_total_tasks) {
    // NOTE: CS149 students are not expected to implement TaskSystemParallelThreadPoolSpinning in Part B.
    for (int i = 0; i < num_total_tasks; i++) {
        runnable->runTask(i, num_total_tasks);
    }
}

TaskID TaskSystemParallelThreadPoolSpinning::runAsyncWithDeps(IRunnable* runnable, int num_total_tasks,
                                                              const std::vector<TaskID>& deps) {
    // NOTE: CS149 students are not expected to implement TaskSystemParallelThreadPoolSpinning in Part B.
    for (int i = 0; i < num_total_tasks; i++) {
        runnable->runTask(i, num_total_tasks);
    }

    return 0;
}

void TaskSystemParallelThreadPoolSpinning::sync() {
    // NOTE: CS149 students are not expected to implement TaskSystemParallelThreadPoolSpinning in Part B.
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

TaskSystemParallelThreadPoolSleeping::TaskSystemParallelThreadPoolSleeping(int num_threads): ITaskSystem(num_threads) {
    for (int tid = 0; tid < num_threads; tid++) {
        workers.emplace_back(std::thread([this] {
            while (true) {
                std::unique_lock<std::mutex> lock(mux);
                cv.wait(lock, [this] {
                    return done|| current_exec_bulk.next_task.load() < current_exec_bulk.total_tasks.load();
                });

                if (done) return;
                
                const int current_task = current_exec_bulk.next_task.fetch_add(1);
                if (current_task >= current_exec_bulk.total_tasks.load()) {
                    current_exec_bulk.next_task.fetch_sub(1); 
                    cv.notify_all();
                    continue;
                }
                lock.unlock();

                IRunnable* local_runnable = current_exec_bulk.runnable.load();
                if (local_runnable) {
                    local_runnable->runTask(current_task, current_exec_bulk.total_tasks.load());
                }

                if (current_exec_bulk.completed_tasks.fetch_add(1) + 1 == current_exec_bulk.total_tasks.load()) {
                    std::unique_lock<std::mutex> lock(mux);
                    cv.notify_all();
                }
            }
        }));
    }
}

TaskSystemParallelThreadPoolSleeping::~TaskSystemParallelThreadPoolSleeping() {
   {
    std::unique_lock<std::mutex> lock(mux);
    done = true;
    cv.notify_all();
   }

   for (auto& worker: workers) {
        worker.join();
   }
}

void TaskSystemParallelThreadPoolSleeping::run(IRunnable* runnable, int num_total_tasks) {
    std::vector<TaskID> nodeps;
    this->runAsyncWithDeps(runnable, num_total_tasks, nodeps);
    this->sync();
}

// returns consecutive task ids, starting from 0
TaskID TaskSystemParallelThreadPoolSleeping::runAsyncWithDeps(IRunnable* runnable, int num_total_tasks,
                                                    const std::vector<TaskID>& deps) {
    dependency_graph.push_back(deps);
    task_info.push_back({runnable, num_total_tasks});

    assert(dependency_graph.size() == next_bulk_task_id + 1 && task_info.size() == next_bulk_task_id + 1);

    return next_bulk_task_id++;
}


std::vector<int> topologicalSort(const std::vector<std::vector<int>>& dependency_graph);

void TaskSystemParallelThreadPoolSleeping::sync() {
    std::vector<int> task_topological_order = topologicalSort(dependency_graph);

    for (int bulk_id : task_topological_order) {
        std::unique_lock<std::mutex> lock(mux);
        auto [runnable, count] = task_info[bulk_id];
        current_exec_bulk.runnable.store(runnable);
        current_exec_bulk.total_tasks.store(count);
        current_exec_bulk.next_task = 0;
        current_exec_bulk.completed_tasks = 0;

        cv.notify_all();

        cv.wait(lock, [this] {
            return done || (current_exec_bulk.completed_tasks.load() >= current_exec_bulk.total_tasks.load());
        });
    }

    // cleanup
    next_bulk_task_id = 0;
    dependency_graph.clear();
    task_info.clear();
}

void dfs(int node, const std::vector<std::vector<int>>& adjacency_list, 
         std::vector<bool>& visited, std::vector<int>& topological_order) {
    visited[node] = true;
    
    for (int neighbor : adjacency_list[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, adjacency_list, visited, topological_order);
        }
    }
    
    topological_order.push_back(node);
}

std::vector<int> topologicalSort(const std::vector<std::vector<int>>& dependency_graph) {
    std::vector<std::vector<int>> adjacency_list(dependency_graph.size());

    for (int node = 0; node < dependency_graph.size(); node++) {
        std::vector<int> deps = dependency_graph[node];
        for (const auto& dep : deps) {
            adjacency_list[dep].push_back(node);
        }
    }

    size_t num_tasks = adjacency_list.size();
    std::vector<bool> visited(num_tasks, false);
    std::vector<int> topological_order;
    
    for (int i = 0; i < num_tasks; i++) {
        if (!visited[i]) {
            dfs(i, adjacency_list, visited, topological_order);
        }
    }
    
    reverse(topological_order.begin(), topological_order.end());
    
    return topological_order;
}
