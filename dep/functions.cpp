
#include "element.hpp"
#include "functions.hpp"
using namespace std;

vector<vector<cv::Point>> getContours(cv::Mat frame, int thresh){

    cv::Mat canny_output;
    cv::Mat image_gray;
    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierarchy;
    cv::cvtColor(frame,image_gray,CV_BGR2GRAY);
    
    //Canny the image
    cv::Canny(image_gray, canny_output, thresh, thresh*2,3);

    //Detect contours and store in memory
    cv::findContours(canny_output, contours, hierarchy, CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE, cv::Point(0,0));

    return contours;    
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

    int width = textSize.x ;
    int height = textSize.y ;

    for(size_t i = 0; i < contours.size(); i++){
        cout << "New contour: " << i << endl;
        for(size_t j = 0; j < contours.at(i).size(); j++){
            cout << "x: "  << contours.at(i).at(j).x << " y: " << contours.at(i).at(j).y << endl;
            int xx = contours.at(i).at(j).x;
            int yy = contours.at(i).at(j).y;


            for(size_t k = 0; k < textInfo->size(); k++){
               int x = textInfo->at(k).getPosition().x;
               int y = textInfo->at(k).getPosition().y;

               if( (x + width) > xx and (y + height) > yy and (xx - width) < x and (yy - height) < y){
                   cout << "match" << endl;
                   cout << "countours: " << xx << "," << yy << endl;
                   cout << "text: " << x << "," << y << endl;
               }  





            }





        }
    } 
   





}


