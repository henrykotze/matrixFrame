#!/bin/sh


g++ ./dep/functions.cpp `pkg-config --libs opencv` -std=c++11 -c 
g++ 