#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/core.hpp>

#include <iostream>
#include <vector>
using namespace cv;
using namespace std;
int contrast = 100;
int bright = 0;
int main(int argc,char** argv)
{
    namedWindow("img");
    vector<Mat> channels;
    Mat tempImg = imread("../core/1.jpg");
    Mat srcImg;
    resize(tempImg,srcImg,Size(640,480));
    createTrackbar("Contrast","img",&contrast,500,contrastandbright,&srcImg);
    createTrackbar("bright","img",&bright,255,contrastandbright,&srcImg);
    waitKey(0);
    return 0;
}
void contrastandbright(int value,void* img)
{
    Mat im = *(Mat*) img;
    for(int i = 0 ; i<im.rows ; i++)
        for(int j = 0 ; j<im.cols ; j++)
            for(int k = 0 ; k < 3;k++)
                im.at<Vec3b>(i,j)[k] = stuc
}
