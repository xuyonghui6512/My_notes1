/*2018.3.27
  made by Xuxuxu
  This class contains  ifo about a bar code
*/ 
#ifndef MY_BAR_CODE_H
#define MY_BAR_CODE_H

#include "common_include.h"

namespace mybar_code
{
class Bar_code{
public:
    Bar_code(){}
    ~Bar_code(){}
    typedef enum type{
        one_dim_code=0,
        two_dim_code
    }TYPE;
    TYPE m_type;//条形码类型（一维还是二维）
    string code_info;//条形码的解码内容
    static string dealing_date;//条形码被处理的日期
    static string get_dealing_date();//得到处理条形码的日期
    Point2d code_lt_pt;//条形码左上角点
    Point2d code_rt_pt;//条形码右上角点
    Point2d code_lb_pt;//条形码左下角点
    Point2d code_rb_pt;//条形码左上角点
};

}
#endif // MY_BAR_CODE_H