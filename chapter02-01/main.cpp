#include <opencv2/opencv.hpp>
#include<sys/time.h>
#include<unistd.h>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;
//中心标记十字
void drawCross(Mat img,CvPoint point,CvScalar color,int size, int thickness){
    line(img,cvPoint(point.x-size/2,point.y),cvPoint(point.x+size/2,point.y),color,thickness,8,0);
    line(img,cvPoint(point.x,point.y-size/2),cvPoint(point.x,point.y+size/2),color,thickness,8,0);
    return;
}
int main( ) {
    VideoCapture capture(0);
    Mat edges;
    CvPoint point;
    struct  timeval start;
    struct  timeval end;
    unsigned long diff;
    gettimeofday(&start,NULL);
    while(1) {
        gettimeofday(&end,NULL);
        diff = (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
        gettimeofday(&start,NULL);
        Mat frame; //定义一个Mat变量，用于存储每一帧的图像

        capture >> frame; //读取当前帧
        if (frame.empty()) {
            printf("--(!) No captured frame -- Break!"); //break;
        } else {
            cvtColor(frame, edges, CV_BGR2GRAY);//彩色转换成灰度
            point = Point(frame.cols/2,frame.rows/2);
            circle(frame,point,25,Scalar(0,255,255),2 );
            circle(edges,point,25,Scalar(0,255,255),2 );
            drawCross(frame,point,Scalar(0,0,255),20,2);
            drawCross(edges,point,Scalar(0,0,255),20,2);
            putText(edges, to_string(diff), Point(20,edges.rows-50), FONT_HERSHEY_COMPLEX, 1, Scalar(0,255,255), 1);
            imshow("原图", frame); //显示当前帧
            imshow("读取被边缘后的视频", edges); //显示当前帧
        }
        waitKey(30); //延时30ms
    }
    return 0;
}
