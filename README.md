Benchmark code for overhead of OpenMP
====

OpenMPプログラムのパラレルリージョンのオーバーヘッドを計測するプログラム。

# 実行方法

$ ./a.out \[-L _n_\] \[-t|--threads _t_\] \[-R|--threads-range _t0_ _t1_\]

## 実行オプション

* -L: 反復回数 [100000]
* -t,--threads: スレッド数 [$OMP\_NUM\_THREADS]
* -R,--threads-range: スレッド数の範囲。このオプションが指定されたときは、スレッド数を_t0_から_t1_まで変化させて実行する。

## 実行例

```sh:
$ g++ -fopenmp bmomp.cpp
$ ./a.out -L 1000000 -R 1 4
 n = 1000000, threads =  1, time =  0.96147[s]
 n = 1000000, threads =  2, time = 21.08942[s]
 n = 1000000, threads =  3, time = 25.95262[s]
 n = 1000000, threads =  4, time = 30.01921[s]
$
```

# スコア例

## MacPro Mid2010 2.8GHz Quad-Core

### 測定環境
* CPU: Intel Xeon W3530 (Nehalem) 4core with Hyper-threading
* Compiler: g++-4.9 (Homebrew gcc 4.9.2) 4.9.2
* -L = 100000

### スコア
| num threads | time[s]  | graph                                                                    |
|:-----------:|---------:|:-------------------------------------------------------------------------|
|  1          |  0.05911 |                                                                          |
|  2          | 20.92602 | #####################                                                    |
|  3          | 24.02070 | ########################                                                 |
|  4          | 29.05888 | #############################                                            |
|  5          | 39.93421 | ########################################                                 |
|  6          | 50.01220 | ##################################################                       |
|  7          | 61.98178 | ##############################################################           |
|  8          | 72.04011 | ######################################################################## |

----
Copyright (c) 2014 Daichi OBINATA