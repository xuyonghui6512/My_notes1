// -------------- test the visual odometry -------------
#include "my_bar_code.h"
#include "find_and_pick.h"
#include "opencv2/opencv.hpp"


int main ( int argc, char** argv )
{
    mybar_code::Bar_code a;
    cout<<"处理时间为： "<<a.dealing_date<<endl;
    Mat img=imread("/home/xuxuxu/b/二维码测试图片/10.jpg");
    mybar_code::CodeDetect::Zbar_It(img,a);
    cout<<a.code_info;
    mybar_code::CodeDetect::Judge_QRCode(img,a);
    cout<<a.m_type<<endl;
    return 0;
}
