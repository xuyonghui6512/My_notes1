#include <iostream>
#include <sstream>
#include <iomanip>
#include <sys/time.h>
#include <boost/thread.hpp>

#include <pylon/PylonIncludes.h>
#include <pylon/gige/BaslerGigEInstantCamera.h>
#include <opencv2/opencv.hpp>
#include "my_bar_code.h"
#include "find_and_pick.h"
#include "image_handle.h"

#include "serialapp.h"
#include "serialbase.h"

using namespace Basler_GigECameraParams;

using namespace Pylon;
using namespace cv;
using namespace std;

typedef Pylon::CBaslerGigEInstantCamera Camera_t;





boost::thread grabThread, processThread, communicationThread, manualThread;
boost::mutex frameMutex, pitchMutex, AssitMutex,m_send_Mutex;
hitcrt::SerialApp* pSerialApp;

namespace hitcrt{
    struct Frame{
        Frame(){}
        Frame(cv::Mat _img, struct timeval _t) : m_img(_img), m_t(_t) {}
        Frame(cv::Mat _img) : m_img(_img) {
            gettimeofday(&m_t, NULL);
        }
        cv::Mat m_img;
        struct timeval m_t;
    };
}

hitcrt::Frame frameBuff;

void grab()
{
    // 新建pylon ImageFormatConverter对象
    CImageFormatConverter formatConverter;
    //确定输出像素格式
    formatConverter.OutputPixelFormat = PixelType_BGR8packed;
    // 创建一个Pylonlmage后续将用来创建OpenCV images
    CPylonImage pylonImage;
    bool GAMMA_ENABLE = true;
    bool GAIN_ENABLE = false;
    float GAMMA_VALUE = 0.7;
    bool GAIN_AUTO = false;//gain_auto==off
    int GAIN_INIT_VALUE = 0;
    int IMAGE_WIDTH = 1024;
    int IMAGE_HEIGHT = 768;
    int FRAME_FPS = 120;

    int INIT_EXPOSURE_TIME = 100;
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
        camera.BalanceRatioSelector.SetValue(BalanceRatioSelector_Red);
//        camera.PixelFormat.SetValue(PixelFormat_Mono8);


        if(GAMMA_ENABLE)    /**启用 GAMMA 校正 **/
        {
            camera.GammaEnable.SetValue(true);
            camera.GammaSelector.SetValue(GammaSelector_User);
            camera.Gamma.SetValue(GAMMA_VALUE);
            camera.DigitalShift.SetValue(2);//

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
            camera.GainSelector.SetValue(GainSelector_AnalogAll);
            camera.GainRaw.SetValue(0);
            /////
            camera.BlackLevelSelector.SetValue(BlackLevelSelector_All);
            camera.BlackLevelRaw.SetValue(0);
            camera.TestImageSelector.SetValue(TestImageSelector_Off);
            camera.AcquisitionFrameCount.SetValue(1);
            camera.ExposureAuto.SetValue(ExposureAuto_Off);
            camera.AutoFunctionProfile.SetValue(AutoFunctionProfile_GainMinimum);
        }

//        camera.UserSetSelector.SetValue(UserSetSelector_Default);
//        camera.DecimationHorizontal.SetValue(1);
//        camera.DecimationVertical.SetValue(1);
        camera.ActionSelector.SetValue(1);////
        camera.Width.SetValue(IMAGE_WIDTH);//
        camera.Height.SetValue(IMAGE_HEIGHT);//
        //camera.OffsetY.SetValue(FRONT_YOFFSET_INIT);
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
        camera.GevSCPSPacketSize.SetValue(1500);
//        camera.StartGrabbing(GRAB_NUM);
        camera.StartGrabbing(GrabStrategy_LatestImages);
//        camera.StartGrabbing(GrabStrategy_OneByOne);
        while ( camera.IsGrabbing())
        {
            //////////////////////////////
            boost::this_thread::interruption_point();
            /////////////////////////////
            cout<<"camera is grabbing"<<endl;
            camera.RetrieveResult( 1000000, ptrGrabResult, TimeoutHandling_ThrowException);//1000000
            if(ptrGrabResult->GrabSucceeded())
            {
                if(frameMutex.try_lock()) {
                    char *pImageBuffer = (char *) ptrGrabResult->GetBuffer();
//                ST_MAT temp_mat;
                    Mat img;
//                temp_mat.img = Mat(IMAGE_HEIGHT,IMAGE_WIDTH,CV_8UC1,pImageBuffer);
                    formatConverter.Convert(pylonImage, ptrGrabResult);
                    img = cv::Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3,
                                  (uint8_t *) pylonImage.GetBuffer());
                    frameBuff=hitcrt::Frame(img);
                    frameMutex.unlock();
//                writer << img;
                    ////////////////////////////////////////////////////////////////////条形码识别部分
//                mybar_code::Bar_code a;
//                bool g_key;
//                Mat theObject;
//                /////////////////////
//                RotatedRect findrect;
//                bool isTrue=mybar_code::CodeDetect::barcode_oriented(img,findrect);
//                cout<<"**********************"<<findrect.center<<endl;
//                bool isPicture;
//                if(isTrue&&findrect.center.x>50&&findrect.center.y>50)
//                    isPicture=mybar_code::CodeDetect::Rotate_and_Find_barcode(findrect,img,theObject);
//                ///////////////////
//                if(isPicture&&(!theObject.empty())) {
//                    bool key = mybar_code::CodeDetect::Zbar_It(theObject, a);
//                    imshow("the",theObject);
//                    g_key=key;
//                    if (key) {
//                        a.bar_code_show(a);
//                        waitKey(0);
//                    }
//                }
//                ////////////////////////////////////////////////////////////////////
////                cvtColor(temp_mat.img,temp_mat.img,CV_BayerRG2RGB);
////                temp_mat.tag = ptrGrabResult->ChunkTriggerinputcounter.GetValue();
////                cout << "left_front = " << temp_mat.tag << endl;
//                    cout << "11111111111111" << endl;
                    //imshow("frame_left", img);
                    waitKey(1);
                }
                boost::this_thread::sleep(boost::posix_time::milliseconds(5));
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


}

void process()
{
    while(1)
    {

        cv::Mat frame;
        boost::this_thread::interruption_point();
        frameMutex.lock();
        if(!frameBuff.m_img.empty()) {
            frame = frameBuff.m_img.clone();
            frameBuff.m_img.release();
            frameMutex.unlock();
        }else{
            frameMutex.unlock();
            continue;
        }
        ///////////////////////////////////////////////////
        vector<float> send_data;
        mybar_code::Bar_code a;
        Mat theObject;
        /////////////////////
        RotatedRect findrect;
        bool isTrue=mybar_code::CodeDetect::barcode_oriented(frame,findrect);
        bool isPicture;

        if(isTrue&&findrect.center.x>50&&findrect.center.y>50)
            isPicture=mybar_code::CodeDetect::Rotate_and_Find_barcode(findrect,frame,theObject);

        ///////////////////
        if(isPicture&&(!theObject.empty())) {
           bool key = mybar_code::CodeDetect::Zbar_It(theObject, a);
            //imshow("the",theObject);

            if (key) {
                a.bar_code_show(a);
                send_data.push_back(1.0);
                send_data.push_back(1.0);
                send_data.push_back(1.0);
                send_data.push_back(1.0);


            }
            else

            {
                send_data.push_back(5.0);
                send_data.push_back(5.0);
                send_data.push_back(5.0);
                send_data.push_back(5.0);
            }


        } else {


            send_data.push_back(5.0);
            send_data.push_back(5.0);
            send_data.push_back(5.0);
            send_data.push_back(5.0);
        }

        pSerialApp->send(hitcrt::SerialApp::SEND_ASSIST_AIM, send_data);




    }

}
void manual()
{
    while(1)
    {
        boost::this_thread::interruption_point();
        if('q' == getchar())
        {
            grabThread.interrupt();
            cout <<"1" << endl;
            grabThread.join();

            processThread.interrupt();
            cout << "2" << endl;
            processThread.join();

            break;
        }
        boost::this_thread::sleep(boost::posix_time::milliseconds(50));
    }
}

void communication()
{
    pSerialApp = new hitcrt::SerialApp("/dev/ttyUSB0", 115200);
    while(1)
    {
        boost::this_thread::interruption_point();
        hitcrt::SerialApp::RECEIVE_FLAG eReceiveFlag;
        std::vector<float> data;
        pSerialApp->receive(eReceiveFlag, data);
//        for (int i = 0; i < data.size(); ++i) {
//            cout << data[i] << endl;
//        }
//        cout << "receiviqqng-------------------------------------------------------------------------" << endl;
//        cout << "eReceiveFlag " << eReceiveFlag <<endl;
//        exit(-2);
        if(eReceiveFlag == hitcrt::SerialApp::RECEIVE_ASSIST_AIM)
        {
            AssitMutex.lock();
            float tempFlag = data.front();
//            cout <<"temp flag " <<tempFlag<<"===================================="<<endl;
//            if(fabs(tempFlag-1)<1e-6){
//                FLAG_ASSIST_AIM = 1;
//            }else if(fabs(tempFlag-2)<1e-6){
//                FLAG_ASSIST_AIM = 2;
//            }
//            else if(fabs(tempFlag)<1e-6){
//                FLAG_ASSIST_AIM = 0;
//            }
            AssitMutex.unlock();
        }
        else if(eReceiveFlag == hitcrt::SerialApp::RECEIVE_PITCH_ANGLE)
        {
            pitchMutex.lock();
            float tempPitchAngle = data.front();
//            cout << "pitchAngle = " << tempPitchAngle << endl;
//            if(tempPitchAngle < 30* 180 / CV_PI
//               && tempPitchAngle > 30 * 180 / CV_PI){
//                pitchAngle = tempPitchAngle * CV_PI / 180; //发0即可
//            }
            pitchMutex.unlock();

        }

        boost::this_thread::sleep(boost::posix_time::milliseconds(20));
    }
}
int main()
{
    grabThread = boost::thread(grab);
    processThread = boost::thread(process);
    manualThread = boost::thread(manual);
    communicationThread = boost::thread(communication);

    manualThread.join();
    return 0;
}