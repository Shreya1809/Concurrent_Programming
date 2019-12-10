#!/bin/bash

ITER=$1

for ((i=1;i<=$ITER;i++)); 
do
    ../bin/project -t50 &>> run.log

done

for ((i=1;i<=$ITER;i++)); 
do
    ../bin/project -t100 &>> run.log
   
done

for ((i=1;i<=$ITER;i++)); 
do
    ../bin/project -t200 &>> run.log
done

for ((i=1;i<=$ITER;i++)); 
do
    ../bin/project -t500 &>> run.log
   
done

for ((i=1;i<=$ITER;i++)); 
do
    ../bin/project -t1000 &>> run.log
   
done

for ((i=1;i<=$ITER;i++)); 
do
    ../bin/project -t1500 &>> run.log
   
done

for ((i=1;i<=$ITER;i++)); 
do
    ../bin/project -t2000 &>> run.log
   
done