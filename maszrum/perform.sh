#!/bin/bash
echo -e "Size\tMSize\tSimulation\tMyMatrixSeidel\tMyMatrixJacobi\tMyMatrixPartial\tMyMatrixSparse\tEigenPartial\tEigenSparse"
echo -e "Size\tMSize\tMyMatrixSeidel\tMyMatrixJacobi\tMyMatrixPartial\tMyMatrixSparse\tEigenPartial\tEigenSparse" > $2
for i in `seq 1 1 16` ; do
./engine.sh $1 $i 1000 $2
done