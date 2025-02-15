## Part (a):

Output:

```
❯ python3 ../tests/run_test_harness.py
runtasks_ref
Darwin arm64
================================================================================
Running task system grading harness... (11 total tests)
  - Detected CPU with 10 execution contexts
  - Task system configured to use at most 10 threads
================================================================================
================================================================================
Executing test: super_super_light...
Reference binary: ./runtasks_ref_osx_arm
Results for: super_super_light
                                        STUDENT   REFERENCE   PERF?
[Serial]                                4.555     4.56        1.00  (OK)
[Parallel + Always Spawn]               45.602    46.834      0.97  (OK)
[Parallel + Thread Pool + Spin]         82.927    179.364     0.46  (OK)
[Parallel + Thread Pool + Sleep]        23.201    19.812      1.17  (OK)
================================================================================
Executing test: super_light...
Reference binary: ./runtasks_ref_osx_arm
Results for: super_light
                                        STUDENT   REFERENCE   PERF?
[Serial]                                22.521    32.713      0.69  (OK)
[Parallel + Always Spawn]               48.938    50.285      0.97  (OK)
[Parallel + Thread Pool + Spin]         103.812   276.526     0.38  (OK)
[Parallel + Thread Pool + Sleep]        31.904    35.504      0.90  (OK)
================================================================================
Executing test: ping_pong_equal...
Reference binary: ./runtasks_ref_osx_arm
Results for: ping_pong_equal
                                        STUDENT   REFERENCE   PERF?
[Serial]                                357.922   521.248     0.69  (OK)
[Parallel + Always Spawn]               98.327    114.642     0.86  (OK)
[Parallel + Thread Pool + Spin]         226.378   341.996     0.66  (OK)
[Parallel + Thread Pool + Sleep]        74.369    89.922      0.83  (OK)
================================================================================
Executing test: ping_pong_unequal...
Reference binary: ./runtasks_ref_osx_arm
Results for: ping_pong_unequal
                                        STUDENT   REFERENCE   PERF?
[Serial]                                910.588   729.368     1.25  (NOT OK)
[Parallel + Always Spawn]               164.913   143.484     1.15  (OK)
[Parallel + Thread Pool + Spin]         246.565   675.088     0.37  (OK)
[Parallel + Thread Pool + Sleep]        144.896   121.232     1.20  (OK)
================================================================================
Executing test: recursive_fibonacci...
Reference binary: ./runtasks_ref_osx_arm
Results for: recursive_fibonacci
                                        STUDENT   REFERENCE   PERF?
[Serial]                                1684.115  1683.943    1.00  (OK)
[Parallel + Always Spawn]               205.497   205.293     1.00  (OK)
[Parallel + Thread Pool + Spin]         236.358   222.466     1.06  (OK)
[Parallel + Thread Pool + Sleep]        204.113   204.361     1.00  (OK)
================================================================================
Executing test: math_operations_in_tight_for_loop...
Reference binary: ./runtasks_ref_osx_arm
Results for: math_operations_in_tight_for_loop
                                        STUDENT   REFERENCE   PERF?
[Serial]                                311.569   309.803     1.01  (OK)
[Parallel + Always Spawn]               260.568   262.45      0.99  (OK)
[Parallel + Thread Pool + Spin]         702.999   1916.749    0.37  (OK)
[Parallel + Thread Pool + Sleep]        142.716   140.966     1.01  (OK)
================================================================================
Executing test: math_operations_in_tight_for_loop_fewer_tasks...
Reference binary: ./runtasks_ref_osx_arm
Results for: math_operations_in_tight_for_loop_fewer_tasks
                                        STUDENT   REFERENCE   PERF?
[Serial]                                311.48    309.76      1.01  (OK)
[Parallel + Always Spawn]               256.458   263.723     0.97  (OK)
[Parallel + Thread Pool + Spin]         967.463   1749.051    0.55  (OK)
[Parallel + Thread Pool + Sleep]        152.663   147.086     1.04  (OK)
================================================================================
Executing test: math_operations_in_tight_for_loop_fan_in...
Reference binary: ./runtasks_ref_osx_arm
Results for: math_operations_in_tight_for_loop_fan_in
                                        STUDENT   REFERENCE   PERF?
[Serial]                                162.677   159.638     1.02  (OK)
[Parallel + Always Spawn]               47.816    50.905      0.94  (OK)
[Parallel + Thread Pool + Spin]         97.208    242.412     0.40  (OK)
[Parallel + Thread Pool + Sleep]        38.013    35.078      1.08  (OK)
================================================================================
Executing test: math_operations_in_tight_for_loop_reduction_tree...
Reference binary: ./runtasks_ref_osx_arm
Results for: math_operations_in_tight_for_loop_reduction_tree
                                        STUDENT   REFERENCE   PERF?
[Serial]                                161.597   161.891     1.00  (OK)
[Parallel + Always Spawn]               28.053    28.131      1.00  (OK)
[Parallel + Thread Pool + Spin]         31.67     46.376      0.68  (OK)
[Parallel + Thread Pool + Sleep]        24.664    23.627      1.04  (OK)
================================================================================
Executing test: spin_between_run_calls...
Reference binary: ./runtasks_ref_osx_arm
Results for: spin_between_run_calls
                                        STUDENT   REFERENCE   PERF?
[Serial]                                598.204   598.343     1.00  (OK)
[Parallel + Always Spawn]               308.367   308.28      1.00  (OK)
[Parallel + Thread Pool + Spin]         318.173   318.213     1.00  (OK)
[Parallel + Thread Pool + Sleep]        307.792   307.957     1.00  (OK)
================================================================================
Executing test: mandelbrot_chunked...
Reference binary: ./runtasks_ref_osx_arm
Results for: mandelbrot_chunked
                                        STUDENT   REFERENCE   PERF?
[Serial]                                407.617   412.819     0.99  (OK)
[Parallel + Always Spawn]               47.816    48.537      0.99  (OK)
[Parallel + Thread Pool + Spin]         49.758    49.184      1.01  (OK)
[Parallel + Thread Pool + Sleep]        47.691    48.449      0.98  (OK)
================================================================================
Overall performance results
[Serial]                                : Perf did not pass all tests
[Parallel + Always Spawn]               : All passed Perf
[Parallel + Thread Pool + Spin]         : All passed Perf
[Parallel + Thread Pool + Sleep]        : All passed Perf
```


## Part (b):

```
❯ python3 ../tests/run_test_harness.py
runtasks_ref
Darwin arm64
================================================================================
Running task system grading harness... (11 total tests)
  - Detected CPU with 10 execution contexts
  - Task system configured to use at most 10 threads
================================================================================
================================================================================
Executing test: super_super_light...
Reference binary: ./runtasks_ref_osx_arm
Results for: super_super_light
                                        STUDENT   REFERENCE   PERF?
[Serial]                                4.57      4.571       1.00  (OK)
[Parallel + Always Spawn]               4.567     46.272      0.10  (OK)
[Parallel + Thread Pool + Spin]         4.566     114.001     0.04  (OK)
[Parallel + Thread Pool + Sleep]        28.507    20.935      1.36  (NOT OK)
================================================================================
Executing test: super_light...
Reference binary: ./runtasks_ref_osx_arm
Results for: super_light
                                        STUDENT   REFERENCE   PERF?
[Serial]                                22.514    32.667      0.69  (OK)
[Parallel + Always Spawn]               22.537    52.385      0.43  (OK)
[Parallel + Thread Pool + Spin]         22.513    146.668     0.15  (OK)
[Parallel + Thread Pool + Sleep]        35.329    36.72       0.96  (OK)
================================================================================
Executing test: ping_pong_equal...
Reference binary: ./runtasks_ref_osx_arm
Results for: ping_pong_equal
                                        STUDENT   REFERENCE   PERF?
[Serial]                                358.089   521.479     0.69  (OK)
[Parallel + Always Spawn]               361.727   119.329     3.03  (NOT OK)
[Parallel + Thread Pool + Spin]         358.021   288.137     1.24  (NOT OK)
[Parallel + Thread Pool + Sleep]        74.581    92.382      0.81  (OK)
================================================================================
Executing test: ping_pong_unequal...
Reference binary: ./runtasks_ref_osx_arm
Results for: ping_pong_unequal
                                        STUDENT   REFERENCE   PERF?
[Serial]                                882.162   730.442     1.21  (NOT OK)
[Parallel + Always Spawn]               881.869   147.104     5.99  (NOT OK)
[Parallel + Thread Pool + Spin]         881.756   398.036     2.22  (NOT OK)
[Parallel + Thread Pool + Sleep]        147.791   120.241     1.23  (NOT OK)
================================================================================
Executing test: recursive_fibonacci...
Reference binary: ./runtasks_ref_osx_arm
Results for: recursive_fibonacci
                                        STUDENT   REFERENCE   PERF?
[Serial]                                1684.901  1688.304    1.00  (OK)
[Parallel + Always Spawn]               1684.902  205.857     8.18  (NOT OK)
[Parallel + Thread Pool + Spin]         1685.637  234.745     7.18  (NOT OK)
[Parallel + Thread Pool + Sleep]        205.157   205.141     1.00  (OK)
================================================================================
Executing test: math_operations_in_tight_for_loop...
Reference binary: ./runtasks_ref_osx_arm
Results for: math_operations_in_tight_for_loop
                                        STUDENT   REFERENCE   PERF?
[Serial]                                314.211   310.285     1.01  (OK)
[Parallel + Always Spawn]               315.822   265.905     1.19  (OK)
[Parallel + Thread Pool + Spin]         312.159   872.532     0.36  (OK)
[Parallel + Thread Pool + Sleep]        162.952   142.397     1.14  (OK)
================================================================================
Executing test: math_operations_in_tight_for_loop_fewer_tasks...
Reference binary: ./runtasks_ref_osx_arm
Results for: math_operations_in_tight_for_loop_fewer_tasks
                                        STUDENT   REFERENCE   PERF?
[Serial]                                317.082   312.934     1.01  (OK)
[Parallel + Always Spawn]               315.962   260.338     1.21  (NOT OK)
[Parallel + Thread Pool + Spin]         315.849   849.359     0.37  (OK)
[Parallel + Thread Pool + Sleep]        156.452   146.374     1.07  (OK)
================================================================================
Executing test: math_operations_in_tight_for_loop_fan_in...
Reference binary: ./runtasks_ref_osx_arm
Results for: math_operations_in_tight_for_loop_fan_in
                                        STUDENT   REFERENCE   PERF?
[Serial]                                162.963   161.895     1.01  (OK)
[Parallel + Always Spawn]               163.162   49.301      3.31  (NOT OK)
[Parallel + Thread Pool + Spin]         163.053   135.584     1.20  (NOT OK)
[Parallel + Thread Pool + Sleep]        38.203    37.379      1.02  (OK)
================================================================================
Executing test: math_operations_in_tight_for_loop_reduction_tree...
Reference binary: ./runtasks_ref_osx_arm
Results for: math_operations_in_tight_for_loop_reduction_tree
                                        STUDENT   REFERENCE   PERF?
[Serial]                                162.859   162.18      1.00  (OK)
[Parallel + Always Spawn]               162.469   28.78       5.65  (NOT OK)
[Parallel + Thread Pool + Spin]         162.595   43.395      3.75  (NOT OK)
[Parallel + Thread Pool + Sleep]        24.971    23.796      1.05  (OK)
================================================================================
Executing test: spin_between_run_calls...
Reference binary: ./runtasks_ref_osx_arm
Results for: spin_between_run_calls
                                        STUDENT   REFERENCE   PERF?
[Serial]                                598.751   599.121     1.00  (OK)
[Parallel + Always Spawn]               598.83    308.811     1.94  (NOT OK)
[Parallel + Thread Pool + Spin]         599.478   322.702     1.86  (NOT OK)
[Parallel + Thread Pool + Sleep]        308.029   308.25      1.00  (OK)
================================================================================
Executing test: mandelbrot_chunked...
Reference binary: ./runtasks_ref_osx_arm
Results for: mandelbrot_chunked
                                        STUDENT   REFERENCE   PERF?
[Serial]                                408.398   414.175     0.99  (OK)
[Parallel + Always Spawn]               407.905   49.057      8.31  (NOT OK)
[Parallel + Thread Pool + Spin]         409.278   50.003      8.19  (NOT OK)
[Parallel + Thread Pool + Sleep]        47.868    48.547      0.99  (OK)
================================================================================
Overall performance results
[Serial]                                : Perf did not pass all tests
[Parallel + Always Spawn]               : Perf did not pass all tests
[Parallel + Thread Pool + Spin]         : Perf did not pass all tests
[Parallel + Thread Pool + Sleep]        : Perf did not pass all tests
```