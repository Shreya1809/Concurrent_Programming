#!/bin/bash
cd bin/
echo "***********NUMBER OF THREADS: 10, NUM OF ITERATIONS 50000**********"
echo "XXXXXXXXXXXXX----------------MICROBENCHMARK----------------XXXXXXXXXXX"
echo "   "
echo "@@@@@@@@@@......Perf Analysis of Microbenchmark Locks......@@@@@@@@@@"
echo "###########------Cache misses------############"
perf stat -e cache-misses ./benchmark -t10 -i50000 --lock=tas -o out.txt
perf stat -e cache-misses ./benchmark -t10 -i50000 --lock=ttas -o out.txt
perf stat -e cache-misses ./benchmark -t10 -i50000 --lock=ticket -o out.txt
perf stat -e cache-misses ./benchmark -t10 -i50000 --lock=mcs -o out.txt
perf stat -e cache-misses ./benchmark -t10 -i50000 --lock=pthread -o out.txt
echo "###########------L1-dcache-loads------############"
perf stat -e L1-dcache-loads ./benchmark -t10 -i50000 --lock=tas -o out.txt
perf stat -e L1-dcache-loads ./benchmark -t10 -i50000 --lock=ttas -o out.txt
perf stat -e L1-dcache-loads ./benchmark -t10 -i50000 --lock=ticket -o out.txt
perf stat -e L1-dcache-loads ./benchmark -t10 -i50000 --lock=mcs -o out.txt
perf stat -e L1-dcache-loads ./benchmark -t10 -i50000 --lock=pthread -o out.txt
echo "###########------L1-dcache-load-misses------############"
perf stat -e L1-dcache-load-misses ./benchmark -t10 -i50000 --lock=tas -o out.txt
perf stat -e L1-dcache-load-misses ./benchmark -t10 -i50000 --lock=ttas -o out.txt
perf stat -e L1-dcache-load-misses ./benchmark -t10 -i50000 --lock=ticket -o out.txt
perf stat -e L1-dcache-load-misses ./benchmark -t10 -i50000 --lock=mcs -o out.txt
perf stat -e L1-dcache-load-misses ./benchmark -t10 -i50000 --lock=pthread -o out.txt
echo "###########------branch-load-misses------############"
perf stat -e branch-load-misses ./benchmark -t10 -i50000 --lock=tas -o out.txt
perf stat -e branch-load-misses ./benchmark -t10 -i50000 --lock=ttas -o out.txt
perf stat -e branch-load-misses ./benchmark -t10 -i50000 --lock=ticket -o out.txt
perf stat -e branch-load-misses ./benchmark -t10 -i50000 --lock=mcs -o out.txt
perf stat -e branch-load-misses ./benchmark -t10 -i50000 --lock=pthread -o out.txt
echo "###########------branch-loads------############"
perf stat -e branch-loads ./benchmark -t10 -i50000 --lock=tas -o out.txt
perf stat -e branch-loads ./benchmark -t10 -i50000 --lock=ttas -o out.txt
perf stat -e branch-loads ./benchmark -t10 -i50000 --lock=ticket -o out.txt
perf stat -e branch-loads ./benchmark -t10 -i50000 --lock=mcs -o out.txt
perf stat -e branch-loads ./benchmark -t10 -i50000 --lock=pthread -o out.txt
echo "###########------page faults------############"
perf stat -e page-faults ./benchmark -t10 -i50000 --lock=tas -o out.txt
perf stat -e page-faults ./benchmark -t10 -i50000 --lock=ttas -o out.txt
perf stat -e page-faults ./benchmark -t10 -i50000 --lock=ticket -o out.txt
perf stat -e page-faults ./benchmark -t10 -i50000 --lock=mcs -o out.txt
perf stat -e page-faults ./benchmark -t10 -i50000 --lock=pthread -o out.txt
echo "   "
echo "@@@@@@@@@@......Perf Analysis of Microbenchmark barriers......@@@@@@@@@@"
echo "###########------Cache misses------############"
perf stat -e cache-misses ./benchmark -t10 -i50000 --bar=pthread -o out.txt
perf stat -e cache-misses ./benchmark -t10 -i50000 --bar=sense -o out.txt
echo "###########------L1-dcache-loads------############"
perf stat -e L1-dcache-loads ./benchmark -t10 -i50000 --bar=pthread -o out.txt
perf stat -e L1-dcache-loads ./benchmark -t10 -i50000 --bar=sense -o out.txt
echo "###########------L1-dcache-load-misses------############"
perf stat -e L1-dcache-load-misses ./benchmark -t10 -i50000 --bar=pthread -o out.txt
perf stat -e L1-dcache-load-misses ./benchmark -t10 -i50000 --bar=sense -o out.txt
echo "###########------branch-load-misses------############"
perf stat -e branch-load-misses ./benchmark -t10 -i50000 --bar=pthread -o out.txt
perf stat -e branch-load-misses ./benchmark -t10 -i50000 --bar=sense -o out.txt
echo "###########------branch-loads------############"
perf stat -e branch-loads ./benchmark -t10 -i50000 --bar=pthread -o out.txt
perf stat -e branch-loads ./benchmark -t10 -i50000 --bar=sense -o out.txt
echo "###########------page faults------############"
perf stat -e page-faults ./benchmark -t10 -i50000 --bar=pthread -o out.txt
perf stat -e page-faults ./benchmark -t10 -i50000 --bar=sense -o out.txt
echo "    "
echo "   "
echo "XXXXXXXXXXXXX----------------BUCKETSORT----------------XXXXXXXXXXX"
echo "   "
echo "@@@@@@@@@@......Perf Analysis of bucket sort Locks, no of threads-> 20......@@@@@@@@@@"
echo "###########------Cache misses------############"
perf stat -e cache-misses ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=tas
perf stat -e cache-misses ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=ttas
perf stat -e cache-misses ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=ticket
perf stat -e cache-misses ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=mcs
perf stat -e cache-misses ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=pthread
echo "###########------L1-dcache-loads------############"
perf stat -e L1-dcache-loads ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=tas
perf stat -e L1-dcache-loads ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=ttas
perf stat -e L1-dcache-loads ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=ticket
perf stat -e L1-dcache-loads ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=mcs
perf stat -e L1-dcache-loads ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=pthread
echo "###########------L1-dcache-load-misses------############"
perf stat -e L1-dcache-load-misses ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=tas
perf stat -e L1-dcache-load-misses ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=ttas
perf stat -e L1-dcache-load-misses ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=ticket
perf stat -e L1-dcache-load-misses ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=mcs
perf stat -e L1-dcache-load-misses ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=pthread
echo "###########------branch-load-misses------############"
perf stat -e branch-load-misses ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=tas
perf stat -e branch-load-misses ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=ttas
perf stat -e branch-load-misses ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=ticket
perf stat -e branch-load-misses ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=mcs
perf stat -e branch-load-misses ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=pthread
echo "###########------branch-loads------############"
perf stat -e branch-loads ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=tas
perf stat -e branch-loads ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=ttas
perf stat -e branch-loads ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=ticket
perf stat -e branch-loads ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=mcs
perf stat -e branch-loads ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=pthread
echo "###########------page faults------############"
perf stat -e page-faults ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=tas
perf stat -e page-faults ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=ttas
perf stat -e page-faults ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=ticket
perf stat -e page-faults ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=mcs
perf stat -e page-faults ./mysort testcase3.txt -o output2.txt -t20 --alg=bucket --lock=pthread
echo "   "
echo "@@@@@@@@@@......Perf Analysis of forkjoin Barriers,no of threads-> 20......@@@@@@@@@@"
echo "###########------Cache misses------############"
perf stat -e cache-misses ./mysort testcase3.txt -o output2.txt -t20 --alg=fj --bar=pthread
perf stat -e cache-misses ./mysort testcase3.txt -o output2.txt -t20 --alg=fj --bar=sense 
echo "###########------L1-dcache-loads------############"
perf stat -e L1-dcache-loads ./mysort testcase3.txt -o output2.txt -t20 --alg=fj --bar=pthread 
perf stat -e L1-dcache-loads ./mysort testcase3.txt -o output2.txt -t20 --alg=fj --bar=sense 
echo "###########------L1-dcache-load-misses------############"
perf stat -e L1-dcache-load-misses ./mysort testcase3.txt -o output2.txt -t20 --alg=fj --bar=pthread 
perf stat -e L1-dcache-load-misses ./mysort testcase3.txt -o output2.txt -t20 --alg=fj --bar=sense 
echo "###########------branch-load-misses------############"
perf stat -e branch-load-misses ./mysort testcase3.txt -o output2.txt -t20 --alg=fj --bar=pthread
perf stat -e branch-load-misses ./mysort testcase3.txt -o output2.txt -t20 --alg=fj --bar=sense 
echo "###########------branch-loads------############"
perf stat -e branch-loads ./mysort testcase3.txt -o output2.txt -t20 --alg=fj --bar=pthread
perf stat -e branch-loads ./mysort testcase3.txt -o output2.txt -t20 --alg=fj --bar=sense 
echo "###########------page faults------############"
perf stat -e page-faults ./mysort testcase3.txt -o output2.txt -t20 --alg=fj --bar=pthread
perf stat -e page-faults ./mysort testcase3.txt -o output2.txt -t20 --alg=fj --bar=sense 