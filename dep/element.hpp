#pragma once
#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/core/utility.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>



class element {
    public:
        void setPosition(cv::Point pos);
        void setColor(cv::Scalar);
        void setText(std::string);
        cv::Point getPosition();
        cv::Scalar getColor();
        std::string getText();
        element(cv::Point, cv::Scalar, std::string);
        element();
    private:
        cv::Point textPos;
        cv::Scalar color;
        std::string text;
};


#endif