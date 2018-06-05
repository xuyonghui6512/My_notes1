/*2018.3.29
  made by Xuxuxu
  This class contains contents about how to 
  find the code form a picuture we have provided
  and pick up its ifo.
*/ 
#ifndef FIND_AND_PICK_H
#define FIND_AND_PICK_H

#include "common_include.h"
#include "my_bar_code.h"
//new include needed to use Zbar
#include <zbar.h>
using namespace zbar;       

namespace mybar_code
{
    class CodeDetect{
    public:
      CodeDetect(){}
      ~CodeDetect(){}
      static bool Zbar_It(Mat& _img,Bar_code& _bar_code);//Zbar解码
      static void Judge_QRCode(Mat& img,Bar_code& _bar_code);//判断是否为二维码，判断结果直接存放在_bar_code里
      static Point Center_cal(vector<vector<Point> > contours,int i);//计算矩形轮廓中心
      static bool Find_QRCode_Oriented_Point(Mat &_img,Point2f& oriented_pt); //该函数可能不需要
      static bool barcode_oriented(Mat &img,RotatedRect& findrect);//用于找到包含条形码的旋转矩形
      static bool Rotate_and_Find_barcode(RotatedRect& findrect,Mat& input,Mat& output);//对找到的二维码进行处理
      static bool Find_QRCode_RotateRect(Mat& inputImg, Point2f oritented_pt,RotatedRect& output);//用于寻找包含二维码的旋转矩形，其中第二个参数由上边函数求得

    };
}
#endif //FIND_AND_PICK_H