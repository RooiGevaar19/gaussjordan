#!/bin/bash

java -classpath ./GenerowanieJava MatrixGenerator $1 $2 > ./ObliczanieCpp/input 2> engine.log
result_math=`./ObliczanieCpp/run ./ObliczanieCpp/input 2>> engine.log`
result_sim=`./SymulacjaFPC/project1 $1 $2 $3 2>> engine.log`
echo "$result_math $result_sim" | ./Utils/rpn '> > -' 2>> engine.log