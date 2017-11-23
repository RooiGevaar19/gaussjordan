#!/bin/bash

exec="run"

echo "//------------------------------------------------------------------------------" >> foutput.cpp
echo "// Projekt:   MyMatrix vs. Eigen - test metody eliminacji Gaussa z pełnym wyborem" > foutput.cpp
echo "// Autorzy:   Paweł Lipkowski" >> foutput.cpp
echo "//            Szymon Cimochowski" >> foutput.cpp
echo "// Data:      11/22/2017" >> foutput.cpp
if ls 00-*.sub.cpp 1> /dev/null 2>&1; then
	echo "//------------------------------------------------------------------------------" >> foutput.cpp
	echo "// Nagłówki i stałe" >> foutput.cpp
	echo "// " >> foutput.cpp
	cat 00-*.sub.cpp >> foutput.cpp
fi
if ls 01-*.sub.cpp 1> /dev/null 2>&1; then
	echo "//------------------------------------------------------------------------------" >> foutput.cpp
	echo "// Klasy i struktury" >> foutput.cpp
	echo "// " >> foutput.cpp
	cat 01-*.sub.cpp >> foutput.cpp
fi
if ls 02-*.sub.cpp 1> /dev/null 2>&1; then
	echo "//------------------------------------------------------------------------------" >> foutput.cpp
	echo "// Funkcje pomocnicze do testów" >> foutput.cpp
	echo "// " >> foutput.cpp
	cat 02-*.sub.cpp >> foutput.cpp
fi
if ls 03-*.sub.cpp 1> /dev/null 2>&1; then
	echo "//------------------------------------------------------------------------------" >> foutput.cpp
	echo "// Moduł testowy" >> foutput.cpp
	echo "// " >> foutput.cpp
	cat 03-*.sub.cpp >> foutput.cpp
fi
if ls 04-Main.sub.cpp 1> /dev/null 2>&1; then
	echo "//------------------------------------------------------------------------------" >> foutput.cpp
	echo "// Main" >> foutput.cpp
	echo "// " >> foutput.cpp
	cat 04-Main.sub.cpp >> foutput.cpp
fi
echo "//------------------------------------------------------------------------------" >> foutput.cpp
case $1 in
   "save-output")
	g++ foutput.cpp -o "$exec" -lm -std=c++11 -O3
	;;
   "save-temps")
	g++ foutput.cpp -o "$exec" -lm -std=c++11 -O3 --save-temps -masm=intel
	rm foutput.cpp
	;;
   "save-all")
	g++ foutput.cpp -o "$exec" -lm -std=c++11 -O3 --save-temps -masm=intel
	;;
   *) 
	g++ foutput.cpp -o "$exec" -lm -std=c++11 -O3
	rm foutput.cpp
	;;
esac