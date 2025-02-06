#!/bin/bash

gcc create_matrix.c -o c

n=2

for i in {1..2}; do
    echo -e "matrix${i}.bin\n${n}" | ./c
done

gcc 31581048_1.c -o p1
./p1

rm matrix1.bin matrix2.bin c