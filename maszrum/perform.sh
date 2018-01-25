#!/bin/bash
echo -e "Size\tMSize\tSimulation\tMyMatrixSeidel\tMyMatrixJacobi\tMyMatrixPartial\tMyMatrixSparse\tEigenPartial\tEigenSparse"
echo -e "Size\tMSize\tMyMatrixSeidel\tMyMatrixJacobi\tMyMatrixPartial\tMyMatrixSparse\tEigenPartial\tEigenSparse" > $2
for i in `seq $4 1 $5` ; do
./engine.sh $1 $i 100000 $2 $3
done