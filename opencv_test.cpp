
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/core/utility.hpp"
#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h>

using namespace std;

// Globals 
cv::Mat image;
cv::Mat image_gray;
cv::Mat image_copy;

int thresh = 100;
int max_thresh = 255; 
cv::RNG rng(12345);

//globals for trackbars
int fontsize = 2 ; 
int max_fontsize = 255 ; 



void threshold_callback(int, void*);
void textsize_callback(int, void*);
void fillText(cv::Mat frame, double fontsize);

vector<vector<cv::Point>> getContours(cv::Mat frame);


cv::Point initMatrix(cv::Point frameSize, vector<cv::Point>* textPos, double fontSize);



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



cv::Point initMatrixMem(cv::Point frameSize, vector<element>* textPos, double fontSize);
void drawFrame(cv::Mat frame, vector<element>* textInfo);

int main( int argc, char** argv )
{
    
    string imageName("/home/henry/Documents/github_dev/matrixFrame/opencv_nic2.jpg"); // by default


    int exit = 0;
    if( argc > 1)
    {
        imageName = argv[1];
    }

    // Defining image objects

    //Loading Image to be Processed
    image = cv::imread(imageName.c_str(), cv::IMREAD_COLOR); // Read the file
    image_copy = image;
    vector<int> image_size(image.cols, image.rows);

    cout << "image cols: " << image_size.at(1) << " image rows: " << image_size.at(2) << endl;


    //Convert image to gray scale
    cv::cvtColor(image,image_gray,CV_BGR2GRAY);






    if( image.empty() )                      // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    // Creating Windows
 //   cv::namedWindow( "original image", cv::WINDOW_AUTOSIZE );


    fillText(image, 7);

    vector<cv::Point>* textPosition = new vector<cv::Point>();
    cout << " Entering Function \n";
    cv::Point charSize = initMatrix(cv::Point(50,50), textPosition, 10.0);
    cout << "Exciting Function \n";

    cout << textPosition->at(2).x << " " << textPosition->at(2).y << "\n";


   // cv::Point initMatrix(cv::Point frameSize, vector<cv::Point>* textPos, double fontSize);

    //charSize = initMatrix(cv::Point(50,50), textPosition, 10.0);


    // Memory allocated classs testing
    vector<element>* bar = new vector<element>();

    cout << "Entering Memory allocated class type funtion \n";
    cv::Point charSize2 = initMatrixMem(cv::Point(50,50), bar, 10.0);
    cout << "Exciting Memory allocated class type funtion \n";



   







    // Show images
//    cv::imshow( "original image", image );
//    cv::createTrackbar( " Canny threshold:", "original image", &thresh, max_thresh, threshold_callback );
//   cv::createTrackbar( " Font Size:", "original image", &fontsize, max_fontsize, textsize_callback );
//   threshold_callback( 0, 0 );  

    cout << "To exit press Escape \n";
    while(exit != 27){
        exit = cv::waitKey(0); // Wait for Escape to exit
    }
    return 0;
}

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
/*  Finds the contours in the frame, and returns
    the pixel locations of each contour.
    */
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
/*  frameSize:  Contains width and height of frame
    textPos:    Pointer which contains the positions of each location of text on frame
    return:     The width and height of 
    */
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
            textInfo->push_back(element(cv::Point(cols_iter, rows_iter), cv::Scalar()));
            text = char(int(rng.uniform(0, 127)));
            rows_iter = rows_iter + fontSize;
            test1 += 1;
        }
        cols_iter = cols_iter + fontSize; 
        rows_iter = 0 ;

    }



}

void drawFrame(cv::Mat frame, vector<element>* textInfo){


//cv::putText(frame, text, cv::Point(cols_iter,rows_iter), cv::FONT_HERSHEY_DUPLEX, 0.25, cv::Scalar(80, 100 , 30), 1, cv::LINE_8);


}