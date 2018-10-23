#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define WINDOW_NAME "Alpha"

using namespace cv;
using namespace std;

Mat tempImg;
Mat srcImg1;
Mat srcImg2;
Mat dstImg;

const int MaxAlphaValue = 100;
int AlphaValueSlider;
double dAlphaValue;
double dBetaValue;

void on_Trackbar(int,void*)
{
    dAlphaValue = (double) AlphaValueSlider/MaxAlphaValue;
    dBetaValue = 1 - dAlphaValue;
    addWeighted(srcImg1,dAlphaValue,srcImg2,dBetaValue,0,dstImg);
    imshow(WINDOW_NAME,dstImg);
}

int main(int argc,char** argv)
{
    namedWindow(WINDOW_NAME,1);
    tempImg = imread("../high-gui/1.jpg");
    resize(tempImg,srcImg1,Size(640,480));
    tempImg = imread("../high-gui/2.jpg");
    resize(tempImg,srcImg2,Size(640,480));
    AlphaValueSlider = 70;
    createTrackbar("mixed",WINDOW_NAME,&AlphaValueSlider,MaxAlphaValue,on_Trackbar);
    waitKey(0);
    return 0;
}
