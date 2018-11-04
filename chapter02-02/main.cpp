#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
using namespace cv;
using namespace std;
Mat src;
vector<Point2f> src_corners;
vector<Point2f> dst_corners;


int i=0;
void mouseHandler(int event, int x, int y, int flags, void* data_ptr)
{
    if  ( event == EVENT_LBUTTONDOWN )
    {
        circle(src, Point(x,y),3,Scalar(0,255,255), 5, CV_AA);
        imshow("input image", src);
        if (i < 4)
        {
            i++;
            dst_corners.emplace_back(x,y);
            cout << x << y << endl;
        }
    }

}


int main(int argc, char** argv) {
    // load images
    src = imread("../images/billboard.png");
    if (!src.data) {
        printf("could not load image...\n");
        return -1;
    }
    // show images
    namedWindow("input image", CV_WINDOW_AUTOSIZE);
    imshow("input image", src);
    Mat replaceImg = imread("../images/lenna.jpg");
    imshow("adv content", replaceImg);    // 定义两个平面上四个角坐标

    // 原图像平面四点坐标
    src_corners.emplace_back(0, 0);
    src_corners.emplace_back(replaceImg.cols, 0);
    src_corners.emplace_back(0, replaceImg.rows);
    src_corners.emplace_back(replaceImg.cols, replaceImg.rows);

    // 目标平面四个角坐标
    setMouseCallback("input image", mouseHandler);
    waitKey(0);

    Mat h = findHomography(src_corners, dst_corners);
    Mat output_img;
    warpPerspective(replaceImg, output_img, h, src.size());// create mask
    Mat m1 = Mat::zeros(replaceImg.size(), CV_8UC1);
    m1 = Scalar(255);
    Mat mask_output;
    warpPerspective(m1, mask_output, h, src.size());
    imshow("input image", mask_output);    // use mask
    Mat result1;
    add(output_img, output_img, result1, mask_output);
    Mat result2;
    bitwise_not(mask_output, mask_output);
    add(src, result1, result2, mask_output);    // put them together
    Mat result;
    add(result1, result2, result);
    imshow("input image", result);
    waitKey(0);
    return 0;
}

