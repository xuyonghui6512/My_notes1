// -------------- test the visual odometry -------------
#include "my_bar_code.h"
#include "find_and_pick.h"
#include "opencv2/opencv.hpp"
#include "image_handle.h"
#include  "myVideoCap.h"

int main ( int argc, char** argv )
{
    VideoCapture cap;
    cap.open("/home/xuxuxu/条形码测试视频/test2.avi");
   // hitcrt::myVideoCap cap("/dev/video1",1024,768,30);
    Mat frame;
    mybar_code::Bar_code a;
    bool g_key;
    Mat img,img1;
    Mat img_abs;
    int countt=1;
    while(1) {
        clock_t start_time = clock();
        cap>>frame;
//        cap.VideoGrab(frame);
        if(countt==1)

        {
            img=frame;
            countt--;
        }
        else {
            img1 = frame.clone();
        }
        if(countt==0&&(!img1.empty()))
            img_abs=img1-img;
        if(!img_abs.empty()) {
            imshow("abs", img_abs);
            waitKey();
        }
        img=frame;
        Mat theObject;
        /////////////////////
        RotatedRect findrect;
        bool isTrue=mybar_code::CodeDetect::barcode_oriented(img,findrect);
        bool isPicture;
        if(isTrue)
            isPicture=mybar_code::CodeDetect::Rotate_and_Find_barcode(findrect,img,theObject);
        /////////////////////
        if(isPicture&&(!theObject.empty())) {
             bool key = mybar_code::CodeDetect::Zbar_It(theObject, a);
            g_key=key;
        if (key) {
            a.bar_code_show(a);
        }
        }
//        else{
//            bool key1=mybar_code::CodeDetect::Zbar_It(img,a);//若没找到合理的roi区域，则解码原图
//            if(key1) {
//                a.bar_code_show(a);
//            }}
        clock_t end_time = clock();
        std::cout << "Runing time is:" << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms"
                  << std::endl;
        imshow("2",frame);
        if(isPicture&&(!theObject.empty())) {
            imshow("1", theObject);
            waitKey(0);
            if(g_key)
                waitKey(0);
        }
        int c=waitKey(1);
        if(c==27)
            break;
    }

    return 0;
}
