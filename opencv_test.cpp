
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h>

#include "./dep/element.hpp"
#include "./dep/functions.hpp"

using namespace std;



int main( int argc, char** argv )
{
    
    string imageName("/home/henry/Documents/github_dev/matrixFrame/opencv_nic2.jpg"); // by default
    cv::Mat image;


    int exit = 0;
    if( argc > 1)
    {
        imageName = argv[1];
    }

    // Defining image objects

    //Loading Image to be Processed
    image = cv::imread(imageName.c_str(), cv::IMREAD_COLOR); // Read the file
    if( image.empty() )                      // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    vector<element>* bar = new vector<element>();

    cout << "Entering Memory allocated class type funtion \n";
    cv::Point charSize2 = initMatrixMem(cv::Point(image.rows,image.cols), bar, 10.0);
    cout << "Exciting Memory allocated class type funtion \n";
    drawFrame(image,bar, 10.0);


    cout << "To exit press Escape \n";
    while(exit != 27){
        exit = cv::waitKey(0); // Wait for Escape to exit
    }
    return 0;
}


/*
void threshold_callback(int, void*){

    cv::Mat canny_output;
    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierarchy;
    
    //Canny the image
    cv::Canny(image_gray, canny_output, thresh, thresh*2,3);

    //Detect contours and store in memory
    cv::findContours(canny_output, contours, hierarchy, CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE, cv::Point(0,0));


    cv::Mat drawing = cv::Mat::zeros( canny_output.size(), CV_8UC3);

    //Draw Contours
    for(int i = 0; i < contours.size(); i++){
       cv::Scalar color = cv::Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       cv::drawContours( drawing, contours, i, color, 1, 8, hierarchy, 0, cv::Point() );
       cv::drawContours( image_copy, contours, i, color, 1, 8, hierarchy, 0, cv::Point() );

       vector<cv::Point> position = contours.at(i);
        //Gives position (x,y) for each pixel in a countour
       for(size_t meep = 0; meep < position.size(); meep++){
           cv::Point point = position.at(meep);
           //cout << point.x << " " << point.y << endl;
       }


       //int proc = cv::waitKey(0);
       //cout << proc << endl;
    }





    cv::namedWindow("Contours on Original", CV_WINDOW_AUTOSIZE);
    cv::namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
    cv::imshow( "Contours", drawing );
    cv::imshow("Contours on Original", image_copy);


}

void textsize_callback(int, void*){

    string text("meep");
    double change_font = double(fontsize)/255;
    int baseline = 0;
    //cv::Mat textImage;
    //textImage = image;

    cv::Mat textImage = cv::Mat::zeros( image.size(), CV_8UC3);

    //insert some text
    cv::putText(textImage, text, cv::Point(20,20), cv::FONT_HERSHEY_DUPLEX, change_font, cv::Scalar(255, 0,3), 1, cv::LINE_8);
    //cv::putText(image, "abcdefghijklmnopqrstuvxyz0123456789", cv::Point(1,0), cv::FONT_HERSHEY_DUPLEX, fontsize, cv::Scalar(255, 0,3), 1, cv::LINE_8);

    cv::Size fontsize = cv::getTextSize(text,cv::FONT_HERSHEY_DUPLEX,change_font,1,&baseline);

    cout << "height: " << fontsize.height << " widht: " << fontsize.width << endl;
    

    cv::namedWindow("Edit",CV_WINDOW_AUTOSIZE);
    cv::imshow("Edit", textImage);

}


void fillText(cv::Mat frame, double font){
    double rows = double(frame.rows);
    double cols = double(frame.cols);
    char test = 100;
    string text(&test);

    vector<cv::Point> textPos;


    int cols_steps = cols/font;
    int rows_steps = rows/font;
    cout << "Number of cols_steps: " << cols_steps << endl;
    cout << "Number of rows_steps: " << rows_steps << endl;
    
    int rows_iter = 0;
    int cols_iter = font;
    int test1 = 0;

    for(int j = 0; j < cols_steps; j++){
        for(int i = 0; i < rows_steps ; i++){
            textPos.push_back(cv::Point(cols_iter,rows_iter));
            text = char(int(rng.uniform(0, 127)));
            //cout << "cols: " << cols_iter << " rows: " << rows_iter << endl;




            //cv::putText(frame, text, cv::Point(cols_iter,rows_iter), cv::FONT_HERSHEY_DUPLEX, 0.25, cv::Scalar(80, 100 , 30), 1, cv::LINE_8);
            cv::putText(frame, text, textPos.at(test1), cv::FONT_HERSHEY_DUPLEX, 0.25, cv::Scalar(80, 100 , 30), 1, cv::LINE_8);
            rows_iter = rows_iter + font;
            test1 += 1;
        }
        cols_iter = cols_iter + font; 
        rows_iter = 0 ;

    }


    cv::namedWindow("filled rows", CV_WINDOW_AUTOSIZE);
    cv::imshow("filled rows", frame);

}

vector<vector<cv::Point>> getContours(cv::Mat frame){

    cv::Mat canny_output;
    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierarchy;
    
    //Canny the image
    cv::Canny(image_gray, canny_output, thresh, thresh*2,3);

    //Detect contours and store in memory
    cv::findContours(canny_output, contours, hierarchy, CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE, cv::Point(0,0));

    return contours;    
}

cv::Point initMatrix(cv::Point frameSize, vector<cv::Point>* textPos, double fontSize){
    double rows = double(frameSize.x);
    double cols = double(frameSize.y);
    char test = 100;
    string text(&test);


    // Needs to be tested
    //int cols_steps = double(frameSize.x)/fontSize;
    //int rows_steps = double(frameSize.y)/fontSize;


    int cols_steps = cols/fontSize;
    int rows_steps = rows/fontSize;
    
    int rows_iter = 0;
    int cols_iter = fontSize;
    int test1 = 0;

    for(int j = 0; j < cols_steps; j++){
        for(int i = 0; i < rows_steps ; i++){
            textPos->push_back(cv::Point(cols_iter,rows_iter));
            text = char(int(rng.uniform(0, 127)));
            //cout << "cols: " << cols_iter << " rows: " << rows_iter << endl;




            //cv::putText(frame, text, cv::Point(cols_iter,rows_iter), cv::FONT_HERSHEY_DUPLEX, 0.25, cv::Scalar(80, 100 , 30), 1, cv::LINE_8);
            rows_iter = rows_iter + fontSize;
            test1 += 1;
        }
        cols_iter = cols_iter + fontSize; 
        rows_iter = 0 ;

    }



}

cv::Point initMatrixMem(cv::Point frameSize, vector<element>* textInfo, double fontSize){
    double rows = double(frameSize.x);
    double cols = double(frameSize.y);
    char test = 100;
    string text(&test);


    // Needs to be tested
    //int cols_steps = double(frameSize.x)/fontSize;
    //int rows_steps = double(frameSize.y)/fontSize;


    int cols_steps = cols/fontSize;
    int rows_steps = rows/fontSize;
    
    int rows_iter = 0;
    int cols_iter = fontSize;
    int test1 = 0;

    for(int j = 0; j < cols_steps; j++){
        for(int i = 0; i < rows_steps ; i++){
            textInfo->push_back(element(cv::Point(cols_iter, rows_iter), cv::Scalar() ,string("s")));
            text = char(int(rng.uniform(0, 127)));
            rows_iter = rows_iter + fontSize;
            test1 += 1;
        }
        cols_iter = cols_iter + fontSize; 
        rows_iter = 0 ;

    }



}

void drawFrame(cv::Mat frame, vector<element>* textInfo, double font){
    double cols = double(frame.cols) ;
    double rows = double(frame.rows) ;
    char test = 100 ;
    string text(&test);

    int cols_steps = cols/font;
    int rows_steps = rows/font;
    
    int rows_iter = 0;
    int cols_iter = font;
    int test1 = 0;

    for(int j = 0; j < cols_steps; j++){
        for(int i = 0; i < rows_steps ; i++){

            cv::putText(frame, textInfo->at(test1).getText(), textInfo->at(test1).getPosition(), cv::FONT_HERSHEY_DUPLEX, 0.2, textInfo->at(test1).getColor(), 1, cv::LINE_8,false);
            rows_iter = rows_iter + font;
            test1 += 1;
        }
        cols_iter = cols_iter + font; 
        rows_iter = 0 ;

    }
    cv::namedWindow("filled rows", CV_WINDOW_AUTOSIZE);
    cv::imshow("filled rows", frame);

}



void updateFrame(vector<vector<cv::Point>> contours, vector<element>* textInfo, cv::Point textSize){




}
*/
