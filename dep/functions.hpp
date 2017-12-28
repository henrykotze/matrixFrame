#ifndef FUNCTIONS_H
#define FUNCTIONS_H


// User defined header file

#include "element.hpp"

using namespace std;

vector<vector<cv::Point>> getContours(cv::Mat frame, int thresh);
cv::Point initMatrixMem(cv::Point frameSize, vector<element>* textPos, double fontSize);
void drawFrame(cv::Mat frame, vector<element>* textInfo, double font);
void updateFrame(vector<vector<cv::Point>> contours, vector<element>* textInfo, cv::Point textSize);

void threshold_callback(int pos, void* image);
void setThreshold(cv::Mat frame, int thresh, int max_tresh);

#endif