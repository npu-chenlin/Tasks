#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;
int main()
{
    Mat SrcPic = imread("/home/chenlin/my_progs/Tasks/cpp/opencv/basic-image-process/test.jpg");
    resize(SrcPic,SrcPic,Size(640,480));
    imshow("Src Pic", SrcPic);
    Mat DstPic;
    blur(SrcPic, DstPic, Size(7, 7));
    imshow("均值模糊效果图", DstPic);
    waitKey(0);
    return 0;
}
