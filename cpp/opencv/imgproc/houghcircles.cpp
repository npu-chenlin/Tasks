#include<opencv2/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc.hpp>

#include<iostream>
using namespace std;
using namespace cv;

String url = "../imgproc/test.jpg";
int main()
{
    Mat srcImage = imread(url);
    resize(srcImage,srcImage,Size(640,480));
    cvtColor(srcImage,srcImage,CV_BGR2GRAY);
    vector<Vec3f> circles;
    HoughCircles(srcImage, circles,CV_HOUGH_GRADIENT,1.5, 10, 200, 100, 0, 0);//注意第五个参数，为阈值
    cout<<circles.size()<<endl;
    //依次画出每条线段
    for (int i = 0; i < circles.size(); i++)
    {
        Vec3f cir = circles[i];
        circle(srcImage, Point(cir[0], cir[1]), cir[2], Scalar(186, 88, 255)); //Scalar函数用于调节线段颜色
    }
    imshow("最终效果图", srcImage);
    waitKey();
    return 0;
}
