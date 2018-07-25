#include <iostream>
//#include <opencv2/opencv.hpp>
#include "Camera_pylon/camera_pylon.h"
#include <stdio.h>

using namespace std;
using namespace cv;
//using namespace hitcrt;
using namespace Basler_GigECameraParams;
using namespace Pylon;
//typedef Pylon::CBaslerGigEInstantCamera Camera_t;

int main()
{

    Pylon::PylonAutoInitTerm autoInitTerm;
    CDeviceInfo info;
    info.SetDeviceClass(Camera_t::DeviceClass());

//    info.SetSerialNumber("21638206");// left-back
    Camera_t camera(CTlFactory::GetInstance().CreateDevice(info));
    camera_pylon camera_p(camera);
    cout << "111 " << endl;
//    int frame_count = 0;
    double t1=0,t2=0;
    double fps=0;
    cv::Mat frame;
    while(camera.IsGrabbing())
    {

        double t1 = (double)getTickCount();

        camera.RetrieveResult(1000000, camera_p.ptrGrabResult, TimeoutHandling_ThrowException);//1000000

        if(camera_p.ptrGrabResult->GrabSucceeded()){

            Mat img_temp;
            camera_p.formatConverter.Convert(camera_p.pylonImage, camera_p.ptrGrabResult);
            img_temp = cv::Mat(camera_p.ptrGrabResult->GetHeight(), camera_p.ptrGrabResult->GetWidth(), CV_8UC3,
                               (uint8_t *) camera_p.pylonImage.GetBuffer());
            imshow("frame",img_temp);
            waitKey(1);

        }

        double t2 = (double)getTickCount();
        cout << "time grab thread is :" << (t2-t1)/getTickFrequency()*1000 <<endl;
        cout << "fps=" << 1000/((t2-t1)/getTickFrequency()*1000) << endl;
    }

    return 0;
}
