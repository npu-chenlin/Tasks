#include <opencv2/video/tracking.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <ctype.h>
#define WINDOW_NAME "Alpha"

using namespace cv;
using namespace std;

Mat g_srcImg1;
Mat g_srcImg2;
Mat g_dstImg;

const int g_nMaxAlphaValue = 100;
int g_nAlphaValueSlider;
double g_dAlphaValue;
double g_dBetaValue;

void on_Trackbar(int,void*)
{
    g_dAlphaValue = (double) g_nAlphaValueSlider/g_nMaxAlphaValue;
    g_dBetaValue = 1 - g_dAlphaValue;
    addWeighted(g_srcImg1,g_dAlphaValue,g_srcImg2,g_dBetaValue,0,g_dstImg);
    imshow(WINDOW_NAME,g_dstImg);
}

int main(int argc,char** argv)
{
    namedWindow(WINDOW_NAME,1);
    g_srcImg1 = imread("C:\\Users\\chenll\\Desktop\\1.png");
    g_srcImg2 = imread("C:\\Users\\chenll\\Desktop\\2.png");
    g_nAlphaValueSlider = 70;
    createTrackbar("mixed",WINDOW_NAME,&g_nAlphaValueSlider,g_nMaxAlphaValue,on_Trackbar);
    waitKey(0);
    return 0;
}
