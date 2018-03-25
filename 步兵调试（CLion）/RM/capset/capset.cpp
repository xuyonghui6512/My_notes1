#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "myVideoCap.h"
#include <iostream>
using namespace std;
using namespace cv;
using namespace hitcrt;
int main(int argc, char *argv[])
{
   myVideoCap cap0("/dev/video1",640,480,120);
   Mat frame;
   double t1=0,t2=0;
    double fps;
    int num = 0;
    char frameName[50];
   while(1)
   {
        t2 = ((double)cv::getTickCount() - t1) / cv::getTickFrequency();
        t1 = (double)cv::getTickCount();
        fps = 1.0 / t2;
        std::cout<<"fps:"<<fps<<std::endl;
        //obj.image_deal();
         cap0.VideoGrab(frame);
         imshow("frame",frame);
         
         
         char ch = waitKey(1);
       if(ch == 'q')
           break;
//       else if(ch == 's')
//       {
           sprintf(frameName,"/home/kx/project/RM/image/img_%.3d.jpg",num);
           std::cout << frameName << std::endl;
           imwrite(frameName,frame);
           ++num;
           cout << num  << endl;
//       }
   }


    return 0;
}



