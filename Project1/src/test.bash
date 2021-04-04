#! /bin/bash

while true;do
    echo "test"
    ./randomDAG 100 0.6 > testfile
    ./old < testfile > oldout
    ./main < testfile > mainout
    diff oldout mainout

done