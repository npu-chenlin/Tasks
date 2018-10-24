#include <opencv2/opencv.hpp>   
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    Mat img5;
    img5.create(2, 2, CV_8UC3);
    img5<<1,2,3,4;

    Mat img6 = Mat::zeros(4, 4, CV_8UC3);
    cout << img6 << endl;

    Mat img7 = img6.clone();
    cout << img7 << endl;

    Mat img8;
    img6.copyTo(img8);
    cout << img8 << endl;
    
    //下面都是浅拷贝，指针指向同一个实例
    Mat img9 = img8;
    Mat img10(img8);

    waitKey(0);
    return 0;
}