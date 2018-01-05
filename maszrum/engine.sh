#!/bin/bash

java -classpath ./GenerowanieJava MatrixGenerator $1 $2 > ./ObliczanieCpp/input
echo -ne "$2\t$[`cat ./ObliczanieCpp/input | wc -l` - 2]\t" >> $4
result_mmtseidel=`./ObliczanieCpp/run-mmtseidel ./ObliczanieCpp/input 2>> $4`
echo -ne "\t" >> $4
result_mmtjacobi=`./ObliczanieCpp/run-mmtjacobi ./ObliczanieCpp/input 2>> $4`
echo -ne "\t" >> $4
result_mmtpartial=`./ObliczanieCpp/run-mmtpartial ./ObliczanieCpp/input 2>> $4`
echo -ne "\t" >> $4
result_mmtsparse=`./ObliczanieCpp/run-mmtsparse ./ObliczanieCpp/input 2>> $4`
echo -ne "\t" >> $4
result_eigpartial=`./ObliczanieCpp/run-eigpartial ./ObliczanieCpp/input 2>> $4`
echo -ne "\t" >> $4
result_eigsparse=`./ObliczanieCpp/run-eigsparse ./ObliczanieCpp/input 2>> $4`
echo -ne "\n" >> $4
result_sim=`./SymulacjaFPC/project1 $1 $2 $3`
echo -e "$2\t$[`cat ./ObliczanieCpp/input | wc -l` - 2]\t$result_sim\t$result_mmtseidel\t$result_mmtjacobi\t$result_mmtpartial\t$result_mmtsparse\t$result_eigpartial\t$result_eigsparse"