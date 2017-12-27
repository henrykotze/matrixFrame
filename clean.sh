#!/bin/sh

echo "Cleaning building process"

echo "Removing Object Files:"
ls ./*.o
rm ./*.o

echo "Removing compile.log"
rm ./compile.log


