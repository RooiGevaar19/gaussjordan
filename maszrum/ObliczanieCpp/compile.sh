#!/bin/bash

g++ MyMatrixSeidel.cpp -o run-seidel -lm -std=c++11 -O3
g++ MyMatrixJacobi.cpp -o run-jacobi -lm -std=c++11 -O3

