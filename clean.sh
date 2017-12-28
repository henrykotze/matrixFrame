#!/bin/sh

echo "Cleaning building process"

echo "Removing Object Files:"
ls ./build/*.o
rm ./build/*.o

echo "Removing execurtable binary"
rm ./matrixFrame

echo "Removing compile.log"
rm ./build/compile.log

echo "Done"

