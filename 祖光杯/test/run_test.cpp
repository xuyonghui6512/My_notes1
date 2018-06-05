// -------------- test the visual odometry -------------
#include "my_bar_code.h"
#include "find_and_pick.h"
#include "opencv2/opencv.hpp"
#include "image_handle.h"


int main ( int argc, char** argv )
{
    clock_t start_time = clock();
    mybar_code::Bar_code a;
    Mat img=imread("/home/xuxuxu/b/二维码测试图片/1.jpg");
    Mat img_for_barcode;
    img_for_barcode=img.clone();
    Mat theObject,theObject2;
    Point2f local;
    RotatedRect output,rotate_rect_for_barcode;
    Mat src=img.clone();
    //resize(src, src, Size(800, 600));
    /////////////////////
      if(mybar_code::CodeDetect::Find_QRCode_Oriented_Point(img,local))//会将图片resize成800×600
      {
          cout << local << endl;

          mybar_code::CodeDetect::Find_QRCode_RotateRect(img, local, output);
          mybar_code::CodeDetect::Rotate_and_Find_QRcode(output,img,theObject);
          if(!theObject.empty()) {
              mybar_code::CodeDetect::Zbar_It(theObject,a);
              a.bar_code_show(a);
              imshow("the", theObject);
          }
      }

//    mybar_code::CodeDetect::barcode_oriented(img_for_barcode,rotate_rect_for_barcode);
    clock_t end_time = clock();
    std::cout<<"Runing time is:"<<static_cast<double>(end_time - start_time)/CLOCKS_PER_SEC*1000<<"ms"<<std::endl;
    waitKey(0);

    return 0;
}
