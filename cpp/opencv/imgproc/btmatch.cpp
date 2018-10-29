#include <opencv2/highgui.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <iostream>  

using namespace cv;
using namespace std;


int main()
{
    Mat image01 = imread("../imgproc/2.jpg");    //右图
    Mat image02 = imread("../imgproc/1.jpg");    //左图
    resize(image01,image01,Size(640,480));
    resize(image02,image02,Size(640,480));
    //灰度图转换  
    Mat image1, image2;
    cvtColor(image01, image1, CV_RGB2GRAY);
    cvtColor(image02, image2, CV_RGB2GRAY);


    //提取特征点    
    SurfFeatureDetector surfDetector(800);  // 海塞矩阵阈值，在这里调整精度，值越大点越少，越精准 
    vector<KeyPoint> keyPoint1, keyPoint2;
    surfDetector.detect(image1, keyPoint1);
    surfDetector.detect(image2, keyPoint2);

    //特征点描述，为下边的特征点匹配做准备    
    SurfDescriptorExtractor SurfDescriptor;
    Mat imageDesc1, imageDesc2;
    SurfDescriptor.compute(image1, keyPoint1, imageDesc1);
    SurfDescriptor.compute(image2, keyPoint2, imageDesc2);

    BruteForceMatcher<L2<float>> matcher;
    vector<DMatch> MatchPoints;
    vector<DMatch> GoodMatchPoints;
    matcher.match(imageDesc1,imageDesc2,MatchPoints);

//    vector<Mat> train_desc(1, imageDesc1);
//    matcher.add(train_desc);
//    matcher.train();

//    matcher.knnMatch(imageDesc2, MatchPoints ,2);
    cout << "total match points: " << MatchPoints.size() << endl;
//    // Lowe's algorithm,获取优秀匹配点
//    for (int i = 0; i < MatchPoints.size(); i++)
//    {
//        if (MatchPoints[i][0].distance < 0.5 * MatchPoints[i][1].distance)
//        {
//           GoodMatchPoints.push_back(MatchPoints[i][0]);
//        }
//    }
    auto minDistance = min_element(MatchPoints.begin(),MatchPoints.end());
    for(auto i : MatchPoints)
    {
        if(i.distance < 2*(minDistance->distance))
            GoodMatchPoints.push_back(i);
    }
    Mat result_match;
    drawMatches(image01, keyPoint1,image02, keyPoint2, GoodMatchPoints, result_match);
    imshow("result_match ", result_match);
    waitKey();
    return 0;
}
