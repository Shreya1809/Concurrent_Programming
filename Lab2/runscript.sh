#!/bin/bash
cd bin/
# valgrind --tool=memcheck --leak-check=yes ./mysort testcase2.txt -o output2.txt -t10 --alg=bucket --bar=sense --lock=tas
./mysort testcase3.txt -o output2.txt -t10 --alg=bucket --bar=pthread --lock=mcs
# valgrind --tool=helgrind ./benchmark -t10 -i1000 --lock=mcs -o out.txt
# valgrind --tool=memcheck --leak-check=yes ./benchmark -t2 -i5 --bar=sense -o out.txt
# ./benchmark -t2 -i5 --bar=pthread -o out.txt
# valgrind --tool=helgrind ./mysort testcase2.txt -o output2.txt -t10 --alg=bucket --bar=sense --lock=mutex
