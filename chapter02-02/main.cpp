#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
//! [includes]

//! [namespace]
using namespace cv;
//! [namespace]

using namespace std;

int main(int argc, char** argv) {
    Mat image = imread( "../images/lenna.jpg" ); // Read the file
    Mat image2 = imread("../images/billboard.png");

    if( image.empty() ) {                    // Check for invalid input
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    if( image2.empty() ) {                    // Check for invalid input
        cout <<  "Could not open or find the image2" << std::endl ;
        return -1;
    }

    Mat edges;
    cvtColor(image2, edges, CV_BGR2GRAY);//彩色转换成灰度
    blur(edges, edges, Size(7, 7));//模糊化
    Canny(edges, edges, 0, 30, 3);//边缘化
    imshow( "lenna", image );
    imshow("billboard", image2);
    imshow("billboard edges", edges);
    waitKey(0); // Wait for a keystroke in the window
    //! [wait]
    return 0;
}