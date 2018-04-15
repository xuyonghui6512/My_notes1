// -------------- test the visual odometry -------------
#include "my_bar_code.h"
#include "find_and_pick.h"
#include "opencv2/opencv.hpp"


int main ( int argc, char** argv )
{
    clock_t start_time = clock();
    mybar_code::Bar_code a;
    Mat img=imread("/home/xuxuxu/b/二维码测试图片/30.jpg");
    Mat theObject;
    /////////////////////
    RotatedRect findrect=mybar_code::CodeDetect::barcode_oriented(img);
    mybar_code::CodeDetect::Rotate_and_Find_barcode(findrect,img,theObject);
    imshow("1111",theObject);
    Point2f rect[4];//用来取外接矩形的四个定点
    findrect.points(rect);  //把最小外接矩形四个端点复制给rect数组
//    for (int k = 0; k < 4; k++) {
//        line(img, rect[k], rect[(k + 1) % 4], Scalar(0, 255, 255), 2, 8);  //绘制最小外接矩形每条边
//    }
    /////////////////////
        bool key = mybar_code::CodeDetect::Zbar_It(theObject, a);
        if (key) {
            a.bar_code_show(a);
        }
    else{
    bool key1=mybar_code::CodeDetect::Zbar_It(img,a);//若没找到合理的roi区域，则解码原图
    if(key1) {
        a.bar_code_show(a);
    }}
//    if(!img11.empty())
//    imshow("1",img11);
    clock_t end_time = clock();
    std::cout<<"Runing time is:"<<static_cast<double>(end_time - start_time)/CLOCKS_PER_SEC*1000<<"ms"<<std::endl;
    waitKey(0);

    return 0;
}
