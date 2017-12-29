
#include "element.hpp"
#include "functions.hpp"


#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"




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

    //TODO: READ on about the mode varaible for cv::findContours
    cv::findContours(canny_output, contours, hierarchy, CV_RETR_TREE,CV_RETR_EXTERNAL, cv::Point(0,0));

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
            textInfo->push_back(element(cv::Point(cols_iter, rows_iter), cv::Scalar(0,255,0) ,string("s")));
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
    cv::waitKey(1000);

}



void updateFrame(vector<vector<cv::Point>> contours, vector<element>* textInfo, cv::Point textSize){

    int width = textSize.x;
    int height = textSize.y;
    vector<cv::Point> known();

    for(size_t i = 0; i < contours.size(); i++){
        cout << "New contour: " << i << endl;
        for(size_t j = 0; j < contours.at(i).size(); j++){
            //cout << "x: "  << contours.at(i).at(j).x << " y: " << contours.at(i).at(j).y << endl;
            int xx = contours.at(i).at(j).x;
            int yy = contours.at(i).at(j).y;



            for(size_t k = 0; k < textInfo->size(); k++){
               int x = textInfo->at(k).getPosition().x;
               int y = textInfo->at(k).getPosition().y;



//           if( (x + width > xx)  and  (y - height  < yy) and (xx - width < x) and (yy + height > y)){
           if( (xx - x) < width and (xx - x) > 0 and (y - yy) < height and (y - yy) > 0){

                    //cout << "testing:\n-------------\n";
/*
                    cout << "x+width=" << x + width << endl;
                    cout << "xx-width=" << xx - width << endl;
                    cout << "y - height=" << y - height << endl;
                    cout << "yy + height=" << yy + height << endl;
                    
*/
                    textInfo->at(k).setColor(cv::Scalar(255,0,0));
               }  
            }
        }
    } 
}

void threshold_callback(int pos, void* image){

    cv::Mat* casted = static_cast<cv::Mat*>(image);
    cv::Mat gray_image = *casted;
    cv::Mat canny_output;

    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierarchy;

    cv::Canny(gray_image, canny_output, pos, pos*2,3);
    cv::findContours(canny_output, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0,0));
    cv::Mat drawing = cv::Mat::zeros( canny_output.size(), CV_8UC3 );

    for(size_t i = 0; i < contours.size(); i++){
       cv::drawContours(drawing, contours, int(i), cv::Scalar(0,255,0), 2, 8, hierarchy, 0, cv::Point());
       
    }
    cv::namedWindow("Determine Threshold", CV_WINDOW_AUTOSIZE);
    cv::imshow("Determine Threshold", drawing);


}

void setThreshold(cv::Mat frame, int* thresh, int max_thresh){
    cv::Mat gray_image;
    cv::cvtColor(frame, gray_image, CV_BGR2GRAY);
    
    cv::namedWindow("source_image", CV_WINDOW_AUTOSIZE);
    cv::imshow("source_image", frame);

    createTrackbar(" Canny Threshold:","source_image", thresh, max_thresh, threshold_callback, &gray_image);
    int exit = 0;
    while(exit != 27){
        exit = cv::waitKey(0);
    }

}


