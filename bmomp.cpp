/**
 Benchmark code for overhead of OpenMP

 Copyright (c) 2014 Daichi OBINATA

 This software is released under the MIT License.
 http://opensource.org/licenses/mit-license.php
*/

#include <cstdlib>
#include <cstdio>
#include <string>
#include <sys/time.h>
#ifdef _OPENMP
#include <omp.h>
#else
int  omp_get_num_threads() { return 1; }
void omp_set_num_threads(int n) { }
#endif

const size_t nmax_default = 100000L;

int main(int argc, char** argv)
{
  size_t nmax = nmax_default;
  int t0 = omp_get_num_threads();
  int t1 = omp_get_num_threads();

  for (int a = 1; a < argc; a++) {
    const std::string a0 = argv[a];
    const std::string a1 = (a+1 < argc)? argv[a+1]: "";
    const std::string a2 = (a+2 < argc)? argv[a+2]: "";
    if (a0 == "-L") {
      nmax = std::atol(a1.c_str());
      a++;
    } else if (a0 == "-t" || a0 == "--threads" ) {
      t1 = t0 = std::atoi(a1.c_str());
      a++;
    } else if (a0 == "-R" || a0 == "--threads-range") {
      t0 = std::atoi(a1.c_str());
      t1 = std::atoi(a2.c_str());
      a += 2;
    }
  }

  for (int t = t0; t <= t1; t++ ) {
    timeval tv1,tv2;
    omp_set_num_threads(t);
    gettimeofday(&tv1, NULL);

    for (size_t n = 0; n < nmax; n++) {
#ifdef _OPENMP
#pragma omp parallel
      {
        asm("nop");
      }
#else
      asm("nop");
#endif
    }

    gettimeofday(&tv2, NULL);
    const float sec  = tv2.tv_sec  - tv1.tv_sec;
    const float usec = tv2.tv_usec - tv1.tv_usec;
    const float time = sec + usec / 10e6;
#ifdef _OPENMP
    const int tout = t;
#else
    const int tout = 0;
#endif
    std::printf(" n = %lu, threads = %2d, time = %8.5f[s]\n",nmax,tout,time);
  }

  return 0;
}
