#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

String url = "../imgproc/test.jpg";

void on_CornerHarris(int, void*);//回调函数  
Mat SrcPic1 , SrcPic;
int main(int argc, char** argv)
{

    int thresh = 0;
    int max_thresh = 255;
    Mat grayImage,threshImage;
    
    SrcPic = imread(url);
    resize(SrcPic,SrcPic,Size(640,480));
    SrcPic1 = SrcPic.clone();

    cvtColor(SrcPic,grayImage,CV_RGB2GRAY);
    adaptiveThreshold(grayImage, threshImage,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY_INV,17,10);
    imshow("角点检测", SrcPic);
    //创建窗口和滚动条
    namedWindow("角点检测", CV_WINDOW_AUTOSIZE);
    createTrackbar("阈值: ", "角点检测", &thresh, max_thresh, on_CornerHarris,&threshImage);

    waitKey(0);
    return(0);
}


void on_CornerHarris(int thresh, void* threshImage)
{
    Mat local_srcPic = SrcPic.clone();
    Mat dstImage;//目标图  
    Mat normImage;//归一化后的图  
    Mat scaledImage;//线性变换后的八位无符号整型的图  

    //进行角点检测  
    //第三个参数表示邻域大小，第四个参数表示Sobel算子孔径大小，第五个参数表示Harris参数
    cornerHarris(*(Mat*) threshImage, dstImage, 2, 3, 0.04, BORDER_DEFAULT);
    // 归一化与转换  
    normalize(dstImage, normImage, 0, 255, NORM_MINMAX);

    convertScaleAbs(normImage, scaledImage);//!!!!!将归一化后的图线性变换成8位无符号整型
   // 将检测到的，且符合阈值条件的角点绘制出来
    for (int j = 0; j < normImage.rows; j++)
    {
        for (int i = 0; i < normImage.cols; i++)
        {
            if ((int)normImage.at<float>(j, i) > thresh+50)
            {
                circle(local_srcPic, Point(i, j), 5, Scalar(10, 10, 255), 2, 8, 0);
                circle(scaledImage, Point(i, j), 5, Scalar(0, 10, 255), 2, 8, 0);
            }
        }
    }
    
    imshow("角点检测", local_srcPic);
    imshow("角点检测2", scaledImage);

}
