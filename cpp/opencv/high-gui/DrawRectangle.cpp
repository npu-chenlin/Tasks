#include <opencv2/video/tracking.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <ctype.h>
#define WINDOW_NAME "draw rectangle"

using namespace cv;
using namespace std;

bool g_bDrawBox = false;
Rect g_rectangle;
RNG rng;
Scalar color;
void on_MounseHandle(int event,int x, int y,int flags, void* param)
{
    Mat img = *(Mat*) param;
    switch(event)
    {
    case EVENT_MOUSEMOVE:
    {
        if(g_bDrawBox)
        {
            Mat temp;
            img.copyTo(temp);
            g_rectangle.width = x - g_rectangle.x;
            g_rectangle.height = y - g_rectangle.y;
            Rect tempRect = g_rectangle;
            if(tempRect.width < 0)
            {
                tempRect.x += tempRect.width;
                tempRect.width *=-1;
            }
            if(tempRect.height < 0)
            {
                tempRect.y += tempRect.height;
                tempRect.height *=-1;
            }
            cout<<color<<endl;
            rectangle(temp,tempRect,color);
            imshow(WINDOW_NAME,temp);
        }
    }
        break;
    case EVENT_LBUTTONDOWN:
    {
        g_bDrawBox = true;
        g_rectangle = Rect(x,y,0,0);
        color = Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255));
    }
        break;
    case EVENT_LBUTTONUP:
    {
        g_bDrawBox = false;
        if(g_rectangle.width < 0)
        {
            g_rectangle.x += g_rectangle.width;
            g_rectangle.width *=-1;
        }
        if(g_rectangle.height < 0)
        {
            g_rectangle.y += g_rectangle.height;
            g_rectangle.height *=-1;
        }
        rectangle(img,g_rectangle,color);
        imshow(WINDOW_NAME,img);
    }
        break;
    }
}

int main(int argc,char** argv)
{
    namedWindow(WINDOW_NAME);
    Mat srcImg(600,800,CV_8UC3),tempImg;
    srcImg.copyTo(tempImg);
    setMouseCallback(WINDOW_NAME,on_MounseHandle,(void*)& tempImg);
    imshow(WINDOW_NAME,tempImg);
    waitKey(0);
    return 0;
}
