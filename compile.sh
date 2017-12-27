#!/bin/sh


echo "Compiling element.cpp"
g++ ./dep/element.cpp `pkg-config --libs opencv` -std=c++11 -c 

echo "Compiling functions.cpp"  | tee -a compile.log
g++ ./dep/functions.cpp `pkg-config --libs opencv` -std=c++11 -c | tee -a compile.log

echo "Compiling main.cpp" | tee -a compile.log
g++ main.cpp `pkg-config --libs opencv` -std=c++11 -c  | tee -a compile.log

echo "Linking" | tee -a compile.log
g++ functions.o element.o main.o -o matrixFrame | tee -a compile.log

echo "Done"