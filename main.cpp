
#include "./dep/element.hpp"
#include "./dep/functions.hpp"

using namespace std;



int main( int argc, char** argv )
{
    
    string imageName("/home/henry/Documents/github_dev/matrixFrame/images/v.jpg"); // by default
    cv::Mat image;
    cv::Mat orig_image;

    double fontsize = 6.0;


    int exit = 0;
    if( argc > 1)
    {
        imageName = argv[1];
    }

    // Defining image objects

    //Loading Image to be Processed
    image = cv::imread(imageName.c_str(), cv::IMREAD_COLOR); // Read the file
    orig_image = cv::imread(imageName.c_str(), cv::IMREAD_COLOR); 

    cv::Mat drawing = cv::Mat::zeros( image.size(), CV_8UC3 );



    if( image.empty() )                      // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    int* thresh = new int(255);
    setThreshold(image,thresh,255 );

    cout << *thresh << endl;




    vector<element>* bar = new vector<element>();

    cv::Point charSize2 = initMatrixMem(cv::Point(image.rows,image.cols), bar, fontsize);

    drawFrame(drawing,bar, fontsize);



    vector<vector<cv::Point>> contours = getContours(orig_image, thresh);
    
    updateFrame(contours, bar, cv::Point(6,6));
    drawFrame(drawing,bar, fontsize);
    cv::imwrite("./output.jpg", drawing);


    cout << "To exit press Escape \n";
    while(exit != 27){
        exit = cv::waitKey(0); // Wait for Escape to exit
    }



    return 0;
}

