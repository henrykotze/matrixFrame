# matrixFrame

matrixFrame tries to create a "The Matrix" art of a input frame. As seen here: 

![alt text](http://www.citizenop.com/wp-content/uploads/2016/03/the-matrix.jpg)

## Status
----
* Still in development

## Current Developing
----
* Currently creating a playground for implementing the idea
* Development is done using openCV 3.2.0 
* Compiler gcc 7.2.1

## How to compile
----
*   Currently: run the compile script : ```./compile```

## How to clean
----
*   Run the clean script: ```./clean```

## Debugging
----
*  During compiling, the output of each compiling source file is written to compile.log

## How things are done
----
*   In the ./dep directory is all the dependancies for the matrixFrame. Each one containing the classes and function declarations.
*   each *.cpp source file is compiled seperately in the ```./dep``` directory. For each source file, an object file is created in the top directory.
*   The main.cpp is compile to create the last object file, where thereafter the linking is done to create the executable binary ```matrixFrame```

## Future Plans
----

*	Use ML to generate matrix embedded images/videos
