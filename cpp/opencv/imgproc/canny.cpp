#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

String url = "../imgproc/test.jpg";

int main()
{
    Mat SrcPic = imread(url);
    resize(SrcPic,SrcPic,Size(640,480));
    imshow("Src Pic", SrcPic);
    Mat DstPic, edge, grayImage;

    DstPic.create(SrcPic.size(), SrcPic.type());

    cvtColor(SrcPic, grayImage, COLOR_BGR2GRAY);
    //先使用3*3内核来降噪
    blur(grayImage, edge, Size(3, 3));
    //运行canny算子
    Canny(edge, edge, 3, 9, 3);
    imshow("边缘提取效果", edge);
    waitKey();
    return 0;
}
