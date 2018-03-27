// -------------- test the visual odometry -------------
#include "my_bar_code.h"
#include "find_and_pick.h"
#include "opencv2/opencv.hpp"


int main ( int argc, char** argv )
{
    mybar_code::Bar_code a;
    cout<<"处理时间为： "<<a.dealing_date<<endl;
    Mat img=imread("/home/xuxuxu/b/xuyonghui6512.github.io-master/练习/22/build/bin/7.jpeg");
    mybar_code::CodeDetect::Zbar_It(img,a);
    cout<<a.code_info;
    return 0;
}
