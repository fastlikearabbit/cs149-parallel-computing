```
ubuntu@ip-172-31-35-19:~/biggraphs-ec/bfs$ ./bfs_grader ../all_graphs/
Max system threads = 32
Running with 32 threads

Graph: grid1000x1000.graph

Top down bfs
ref_time: 0.029874s
stu_time: 0.0217183s

Bottom up bfs
ref_time: 0.536326s
stu_time: 0.827648s

Hybrid bfs
ref_time: 0.227911s
stu_time: 0.823596s

Graph: soc-livejournal1_68m.graph

Top down bfs
ref_time: 0.0632036s
stu_time: 0.036948s

Bottom up bfs
ref_time: 0.0545595s
stu_time: 0.135299s

Hybrid bfs
ref_time: 0.0474562s
stu_time: 0.136135s

Graph: com-orkut_117m.graph

Top down bfs
ref_time: 0.0751638s
stu_time: 0.0605116s

Bottom up bfs
ref_time: 0.0518518s
stu_time: 0.11458s

Hybrid bfs
ref_time: 0.0586801s
stu_time: 0.114804s

Graph: random_500m.graph

Top down bfs
ref_time: 1.26754s
stu_time: 0.936308s

Bottom up bfs
ref_time: 2.49479s
stu_time: 1.9186s

Hybrid bfs
ref_time: 0.895784s
stu_time: 1.89608s

Graph: rmat_200m.graph

Top down bfs
ref_time: 0.549804s
stu_time: 0.428753s

Bottom up bfs
ref_time: 0.481859s
stu_time: 0.671036s

Hybrid bfs
ref_time: 0.441583s
stu_time: 0.66682s


--------------------------------------------------------------------------
SCORES :                    |   Top-Down    |   Bott-Up    |    Hybrid    |
--------------------------------------------------------------------------
grid1000x1000.graph         |      2.00 / 2 |     2.69 / 3 |     0.60 / 3 |
--------------------------------------------------------------------------
soc-livejournal1_68m.graph  |      2.00 / 2 |     1.22 / 3 |     0.89 / 3 |
--------------------------------------------------------------------------
com-orkut_117m.graph        |      2.00 / 2 |     1.52 / 3 |     1.87 / 3 |
--------------------------------------------------------------------------
random_500m.graph           |      7.00 / 7 |     8.00 / 8 |     4.36 / 8 |
--------------------------------------------------------------------------
rmat_200m.graph             |      7.00 / 7 |     8.00 / 8 |     7.40 / 8 |
--------------------------------------------------------------------------
TOTAL                                                      |  56.54 / 70 |
--------------------------------------------------------------------------
```