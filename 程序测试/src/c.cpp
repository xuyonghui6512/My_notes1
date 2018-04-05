 


#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()

    {    

       Mat lena = imread("/home/xuxuxu/b/二维码测试图片/16.jpg");
     Mat sharpenedLena;

        Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);

       cv::filter2D(lena, sharpenedLena, lena.depth(), kernel);

 
     imshow("lena", lena);
     imshow("sharpened lena", sharpenedLena);
     cvWaitKey();
     return 0;
 }
