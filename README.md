# matrixFrame

matrixFrame tries to create a "The Matrix" art of a input frame. As seen here: 

![alt text](http://www.citizenop.com/wp-content/uploads/2016/03/the-matrix.jpg)

## Status
----
* Still in development

## Workflow
----
* Initially it will prompt your input image with a trackbar. Move this trackbar to set how many contours you want to capture in the transformation. Pressing Esc will continue to allow the transformation to be done on the given threshold value. After a few seconds/minutes it will display your transformed image.

## Excecution Time Variables
----
1.  size of image
2.  size of text
3.  number on contours to capture

## Current Developing
----
* Currently creating a playground for implementing the idea
* Development is done using openCV 3.2.0 
* Compiler gcc 7.2.1

## How to compile
----
*   In ```main.cpp``` give the path to the image to transform in the following line: ```string imageName("/home/henry/Documents/github_dev/matrixFrame/images/v3.jpg");```
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

## Current Transformation Results:
![alt text](https://raw.githubusercontent.com/hhenryy/matrixFrame/updateFrame/images/v.jpg)

to

![alt text](https://raw.githubusercontent.com/hhenryy/matrixFrame/updateFrame/output.jpg)


## Future Plans
----

*	Use ML to generate matrix embedded images/videos
