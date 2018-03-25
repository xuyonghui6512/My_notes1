#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "../capset/myVideoCap.h"
#include <iostream>
using namespace std;
using namespace cv;
using namespace hitcrt;
int main(int argc, char *argv[])
{
    myVideoCap cap0("/dev/video1",640,480,120);
    Mat frame,undistort_frame;
    double t1=0,t2=0;
    double fps;
    int num = 0;
    char frameName[50];
    Mat KK,DISTORT,MAPX,MAPY;
    cv::FileStorage fs;
    fs.open("/home/kx/project/RM/camera.yml", cv::FileStorage::READ);
    assert(fs.isOpened());
    fs["camera_matrix"] >> KK;
    fs["distortion_coefficients"] >> DISTORT;
    Mat R,new_Matrix;
    cv::initUndistortRectifyMap(KK,DISTORT,R,new_Matrix,Size(640,480),CV_32FC1,
                                MAPX,MAPY);
    float CX=KK.at<double>(0,2);
    float CY=KK.at<double>(1,2);
    std::cout<<"MAPX "<<MAPX.rows<<"  "<<MAPX.cols<<std::endl;
//    std::cout<<"MAPY "<<MAPY<<std::endl;
    while(1)
    {

        cap0.VideoGrab(frame);

        ///去畸变
        remap(frame,undistort_frame,MAPX,MAPY,INTER_LINEAR);

        Vec3b* data = frame.ptr<Vec3b>(CY);
        for (int i = 0; i < frame.cols; ++i) {
            data[i] = Vec3b(0,0,255);
        }

        for (int i = 0; i < frame.rows; ++i) {
            frame.at<Vec3b>(i, CX) = Vec3b(0,0,255);
        }

//        Vec3b* data = frame.ptr<Vec3b>(frame.rows/2);
//        for (int i = 0; i < frame.cols; ++i) {
//            data[i] = Vec3b(0,0,255);
//        }
//
//        for (int i = 0; i < frame.rows; ++i) {
//            frame.at<Vec3b>(i, frame.cols/2) = Vec3b(0,0,255);
//        }

        Vec3b* data_u = undistort_frame.ptr<Vec3b>(frame.rows/2);
        for (int i = 0; i < undistort_frame.cols; ++i) {
            data_u[i] = Vec3b(0,0,255);
        }

        for (int i = 0; i < undistort_frame.rows; ++i) {
            undistort_frame.at<Vec3b>(i, frame.cols/2) = Vec3b(0,0,255);
        }

        imshow("frame",frame);
        imshow("undistort",undistort_frame);

        char ch = waitKey(1);
        if(ch == 'q')
            break;

    }


    return 0;
}



