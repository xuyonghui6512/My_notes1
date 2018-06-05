//
// Created by xuxuxu on 18-4-5.
//
#include"image_handle.h"
#include <opencv2/opencv.hpp>
namespace mybar_code{

    void Image_handle::Image_sharp(Mat& _img,Mat& _output)
{
    Mat srcimg = _img;

    Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);

    cv::filter2D(srcimg, _output, srcimg.depth(), kernel);
}
    Mat Image_handle::turn90degree(Mat &srcimg) {
        Mat src=srcimg.clone();
        Mat srcCopy =src.clone();
        transpose(src, srcCopy);
        flip(srcCopy, srcCopy, 1);
        return srcCopy;
    }
    Mat Image_handle::Best_Image_Choose(Mat &A, Mat &B,int& key)
    {
        int countA=0;
        int countB=0;
        for(int i=0;i<A.rows-5;i=i+6)
        {
            uchar* data=A.ptr<uchar>(i);
            for(int j=0;j<A.cols;j++)
            {
                if(data[j]==255)
                    countA++;
            }
        }
        for(int i=0;i<B.rows-5;i=i+6)
        {
            uchar* data=B.ptr<uchar>(i);
            for(int j=0;j<B.cols;j++)
            {
                if(data[j]==255)
                    countB++;
            }
        }
        if(countA>countB)
        {
            key=0;
            return A;

        }
        else {
            key=1;
            return B;
        }

    }
}