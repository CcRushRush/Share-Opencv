#include <opencv2/opencv.hpp>
#include <math.h>
#include <iostream>
#include <stack>
#include <cv.h>
#include <highgui.h>
using namespace cv;
using namespace std;
int main(int argc, char** argv) {
    int i =0;
    Mat src = imread("../chapter04-01/lab/sample4.png");
    if (src.empty()) {
        printf("could not load image...\n");
        return -1;
    }
    namedWindow("input image", CV_WINDOW_AUTOSIZE);
    imshow("input image", src);
    Mat gray, binary;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
    //imshow("binary",binary);
    vector<vector<Point>> contours;
    vector<Vec4i> hireachy;
    findContours(binary,contours,hireachy,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE,Point(0,0));
    for (size_t a = 0; a < contours[0].size(); a++)
    {
        line(src, contours[0][a], contours[0][(a + 1) % contours[0].size()], Scalar(0, 255, 0), 1, 8);
    }
    //imshow("linehello",src);
    //printf("hello");
    Mat result = Mat::zeros(src.size(), CV_8UC3);
    for (size_t t = 0; t < contours.size(); t++) {
        double area = contourArea(contours[t]);

        if (area < 100) continue;
        RotatedRect rect = minAreaRect(contours[t]);
        float w = rect.size.width;
        float h = rect.size.height;
        float rate = min(w, h) / max(w, h);
        char *s;
        CvPoint pt;
        if (rate > 0.85 && w < src.cols/4 && h<src.rows/4) {

            printf("angle : %.2f\n", rect.angle);
            pt = rect.center;
            circle(src,pt,4,Scalar(0,0,255),2 );
            drawContours(src, contours, static_cast<int>(t), Scalar(0, 0, 255), 2, 8);
            sprintf(s,"%f", rect.angle);
            string ss(s);
            putText(src,ss,pt,FONT_HERSHEY_SIMPLEX,1,Scalar(255,23,0),4,8);//在图片上写文字
        }
    }
    imshow("src", src);
    waitKey(0);
    return 0;
}