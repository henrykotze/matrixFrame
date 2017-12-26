
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
        cv::Point getPosition();
        cv::Scalar getColor();
        element(cv::Point, cv::Scalar);
        element();
    private:
        cv::Point textPos;
        cv::Scalar color;
};

element::element(cv::Point pos, cv::Scalar colr){
    textPos = pos;
    color = colr;

}

element::element(){
    textPos = cv::Point();
    color = cv::Scalar();
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

#endif