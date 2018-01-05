#!/bin/bash

g++ EigenPartial.cpp -o run-eigpartial -lm -std=c++11 -O3
g++ EigenSparse.cpp -o run-eigsparse -lm -std=c++11 -O3

g++ MyMatrixSeidel.cpp -o run-mmtseidel -lm -std=c++11 -O3
g++ MyMatrixJacobi.cpp -o run-mmtjacobi -lm -std=c++11 -O3
g++ MyMatrixPartial.cpp -o run-mmtpartial -lm -std=c++11 -O3
g++ MyMatrixSparse.cpp -o run-mmtsparse -lm -std=c++11 -O3

