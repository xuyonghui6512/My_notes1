// -------------- test the visual odometry -------------
#include "my_bar_code.h"
#include "find_and_pick.h"
#include "opencv2/opencv.hpp"
#include "image_handle.h"


int main ( int argc, char** argv )
{

    mybar_code::Bar_code a;
    //cout<<"处理时间为： "<<a.dealing_date<<endl;
//    VideoCapture cap;
//    cap.open(0);
//    Mat frame;
//    while(1)
//    {
        clock_t start_time = clock();
//        cap>>frame;
    Mat img=imread("/home/xuxuxu/b/二维码测试图片/17.jpg");

    //cout<<a.code_info;
//          mybar_code::CodeDetect::Judge_QRCode(img,a);
//   mybar_code::CodeDetect::Zbar_It(img,a);


//    a.bar_code_show(a);
    //Mat lena = imread("/home/xuxuxu/b/二维码测试图片/16.jpg");
    Mat img11;
    //mybar_code::Image_handle::Image_sharp(img,img11);
    //imshow("img",img11);
     mybar_code::CodeDetect::Find_Bar_Code_And_Rotate(img,img11);
    //resize(img11,img11,Size(600,800));
    if(!img11.empty()) {
        mybar_code::CodeDetect::Zbar_It(img11, a);
        a.bar_code_show(a);
    }
    if(!img11.empty())
    imshow("1",img11);
    clock_t end_time = clock();
    std::cout<<"Runing time is:"
             <<static_cast<double>(end_time - start_time)/CLOCKS_PER_SEC*1000
             <<"ms"<<std::endl;
        int c=waitKey(0);
//        if(c==27)
//        {
//            break;
//        }
        if(img.empty())
        {
            printf("--(!) No captured frame -- Break!");
//break;
        }


    return 0;
}
