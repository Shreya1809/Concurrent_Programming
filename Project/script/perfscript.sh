#!/bin/bash
cd bin/
echo "***********NUMBER OF THREADS: 100, 200, 500, 1000, 1500, 2000**********"
echo "XXXXXXXXXXXXX----------------MICROBENCHMARK----------------XXXXXXXXXXX"
echo "   "
echo "@@@@@@@@@@......Perf Analysis of project......@@@@@@@@@@"
echo "###########------Cache misses------############"
perf stat -e cache-misses ./project -t100 
perf stat -e cache-misses ./project -t200 
perf stat -e cache-misses ./project -t500 
perf stat -e cache-misses ./project -t1000
perf stat -e cache-misses ./project -t1500
perf stat -e cache-misses ./project -t2000
echo "###########------L1-dcache-loads------############"
perf stat -e L1-dcache-loads ./project -t200  
perf stat -e L1-dcache-loads ./project -t500  
perf stat -e L1-dcache-loads ./project -t1000 
perf stat -e L1-dcache-loads ./project -t1500 
perf stat -e L1-dcache-loads ./project -t2000 
echo "###########------L1-dcache-load-misses------############"
perf stat -e L1-dcache-load-misses ./project -t200 
perf stat -e L1-dcache-load-misses ./project -t500 
perf stat -e L1-dcache-load-misses ./project -t1000
perf stat -e L1-dcache-load-misses ./project -t1500
perf stat -e L1-dcache-load-misses ./project -t2000
echo "###########------branch-load-misses------############"
perf stat -e branch-load-misses ./project -t200 
perf stat -e branch-load-misses ./project -t500 
perf stat -e branch-load-misses ./project -t1000
perf stat -e branch-load-misses ./project -t1500
perf stat -e branch-load-misses ./project -t2000
echo "###########------branch-loads------############"
perf stat -e branch-loads ./project -t200 
perf stat -e branch-loads ./project -t500 
perf stat -e branch-loads ./project -t1000
perf stat -e branch-loads ./project -t1500
perf stat -e branch-loads ./project -t2000
echo "###########------page faults------############"
perf stat -e page-faults ./project -t200 
perf stat -e page-faults ./project -t500 
perf stat -e page-faults ./project -t1000
perf stat -e page-faults ./project -t1500
perf stat -e page-faults ./project -t2000
echo "   "