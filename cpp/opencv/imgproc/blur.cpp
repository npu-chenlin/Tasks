#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

String url = "../imgproc/test.jpg";
String windowName = "blur";
Mat DstPic;
void on_change(int kernelSize, void* img)
{
    Mat srcimg = *(Mat*) img;
    blur(srcimg, DstPic, Size(kernelSize*2+1, kernelSize*2+1));
    imshow(windowName, DstPic);
}
int main()
{
    int kernelSize = 2;
    namedWindow(windowName);
    Mat SrcPic = imread(url);
    resize(SrcPic,SrcPic,Size(640,480));
    createTrackbar("kernelSize",windowName,&kernelSize,7,on_change,&SrcPic);
    waitKey(0);
    return 0;
}
