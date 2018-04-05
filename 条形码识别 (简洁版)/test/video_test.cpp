// -------------- test the visual odometry -------------
#include "my_bar_code.h"
#include "find_and_pick.h"
#include "opencv2/opencv.hpp"
#include "image_handle.h"

int main ( int argc, char** argv )
{
    VideoCapture cap;
    cap.open(0);
    Mat frame;
    mybar_code::Bar_code a;
    while(1) {
        clock_t start_time = clock();
        cap>>frame;
       // Mat img = frame.clone();
        mybar_code::CodeDetect::Judge_QRCode(frame,a);
//    Mat img11;
//    img11=mybar_code::CodeDetect::Find_Bar_Code_And_Rotate(img);
////        mybar_code::Image_handle::Image_sharp(frame,frame);
//        mybar_code::CodeDetect::Find_Bar_Code_And_Rotate(frame);
       bool key = mybar_code::CodeDetect::Zbar_It(frame, a);
        if (key) {
            a.bar_code_show(a);
            waitKey(0);
        }
//    if(!img11.empty())
//    imshow("1",img11);
        clock_t end_time = clock();
        std::cout << "Runing time is:" << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms"
                  << std::endl;
        imshow("1",frame);
        int c=waitKey(1);
        if(c==27)
            break;
    }

    return 0;
}
