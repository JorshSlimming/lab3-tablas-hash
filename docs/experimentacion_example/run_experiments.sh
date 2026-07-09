#!/bin/bash

echo "ejecutable;numElementos;tiempo"

for (( c=1; c<=30; c++ ))
do
    for n in 100000 200000 300000 400000 500000
    do
	./heapsort_v1 $n
    done

    for n in 100000 200000 300000 400000 500000
    do
	./heapsort_v2 $n
    done
done
