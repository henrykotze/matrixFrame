#!/bin/sh


echo "Creating build dir" | tee -a ./build/compile.log
mkdir -p ./build

echo "Compiling element.cpp" | tee -a ./build/compile.log
g++ -c ./dep/element.cpp `pkg-config --libs opencv` -std=c++11 -o ./build/element.o 2>&1  | tee -a ./build/compile.log

echo "Compiling functions.cpp"  | tee -a ./build/compile.log
g++ -c ./dep/functions.cpp `pkg-config --libs opencv` -std=c++11 -o ./build/functions.o 2>&1 | tee -a ./build/compile.log

echo "Compiling main.cpp" | tee -a ./build/compile.log
g++ -c main.cpp `pkg-config --libs opencv` -std=c++11 -o ./build/main.o 2>&1 | tee -a ./build/compile.log

echo "Linking object files" | tee -a ./build/compile.log
g++ -std=c++11 `pkg-config --libs opencv` ./build/*.o -o matrixFrame 2>&1 | tee -a ./build/compile.log

echo "Done"