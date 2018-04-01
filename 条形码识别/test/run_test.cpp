// -------------- test the visual odometry -------------
#include "my_bar_code.h"
#include "find_and_pick.h"
#include "opencv2/opencv.hpp"


int main ( int argc, char** argv )
{
    clock_t start_time = clock();
    mybar_code::Bar_code a;
    //cout<<"处理时间为： "<<a.dealing_date<<endl;
    Mat img=imread("/home/xuxuxu/b/二维码测试图片/17.jpg");

    //cout<<a.code_info;
    mybar_code::CodeDetect::Judge_QRCode(img,a);
//    mybar_code::CodeDetect::Zbar_It(img,a);


//    a.bar_code_show(a);
    Mat img11;
    img11=mybar_code::CodeDetect::Find_Bar_Code_And_Rotate(img);
    mybar_code::CodeDetect::Zbar_It(img11,a);
    a.bar_code_show(a);
    if(!img11.empty())
    imshow("1",img11);
    clock_t end_time = clock();
    std::cout<<"Runing time is:"<<static_cast<double>(end_time - start_time)/CLOCKS_PER_SEC*1000<<"ms"<<std::endl;
    waitKey(0);

    return 0;
}
