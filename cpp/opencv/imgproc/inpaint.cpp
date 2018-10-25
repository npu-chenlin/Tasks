#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/photo/photo.hpp>
#include <iostream>
using namespace cv;

Point ptL, ptR; //鼠标画出矩形框的起点和终点
Mat imageSource, imageSourceCopy;
Mat ROI,Gray; //原图需要修复区域的ROI

void OnMouse(int event, int x, int y, int flag, void *ustg);
String url = "../imgproc/test.jpg";
//鼠标圈定区域阈值处理+Mask膨胀处理
int main()
{
    imageSource = imread(url);
    resize(imageSource,imageSource,Size(640,480));
    imshow("原图", imageSource);
    setMouseCallback("原图", OnMouse);
    waitKey(0);
}
void OnMouse(int event, int x, int y, int flag, void *ustg)
{
    if (event == CV_EVENT_LBUTTONDOWN)
    {
        ptL = Point(x, y);
        ptR = Point(x, y);
       std::cout<<ptL<<std::endl;
    }
    if (flag == 33)
    {
        ptR = Point(x, y);
        imageSourceCopy = imageSource.clone();
        rectangle(imageSourceCopy, ptL, ptR, Scalar(255, 0, 0));
        imshow("原图", imageSourceCopy);
    }
    if (event == CV_EVENT_LBUTTONUP)
    {
        if (ptL != ptR)
        {
            ROI = imageSource(Rect(ptL, ptR));
            waitKey();
        }
    }
    //单击鼠标右键开始图像修复
    if (event == CV_EVENT_RBUTTONDOWN)
    {
        imageSourceCopy = ROI.clone();
        Mat imageGray;
        cvtColor(ROI, imageGray, CV_RGB2GRAY); //转换为灰度图
        Mat imageMask = Mat(ROI.size(), CV_8UC1, Scalar::all(0));
        //通过阈值处理生成Mask
        adaptiveThreshold(imageGray, imageMask,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY,51,0);
        Mat Kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        dilate(imageMask, imageMask, Kernel);  //对Mask膨胀处理
        inpaint(ROI, imageMask, ROI, 9, INPAINT_TELEA);  //图像修复
        imshow("原图", imageSource);
    }
}
