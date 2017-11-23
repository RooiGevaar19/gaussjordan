#!/bin/bash
rm results-*.csv
for i in run-* ; do
	./$i > results-$i.csv
done