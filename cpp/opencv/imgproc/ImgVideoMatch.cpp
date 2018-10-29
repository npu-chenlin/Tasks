#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Size size(800,1000);
int main()
{
    Mat image01 = imread("../imgproc/3.jpg");
    resize(image01,image01,size);
    //灰度图转换
    Mat image1;
    cvtColor(image01, image1, CV_RGB2GRAY);

    //提取特征点
    SurfFeatureDetector surfDetector(700);  // 海塞矩阵阈值，在这里调整精度，值越大点越少，越精准
    vector<KeyPoint> keyPoint1;
    surfDetector.detect(image1, keyPoint1);
    //特征点描述，为下边的特征点匹配做准备
    SurfDescriptorExtractor SurfDescriptor;
    Mat imageDesc1;
    SurfDescriptor.compute(image1, keyPoint1, imageDesc1);
    FlannBasedMatcher matcher;
    vector<vector<DMatch> > matchPoints;
    vector<DMatch> GoodmatchPoints;

    vector<Mat> train_desc(1, imageDesc1);
    matcher.add(train_desc);
    matcher.train();

    VideoCapture camara(0);
    Mat inputImg , inputImgGray ,descriptor ,result_match;
    vector<KeyPoint> keyPoint2;
    while(char(waitKey(1)) != 'q')
    {
        GoodmatchPoints.clear();
        camara >> inputImg ;
        resize(inputImg,inputImg,size);
        cvtColor(inputImg,inputImgGray,CV_RGB2GRAY);
        surfDetector.detect(inputImgGray,keyPoint2);
        SurfDescriptor.compute(inputImgGray,keyPoint2,descriptor);
        matcher.knnMatch(descriptor, matchPoints ,2);
        for(auto i : matchPoints)
        {
            if(i[0].distance < 0.7 * i[1].distance)
                GoodmatchPoints.push_back(i[0]);
        }
        cout<<GoodmatchPoints.size()<<endl;
        if(GoodmatchPoints.size()>3)
        {
            drawMatches(inputImg, keyPoint2, image01, keyPoint1, GoodmatchPoints, result_match);
            imshow("result_match ", result_match);
        }
        else
            imshow("result_match ", inputImg);

    }
    return 0;
}
