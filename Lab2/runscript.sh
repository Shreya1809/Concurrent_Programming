#!/bin/bash
cd bin/
./mysort testcase2.txt -o output2.txt -t10 --alg=bucket --bar=sense --lock=ttas
./counter -t10 -i100 --bar=sense --lock=tas -o out.txt