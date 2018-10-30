#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
String url = "../imgproc/1540865910.jpg";
int main()
{
    Mat basePic = imread(url);
    Mat basePic_grayScale;
    if(!basePic.data)
    {cout<<"no pic"<<endl;return 0;}
    cvtColor(basePic,basePic_grayScale,CV_RGB2GRAY);
    imshow("basePic",basePic_grayScale);
    Mat element_erode = getStructuringElement(MORPH_RECT, Size(7, 7)); //getStructuringElement函数返回的是指定形状和尺寸的结构元素
    Mat element_dilate = getStructuringElement(MORPH_RECT, Size(15, 15));

    VideoCapture camara(0);

    Mat inputImg ,inputImg_grayScale ,diffImg;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarcy;

    while(char(waitKey(1)) != 'q')
    {
        camara >> inputImg;
        cvtColor(inputImg,inputImg_grayScale,CV_RGB2GRAY);
        imshow("inputImg",inputImg_grayScale);
        absdiff(inputImg_grayScale,basePic_grayScale,diffImg);
        threshold(diffImg, diffImg, 45, 255, CV_THRESH_BINARY);
        erode(diffImg,diffImg,element_erode);
        dilate(diffImg,diffImg,element_dilate);
        findContours(diffImg, contours, hierarcy, CV_RETR_EXTERNAL, CHAIN_APPROX_NONE); //查找轮廓
        vector<Rect> boundRect(contours.size()); //定义外接矩形集合
        int x0=0, y0=0, w0=0, h0=0;
        for(int i=0; i<contours.size(); i++)
        {
            boundRect[i] = boundingRect((Mat)contours[i]); //查找每个轮廓的外接矩形
            x0 = boundRect[i].x;  //获得第i个外接矩形的左上角的x坐标
            y0 = boundRect[i].y; //获得第i个外接矩形的左上角的y坐标
            w0 = boundRect[i].width; //获得第i个外接矩形的宽度
            h0 = boundRect[i].height; //获得第i个外接矩形的高度
            rectangle(inputImg, Point(x0, y0), Point(x0+w0, y0+h0), Scalar(0, 255, 0), 2, 8); //绘制第i个外接矩形
        }
        imshow("outline", inputImg);
    }
    return 0;
}
