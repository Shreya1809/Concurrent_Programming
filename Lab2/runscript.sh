#!/bin/bash
cd bin/
# valgrind --tool=memcheck --leak-check=yes ./mysort testcase2.txt -o output2.txt -t10 --alg=bucket --bar=sense --lock=tas
# ./mysort testcase2.txt -o output2.txt -t10 --alg=bucket --bar=sense --lock=mcs
# #./benchmark -t2 -i10 --lock=mcs -o out.txt
# valgrind --tool=memcheck --leak-check=yes ./benchmark -t2 -i5 --bar=sense -o out.txt
#./benchmark -t2 -i5 --bar=pthread -o out.txt
./mysort testcase2.txt -o output2.txt -t10 --alg=fj --bar=sense --lock=mcs