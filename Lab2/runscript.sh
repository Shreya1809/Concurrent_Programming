#!/bin/bash
cd bin/
./mysort testcase2.txt -o output2.txt -t10 --alg=bucket --bar=sense --lock=tas
./benchmark -t10 -i100 --lock=tas -o out.txt