// -------------- test the visual odometry -------------
#include "my_bar_code.h"
#include "find_and_pick.h"
#include "opencv2/opencv.hpp"
#include "image_handle.h"


int main ( int argc, char** argv )
{
    cout<<"I'm running!"<<endl;
    clock_t start_time = clock();
    mybar_code::Bar_code a;
    Mat img=imread("/home/xuxuxu/b/二维码测试图片/2.jpg");
    imshow("src",img);
    Mat img_for_barcode;
    img_for_barcode=img.clone();
    Mat theObject,theObject2;
    Point2f local;
    RotatedRect output,rotate_rect_for_barcode;
    Mat src=img.clone();
    ///////////////////////////////////
//      if(mybar_code::CodeDetect::Find_QRCode_Oriented_Point(img,local))//会将图片resize成800×600
//      {
//          cout << local << endl;
//
//          mybar_code::CodeDetect::Find_QRCode_RotateRect(img, local, output);
//          mybar_code::CodeDetect::Rotate_and_Find_QRcode(output, img, theObject);
//          if(!theObject.empty())
//          {
//              mybar_code::CodeDetect::Zbar_It(theObject,a);
//              a.bar_code_show(a);
//              imshow("the",theObject);
//          }
//
//
//      }
/////////////////////////////////////////下面是条形码部分
    bool g_key;
    /////////////////////
    RotatedRect findrect;
    bool isTrue=mybar_code::CodeDetect::barcode_oriented(img,findrect);
    cout<<"**********************"<<findrect.center<<endl;
    bool isPicture;
    if(isTrue&&findrect.center.x>0&&findrect.center.y>0)
        isPicture=mybar_code::CodeDetect::Rotate_and_Find_barcode(findrect,img,theObject);
    ///////////////////
    if(isPicture&&(!theObject.empty())) {
        bool key = mybar_code::CodeDetect::Zbar_It(theObject, a);
        if (key) {
            cv::RNG rng(time(0));
            putText(theObject, a.code_data, Point(theObject.cols / 9, theObject.rows / 2 + 20), FONT_HERSHEY_SIMPLEX,
                    0.8, Scalar(rng.uniform(150, 255), rng.uniform(150, 255), rng.uniform(150, 255)), 2);
            putText(theObject, a.code_type, Point(theObject.cols / 9, theObject.rows / 2 - 20), FONT_HERSHEY_SIMPLEX,
                    0.8, Scalar(rng.uniform(150, 255), rng.uniform(150, 255), rng.uniform(150, 255)), 2);
            imshow("提取的条码及信息", theObject);
            a.bar_code_show(a);
            waitKey(0);
        }
    }
    clock_t end_time = clock();
    std::cout<<"Runing time is:"<<static_cast<double>(end_time - start_time)/CLOCKS_PER_SEC*1000<<"ms"<<std::endl;
    waitKey(0);

    return 0;
}
