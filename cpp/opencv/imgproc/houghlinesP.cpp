#include<opencv2/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc.hpp>

#include<iostream>
using namespace std;
using namespace cv;


String url = "/home/chenlin/my_progs/Tasks/cpp/opencv/imgproc/test.jpg";
int main()
{
    Mat srcImage = imread(url);
    resize(srcImage,srcImage,Size(640,480));

    Mat midImage, dstImage;

    Canny(srcImage, midImage, 50, 200, 3);
    cvtColor(midImage, dstImage, CV_GRAY2BGR);

    vector<Vec4i> lines;
    //与HoughLines不同的是，HoughLinesP得到lines的是含有直线上点的坐标的，所以下面进行划线时就不再需要自己求出两个点来确定唯一的直线了
    HoughLinesP(midImage, lines, 1, CV_PI / 180, 80, 50,10);//注意第五个参数，为阈值

    //依次画出每条线段
    for (int i = 0; i < lines.size(); i++)
    {
        Vec4i l = lines[i];

        line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255)); //Scalar函数用于调节线段颜色
    }
    imshow("边缘检测后的图", midImage);
    imshow("最终效果图", dstImage);
    waitKey();
    return 0;
}
