#include "element.hpp"

element::element(cv::Point pos, cv::Scalar colr, std::string txt){
    textPos = pos;
    color = colr;
    text = txt;

}

element::element(){
    textPos = cv::Point();
    color = cv::Scalar();
    text = std::string();
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
void element::setText(std::string txt){
    text = txt;
}
std::string element::getText(){
    return text;
}