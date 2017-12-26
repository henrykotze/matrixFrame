
#ifndef __ELEMENT_H_INCLUDED__
#define __ELEMENT_H_INCLUDED__

#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/core/utility.hpp"
#include <opencv2/opencv.hpp>



class element {
    public:
        void setPosition(cv::Point pos);
        void setColor(cv::Scalar);
        void setText(char);
        cv::Point getPosition();
        cv::Scalar getColor();
        char getText();
        element(cv::Point, cv::Scalar, char);
        element();
    private:
        cv::Point textPos;
        cv::Scalar color;
        char text;
};

element::element(cv::Point pos, cv::Scalar colr, char txt){
    textPos = pos;
    color = colr;
    text = txt;

}

element::element(){
    textPos = cv::Point();
    color = cv::Scalar();
    text = ' ';
}

void element::setColor(cv::Scalar colr){
    color = colr;
}

void element::setPosition(cv::Point pos){
    textPos = pos;
}

cv::Point element::getPosition(){
    return textPos;
}
cv::Scalar element::getColor(){
    return color;
}
void element::setText(char txt){
    text = txt;
}
char element::getText(){
    return text;
}

#endif