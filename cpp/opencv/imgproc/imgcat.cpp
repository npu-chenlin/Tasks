#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main()
{
    Mat image02 = imread("../imgproc/2.jpg");    //右图
    Mat image01 = imread("../imgproc/1.jpg");    //左图
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

    FlannBasedMatcher matcher;
    vector<vector<DMatch> > matchPoints;
    vector<DMatch> GoodmatchPoints;

    vector<Mat> train_desc(1, imageDesc2);
    matcher.add(train_desc);
    matcher.train();

    matcher.knnMatch(imageDesc1, matchPoints ,2);
    cout << "total match points: " << matchPoints.size() << endl;
    // Lowe's algorithm,获取优秀匹配点
    for (int i = 0; i < matchPoints.size(); i++)
    {
        if (matchPoints[i][0].distance < 0.5 * matchPoints[i][1].distance)
        {
           GoodmatchPoints.push_back(matchPoints[i][0]);
        }
    }
    vector<Point2f> goodMatchPointImg1 ,goodMatchPointImg2;
    for(auto i : GoodmatchPoints)
    {
        goodMatchPointImg1.push_back(keyPoint1[i.queryIdx].pt);
        goodMatchPointImg2.push_back(keyPoint2[i.trainIdx].pt);
    }
    Mat transformMatrix = findHomography(goodMatchPointImg1,goodMatchPointImg2);

    Mat imageTransform1;
    warpPerspective(image01, imageTransform1, transformMatrix,Size(640,480));
    //warpPerspective(image01, imageTransform2, adjustMat*homo, Size(image02.cols*1.3, image02.rows*1.8));
    Mat dstimg(640,480,CV_8UC3);
    addWeighted(imageTransform1,0.5,image02,0.5,0,dstimg);
    imshow("ri",dstimg );

//    Mat result_match;
//    drawMatches(image01, keyPoint1, image02, keyPoint2, GoodmatchPoints, result_match);
//    imshow("result_match ", result_match);
    waitKey();
    return 0;
}
