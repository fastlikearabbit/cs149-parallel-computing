## Part 1: CUDA Warm-Up 1: SAXPY

Timing with memory movement: 
```
---------------------------------------------------------
Found 1 CUDA devices
Device 0: NVIDIA T4G
   SMs:        40
   Global mem: 14918 MB
   CUDA Cap:   7.5
---------------------------------------------------------
Running 3 timing tests:
Effective BW by CUDA saxpy: 250.151 ms		[4.468 GB/s]
Effective BW by CUDA saxpy: 269.274 ms		[4.150 GB/s]
Effective BW by CUDA saxpy: 269.270 ms		[4.150 GB/s]
```

Without memory movement:
```
---------------------------------------------------------
Found 1 CUDA devices
Device 0: NVIDIA T4G
   SMs:        40
   Global mem: 14918 MB
   CUDA Cap:   7.5
---------------------------------------------------------
Running 3 timing tests:
Effective BW by CUDA saxpy: 4.928 ms		[226.773 GB/s]
Effective BW by CUDA saxpy: 4.859 ms		[230.010 GB/s]
Effective BW by CUDA saxpy: 4.861 ms		[229.902 GB/s]
```

(1) I got 3.095 ms for the ispc and 1.756 ms for the task ispc, so the cpu version was more performant. But this one
has more GB/s.

(2) The memory bandwidth of AWS is what sets the speed of those transfers so low.

## Part 2: CUDA Warm-Up 2: Parallel Prefix-Sum
```
-------------------------
Scan Score Table:
-------------------------
-------------------------------------------------------------------------
| Element Count   | Ref Time        | Student Time    | Score           |
-------------------------------------------------------------------------
| 1000000         | 1.492           | 0.475           | 1.25            |
| 10000000        | 9.278           | 7.854           | 1.25            |
| 20000000        | 17.719          | 15.629          | 1.25            |
| 40000000        | 35.153          | 31.185          | 1.25            |
-------------------------------------------------------------------------
|                                   | Total score:    | 5.0/5.0         |
-------------------------------------------------------------------------
```

```
-------------------------
Find_repeats Score Table:
-------------------------
-------------------------------------------------------------------------
| Element Count   | Ref Time        | Student Time    | Score           |
-------------------------------------------------------------------------
| 1000000         | 1.05            | 0.755           | 1.25            |
| 10000000        | 12.029          | 10.159          | 1.25            |
| 20000000        | 22.457          | 19.139          | 1.25            |
| 40000000        | 42.436          | 37.04           | 1.25            |
-------------------------------------------------------------------------
|                                   | Total score:    | 5.0/5.0         |
-------------------------------------------------------------------------
```

## Part 3: A Simple Circle Renderer

```
ubuntu@ip-172-31-2-50:~/asst3/render$ ./checker.py

Running scene: rgb...
[rgb] Correctness passed!
[rgb] Student times:  [0.4451, 0.4436, 0.4506]
[rgb] Reference times:  [0.2662, 0.2634, 0.2647]

Running scene: rand10k...
[rand10k] Correctness passed!
[rand10k] Student times:  [3.0629, 3.0628, 3.0567]
[rand10k] Reference times:  [2.7426, 2.745, 2.7473]

Running scene: rand100k...
[rand100k] Correctness passed!
[rand100k] Student times:  [31.0364, 31.2336, 30.8379]
[rand100k] Reference times:  [26.1825, 26.1615, 26.3371]

Running scene: pattern...
[pattern] Correctness passed!
[pattern] Student times:  [0.4762, 0.4643, 0.4676]
[pattern] Reference times:  [0.3577, 0.358, 0.3585]

Running scene: snowsingle...
[snowsingle] Correctness passed!
[snowsingle] Student times:  [1.4859, 1.4721, 1.4857]
[snowsingle] Reference times:  [16.1391, 16.1237, 16.1781]

Running scene: biglittle...
[biglittle] Correctness passed!
[biglittle] Student times:  [34.6562, 34.6177, 34.5002]
[biglittle] Reference times:  [15.08, 14.9866, 15.0045]

Running scene: rand1M...
[rand1M] Correctness passed!
[rand1M] Student times:  [67.0632, 67.3154, 67.457]
[rand1M] Reference times:  [189.4217, 189.9452, 189.5129]

Running scene: micro2M...
[micro2M] Correctness passed!
[micro2M] Student times:  [54.7151, 54.6113, 54.7198]
[micro2M] Reference times:  [358.7095, 359.0803, 359.2549]
------------
Score table:
------------
--------------------------------------------------------------------------
| Scene Name      | Ref Time (T_ref) | Your Time (T)   | Score           |
--------------------------------------------------------------------------
| rgb             | 0.2634           | 0.4436          | 7               |
| rand10k         | 2.7426           | 3.0567          | 9               |
| rand100k        | 26.1615          | 30.8379         | 9               |
| pattern         | 0.3577           | 0.4643          | 8               |
| snowsingle      | 16.1237          | 1.4721          | 9               |
| biglittle       | 14.9866          | 34.5002         | 6               |
| rand1M          | 189.4217         | 67.0632         | 9               |
| micro2M         | 358.7095         | 54.6113         | 9               |
--------------------------------------------------------------------------
|                                    | Total score:    | 66/72           |
--------------------------------------------------------------------------
```