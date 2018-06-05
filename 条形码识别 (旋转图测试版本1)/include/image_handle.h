//
// Created by xuxuxu on 18-4-5.
//

#ifndef BAR_CODE_IMAGE_HANDLE_H
#define BAR_CODE_IMAGE_HANDLE_H
#include "common_include.h"

namespace mybar_code
{
    class Image_handle{
    public:
        Image_handle(){}
        ~Image_handle(){}
        static void Image_sharp(Mat& _img,Mat& _output);
        static Mat Best_Image_Choose(Mat& A,Mat& B,int& key);
        static Mat turn90degree(Mat& srcimg);
    };
}
#endif //BAR_CODE_IMAGE_HANDLE_H
