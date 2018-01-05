#!/bin/bash
echo -e "Size\tSimulation\tMyMatrixSeidel\tMyMatrixJacobi\tMyMatrixPartial\tMyMatrixSparse\tEigenPartial\tEigenSparse"
for i in `seq 1 1 16` ; do
./engine.sh $1 $i 1000
done