#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/photo/photo.hpp>
#include <iostream>
using namespace cv;

String url = "../imgproc/test.jpg";

int main()
{
    Mat original = imread(url);
    resize(original,original,Size(640,480));
    namedWindow("My original");
    imshow("My original", original);
    Mat gray = original;
    cvtColor(gray, gray, CV_RGB2GRAY);//灰度化

    int thresh_size = (100 / 4) * 2 + 1; // ???怎么确定
    adaptiveThreshold(gray, gray, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY_INV, thresh_size, thresh_size / 3);

    vector<vector<Point> > contours;
    findContours(gray, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE); //找轮廓
    vector<vector<Point>> contours1;
    for (int i = 0; i < contours.size(); ++i)
    {
        contours1.push_back(contours[i]);
    }

    Mat hole(gray.size(), CV_8U, Scalar(0)); //遮罩图层
    drawContours(hole, contours1, -1, Scalar(255), CV_FILLED); //在遮罩图层上，用白色像素填充轮廓，得到MASK
    namedWindow("My hole");
    imshow("My hole", hole);
    Mat crop(original.rows, original.cols, CV_8UC3);
    original.copyTo(crop, hole);//将原图像拷贝进遮罩图层
    namedWindow("My warpPerspective");
    imshow("My warpPerspective", crop);
    waitKey(0);
}
