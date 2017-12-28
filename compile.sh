#!/bin/sh


echo "Creating build dir"
mkdir -p ./build

echo "Compiling element.cpp"
g++ -c ./dep/element.cpp `pkg-config --libs opencv` -std=c++11 -o ./build/element.o  | tee -a ./build/compile.log

echo "Compiling functions.cpp"  | tee -a compile.log
g++ -c ./dep/functions.cpp `pkg-config --libs opencv` -std=c++11 -o ./build/functions.o | tee -a ./build/compile.log

echo "Compiling main.cpp" | tee -a compile.log
g++ -c main.cpp `pkg-config --libs opencv` -std=c++11 -o ./build/main.o| tee -a ./build/compile.log

echo "Linking object files" | tee -a compile.log
g++ -std=c++11 `pkg-config --libs opencv` ./build/*.o -o matrixFrame | tee -a ./build/compile.log

echo "Done"