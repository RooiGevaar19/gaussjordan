#!/bin/bash

java -classpath ./GenerowanieJava MatrixGenerator $1 $2 > ./ObliczanieCpp/input 2> engine.log
result_seidel=`./ObliczanieCpp/run-seidel ./ObliczanieCpp/input 2>> engine.log`
result_jacobi=`./ObliczanieCpp/run-jacobi ./ObliczanieCpp/input 2>> engine.log`
result_sim=`./SymulacjaFPC/project1 $1 $2 $3 2>> engine.log`
echo -e "$result_sim\t$result_seidel\t$result_jacobi"
#echo "$result_math $result_sim" | ./Utils/rpn '> > -' 2>> engine.log