#include <pylon/PylonIncludes.h>
#include <pylon/gige/BaslerGigEInstantCamera.h>
#include <opencv2/opencv.hpp>
#include "my_bar_code.h"
#include "find_and_pick.h"
#include "image_handle.h"
#include  "myVideoCap.h"

using namespace std;

using namespace Basler_GigECameraParams;

using namespace Pylon;
using namespace cv;

typedef Pylon::CBaslerGigEInstantCamera Camera_t;

typedef struct _ST_MAT
{
    cv::Mat img;
    int tag;
}ST_MAT;

int main()
{
    int ImgNum=0;
    char ImgName[50];

    // 新建pylon ImageFormatConverter对象
    CImageFormatConverter formatConverter;
    //确定输出像素格式
    formatConverter.OutputPixelFormat = PixelType_BGR8packed;
    // 创建一个Pylonlmage后续将用来创建OpenCV images
    CPylonImage pylonImage;

    bool GAMMA_ENABLE = true;
    bool GAIN_ENABLE = false;
    float GAMMA_VALUE = 0.7;
    bool GAIN_AUTO = false;
    int GAIN_INIT_VALUE = 0;
    int IMAGE_WIDTH = 1024;
    int IMAGE_HEIGHT = 768;
    int FRAME_FPS = 120;

    int INIT_EXPOSURE_TIME = 21000;
    float FRONT_YOFFSET_INIT = 0;


    int exitCode = 0;
    Pylon::PylonAutoInitTerm autoInitTerm;              /** 优先保证其最先开始初始化  **/
    try
    {
        CDeviceInfo info;
        CBaslerGigEGrabResultPtr ptrGrabResult;
        info.SetDeviceClass( Camera_t::DeviceClass());
        info.SetSerialNumber("21638141");// left-back//需要看basler相机上的info
        Camera_t camera( CTlFactory::GetInstance().CreateDevice(info));
        camera.Open();
        if(camera.IsOpen()){
            cout<<"camera open successfully"<<endl;
        } else{
            cout<<"camera open failed"<<endl;
        }
//        camera.ChunkModeActive.SetValue(false);//true
//        camera.CounterSelector.SetValue(CounterSelector_Counter1);
//        camera.CounterEventSource.SetValue(CounterEventSource_FrameTrigger);
//        camera.CounterResetSource.SetValue(CounterResetSource_Software);
//        camera.CounterReset.Execute();
//        camera.ChunkSelector.SetValue(ChunkSelector_Triggerinputcounter);
//        camera.ChunkEnable.SetValue(true);//true

        camera.PixelFormat.SetValue(PixelFormat_BayerRG8);
//        camera.PixelFormat.SetValue(PixelFormat_BGR8Packed);
//        camera.PixelFormat.SetValue(PixelFormat_BGR8Packed,true);
        camera.BalanceWhiteAuto.SetValue(BalanceWhiteAuto_Continuous);
//        camera.PixelFormat.SetValue(PixelFormat_Mono8);


        if(GAMMA_ENABLE)    /**启用 GAMMA 校正 **/
        {
            camera.GammaEnable.SetValue(true);
            camera.GammaSelector.SetValue(GammaSelector_User);
            camera.Gamma.SetValue(GAMMA_VALUE);

        }
        else
        {
            camera.GammaEnable.SetValue(false);
        }
        if(GAIN_ENABLE)
        {
            if(GAIN_AUTO)
            {
                camera.GainAuto.SetValue(GainAuto_Continuous);
            }
            else
            {
                camera.GainAuto.SetValue(GainAuto_Off);
                camera.GainSelector.SetValue(GainSelector_DigitalAll);
                camera.GainRaw.SetValue(GAIN_INIT_VALUE);
            }
        }
        else
        {
            camera.GainAuto.SetValue(GainAuto_Off);
            camera.GainSelector.SetValue(GainSelector_DigitalAll);
            camera.GainRaw.SetValue(0);
        }

//        camera.UserSetSelector.SetValue(UserSetSelector_Default);
//        camera.DecimationHorizontal.SetValue(1);
//        camera.DecimationVertical.SetValue(1);

        camera.Width.SetValue(IMAGE_WIDTH);
        camera.Height.SetValue(IMAGE_HEIGHT);
        camera.OffsetY.SetValue(FRONT_YOFFSET_INIT);
        camera.ExposureMode.SetValue(ExposureMode_Timed);
        camera.ExposureTimeAbs.SetValue(INIT_EXPOSURE_TIME);
        camera.AcquisitionMode.SetValue(AcquisitionMode_Continuous);
//        camera.TriggerSelector.SetValue(TriggerSelector_AcquisitionStart);
//        camera.TriggerMode.SetValue(TriggerMode_Off);
        camera.AcquisitionFrameRateEnable.SetValue(true);
        camera.AcquisitionFrameRateAbs.SetValue(FRAME_FPS);
//        camera.TriggerSelector.SetValue(TriggerSelector_FrameStart);
//        camera.TriggerMode.SetValue(TriggerMode_On);//TriggerMode_On
//        camera.TriggerSource.SetValue(TriggerSource_Line1);            /** 硬触发 **/
//        camera.TriggerActivation.SetValue(TriggerActivation_FallingEdge);
//        camera.GevStreamChannelSelector.SetValue(GevStreamChannelSelector_StreamChannel0);
//        camera.GevSCPSPacketSize.SetValue(8192);
//        camera.StartGrabbing(GRAB_NUM);
        camera.StartGrabbing(GrabStrategy_LatestImages);
//        camera.StartGrabbing(GrabStrategy_OneByOne);
        int frame_count = 0;
        double t1=0,t2=0;
        double fps=0;
        while ( camera.IsGrabbing())
        {
            cout<<"camera is grabbing"<<endl;
            t1 = ((double)cv::getTickCount()-t2);
            cout<<"fps: "<<(double)1/(t1/cv::getTickFrequency())<<endl;
            t2 = (double)cv::getTickCount();
            camera.RetrieveResult( 1000000, ptrGrabResult, TimeoutHandling_ThrowException);//1000000
            if(ptrGrabResult->GrabSucceeded())
            {
                cout<<"frame count "<<frame_count<<endl;
                frame_count++;
                char* pImageBuffer = (char *) ptrGrabResult->GetBuffer();
//                ST_MAT temp_mat;
                Mat img;
//                temp_mat.img = Mat(IMAGE_HEIGHT,IMAGE_WIDTH,CV_8UC1,pImageBuffer);
                formatConverter.Convert(pylonImage, ptrGrabResult);
                img = cv::Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3,
                                       (uint8_t *) pylonImage.GetBuffer());
                ////////////////////////////////////////////////////////////////////条形码识别部分
                mybar_code::Bar_code a;
                bool g_key;
                Mat theObject;
                /////////////////////
                RotatedRect findrect;
                bool isTrue=mybar_code::CodeDetect::barcode_oriented(img,findrect);
//                bool isPicture;
//                if(isTrue)
//                    isPicture=mybar_code::CodeDetect::Rotate_and_Find_barcode(findrect,img,theObject);
//                /////////////////////
//                if(isPicture&&(!theObject.empty())) {
//                    bool key = mybar_code::CodeDetect::Zbar_It(img, a);
////                    imshow("the",theObject);
//                    g_key=key;
//                    if (key) {
//                        a.bar_code_show(a);
//                    }
//                }
                ////////////////////////////////////////////////////////////////////
//                cvtColor(temp_mat.img,temp_mat.img,CV_BayerRG2RGB);
//                temp_mat.tag = ptrGrabResult->ChunkTriggerinputcounter.GetValue();
//                cout << "left_front = " << temp_mat.tag << endl;
                cout<<"11111111111111"<<endl;
                imshow("frame_left",img);
                waitKey(1);
//                if(!temp_mat.img.empty()){
////                    cv::imshow("frame",temp_mat.img);
//                    sprintf(ImgName, "Img_%.3d.jpg", ImgNum);
//                    cv::imwrite(ImgName,temp_mat.img);
//                    ImgNum++;
//                    cout<<"saving"<<ImgNum<<endl;
//                }
            }

//            cout << "left_front    " << frame_count << endl;
        }
    }
    catch (GenICam::GenericException &e)
    {
        cerr << "An exception occurred on left front camera." << endl
             << e.GetDescription() << endl;
        exitCode = 1;
    }

    return 1;
}

