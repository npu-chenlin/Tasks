#include<opencv2/opencv.hpp>   
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

String url = "../imgproc/test.jpg";
int main()
{
    Mat img = imread(url);
    resize(img,img,Size(640,480));
    imshow("原始图", img);
    Mat dst;
    cvtColor(img, img, CV_RGB2GRAY);
    imshow("灰度图", img);
    equalizeHist(img, dst);

    imshow("直方图均衡化", dst);

    waitKey(0);

}