#ifndef FUNCTIONS_H
#define FUNCTIONS_H_


#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/opencv.hpp>

// User defined header file
#include "element.hpp"
using namespace std;

vector<vector<cv::Point>> getContours(cv::Mat frame);
cv::Point initMatrix(cv::Point frameSize, vector<cv::Point>* textPos, double fontSize);
cv::Point initMatrixMem(cv::Point frameSize, vector<element>* textPos, double fontSize);
void drawFrame(cv::Mat frame, vector<element>* textInfo, double font);
void threshold_callback(int, void*);
void textsize_callback(int, void*);
void fillText(cv::Mat frame, double fontsize);
void updateFrame(vector<vector<cv::Point>> contours, vector<element>* textInfo, cv::Point textSize);

#endif