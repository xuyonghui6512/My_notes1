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
}