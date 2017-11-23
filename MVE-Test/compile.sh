#!/bin/bash

#=======================================================================================================
# KOMPILATOR WIELOPROJEKTOWY
#=======================================================================================================
# dane o programie, możliwość edycji

exec="run";
i=1;
for ifile in `ls 04-*.sub.cpp` ; do
echo "//------------------------------------------------------------------------------" > foutput-$i-.cpp
echo "// Projekt:   MyMatrix vs. Eigen" >> foutput-$i-.cpp
echo "// Autorzy:   Paweł Lipkowski" >> foutput-$i-.cpp
echo "// Data:      11/23/2017" >> foutput-$i-.cpp
#=======================================================================================================
# silnik kompilujący moduły
if ls 00-*.sub.cpp 1> /dev/null 2>&1; then
	echo "//------------------------------------------------------------------------------" >> foutput-$i-.cpp
	echo "// Nagłówki i stałe" >> foutput-$i-.cpp
	echo "// " >> foutput-$i-.cpp
	cat 00-*.sub.cpp >> foutput-$i-.cpp
fi
if ls 01-*.sub.cpp 1> /dev/null 2>&1; then
	echo "//------------------------------------------------------------------------------" >> foutput-$i-.cpp
	echo "// Klasy i struktury" >> foutput-$i-.cpp
	echo "// " >> foutput-$i-.cpp
	cat 01-*.sub.cpp >> foutput-$i-.cpp
fi
if ls 02-*.sub.cpp 1> /dev/null 2>&1; then
	echo "//------------------------------------------------------------------------------" >> foutput-$i-.cpp
	echo "// Funkcje pomocnicze do testów" >> foutput-$i-.cpp
	echo "// " >> foutput-$i-.cpp
	cat 02-*.sub.cpp >> foutput-$i-.cpp
fi
if ls 03-*.sub.cpp 1> /dev/null 2>&1; then
	echo "//------------------------------------------------------------------------------" >> foutput-$i-.cpp
	echo "// Moduł testowy" >> foutput-$i-.cpp
	echo "// " >> foutput-$i-.cpp
	cat 03-*.sub.cpp >> foutput-$i-.cpp
fi
#if ls $ifile 1> /dev/null 2>&1; then
	echo "//------------------------------------------------------------------------------" >> foutput-$i-.cpp
	echo "// Main" >> foutput-$i-.cpp
	echo "// " >> foutput-$i-.cpp
	cat "$ifile" >> foutput-$i-.cpp
#fi
echo "//------------------------------------------------------------------------------" >> foutput-$i-.cpp
#=======================================================================================================
# silnik kompilujący
case $1 in
   "save-output")
	g++ foutput-$i-.cpp -o "$exec-$i" -lm -std=c++11 -O3
	;;
   "save-temps")
	g++ foutput-$i-.cpp -o "$exec-$i" -lm -std=c++11 -O3 --save-temps -masm=intel
	rm foutput-$i-.cpp
	;;
   "save-all")
	g++ foutput-$i-.cpp -o "$exec-$i" -lm -std=c++11 -O3 --save-temps -masm=intel
	;;
   *) 
	g++ foutput-$i-.cpp -o "$exec-$i" -lm -std=c++11 -O3
	rm foutput-$i-.cpp
	;;
esac
i=$((i+1))
done