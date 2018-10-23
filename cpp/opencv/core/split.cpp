#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/core.hpp>

#include <iostream>
#include <vector>
using namespace cv;
using namespace std;
// opencv uses BGR instead of RGB
int main(int argc,char** argv)
{
    namedWindow("B");
    vector<Mat> channels;
    Mat tempImg = imread("../core/1.jpg");
    Mat srcImg;
    resize(tempImg,srcImg,Size(640,480));
    split(srcImg,channels);
    cout<<channels.size()<<endl;
    imshow("B",channels.at(0));
    waitKey(0);
    return 0;
}
