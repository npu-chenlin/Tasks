#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

String url = "../imgproc/test.jpg";

int main(int argc, char *argv[])
{
    Mat img = imread(url,CV_LOAD_IMAGE_GRAYSCALE);
    resize(img,img,Size(640,480));
    int th = 100;
    //globally binaryzation
    Mat global;
    threshold(img,global,th,255,CV_THRESH_BINARY);

    //local binaryzation
    int blockSize = 25;
    int coustVal = 10;
    Mat local;
    adaptiveThreshold(img,local,255,CV_ADAPTIVE_THRESH_MEAN_C,CV_THRESH_BINARY_INV,blockSize,coustVal);
    imshow("origin",img);
    imshow("global",global);
    imshow("local",local);
    waitKey(0);

    return 0;
}
