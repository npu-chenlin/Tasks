#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
int main()
{
    Mat SrcPic = imread("/home/chenlin/my_progs/Tasks/cpp/opencv/basic-image-process/test.jpg");
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15)); //getStructuringElement函数返回的是指定形状和尺寸的结构元素
    resize(SrcPic,SrcPic,Size(640,480));
    imshow("Src Pic", SrcPic);
    Mat DstPic;
    erode(SrcPic, DstPic, element); //腐蚀操作
    imshow("腐蚀效果图", DstPic);
    waitKey(0);
    return 0;
}
