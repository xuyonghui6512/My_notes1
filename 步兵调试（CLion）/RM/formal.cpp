//
// Created by xuduo on 17-7-5.
//

#include <iostream>
#include <sstream>
#include <iomanip>
#include <sys/time.h>
#include <boost/thread.hpp>

#include "ArmorDetect/ArmorDetect.h"
#include "ArmorDetect/Predictor.h"

#include "capset/myVideoCap.h"
#include "ArmorDetect/serialapp.h"

using namespace cv;
using namespace std;


int ImgCount=0;
char ImgName[50];

boost::thread grabThread, processThread, communicationThread, manualThread;
boost::mutex frameMutex, pitchMutex, AssitMutex;
hitcrt::SerialApp* pSerialApp;
float pitchAngle = 0.0f;
int FLAG_ASSIST_AIM = 1; ///DEBUG

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
//    hitcrt::myVideoCap cap("/dev/video1",640,480,120);
    cv::VideoCapture cap;
    cap.open("/home/kx/RFID/recordArmor.avi");
    cv::Mat frame;
    while(1)
    {
        boost::this_thread::interruption_point();
        if(frameMutex.try_lock())
        {
//            cap.VideoGrab(frame);
            cap>>frame;
            imshow("frame",frame);
            frameBuff = hitcrt::Frame(frame);
            frameMutex.unlock();
        }
        boost::this_thread::sleep(boost::posix_time::milliseconds(5));
    }
}

void process()
{
    cv::Mat frame;
    hitcrt::ArmorDetect armorDetect;
    hitcrt::Predictor predictor(10);
    Mat R,new_Matrix;
    cv::initUndistortRectifyMap(hitcrt::Param::KK,hitcrt::Param::DISTORT,R,new_Matrix,Size(640,480),CV_32FC1,
                                    hitcrt::Param::MAPX,hitcrt::Param::MAPY);

    struct timeval frame_t;
    int countNum = 0;
    double t1=0,t2=0;
    double fps = 0;
    int checkAssistFlag = 0;
    while(1)
    {
        boost::this_thread::interruption_point();
//        gettimeofday(&st,NULL);
        AssitMutex.lock();
        checkAssistFlag = FLAG_ASSIST_AIM;
        AssitMutex.unlock();
        if(checkAssistFlag==0)
            continue;
        else if(checkAssistFlag==1){
            armorDetect.armor_type = true;
        }
        else if(checkAssistFlag==2){
            armorDetect.armor_type = false;
        }
//        cout << "checkAssistFlag " << checkAssistFlag <<endl;
        frameMutex.lock();
        if(!frameBuff.m_img.empty()) {
            frame = frameBuff.m_img.clone();
            frameBuff.m_img.release();
            frame_t = frameBuff.m_t;
            frameMutex.unlock();
        }else{
            frameMutex.unlock();
            continue;
        }

        ++countNum;
//        cout << "countNum = " << countNum << endl;
        ///去畸变
        remap(frame,frame,hitcrt::Param::MAPX,hitcrt::Param::MAPY,INTER_LINEAR);

        vector<hitcrt::Armor> armors;
        pitchMutex.lock();
        float m_pitchAngle = pitchAngle;
        pitchMutex.unlock();
        armorDetect.Apply(armors, frame,m_pitchAngle);
//        sprintf(ImgName,"/home/kx/project/picture/Img_%.3d.jpg",ImgCount);
//        cv::imwrite(ImgName,frame);
//        ImgCount++;
//        cout<<"imgcount "<<ImgCount<<endl;
        armorDetect.showImage(armors);
        if(armors.size() < 1)
            continue;

        float min_distance = 100000;
        int min_index = 0;
        for (int j = 0; j < armors.size(); ++j) {
            if(armors[j].m_distance < min_distance)
            {
                min_distance = armors[j].m_distance;
                min_index = j;
            }
        }

        double now_time = static_cast<double>(frame_t.tv_sec) + static_cast<double>(frame_t.tv_usec) / 1000000.0;
        cout << "now time "<<now_time<<endl;



//        cout << "record = " << armors[min_index].m_center_uv.x-320 << endl;

//        cout << "output = " << output << endl;
//        cout << "distance = " << armors[min_index].m_distance << endl;
//        cout << "countNum" << countNum << endl;
        float sendAngle = (armors[min_index].m_center_uv.x - 320) / (hitcrt::Param::DXDY) * 180/ CV_PI;

        sendAngle += asin(46.5 / armors[min_index].m_distance) * 180 / CV_PI;

        predictor.setRecord(sendAngle, now_time);
        float output = predictor.predict(now_time+0.016*3);///#1 #5 0.016*3




        vector<float> send_data;
        send_data.push_back(armors[min_index].m_eject_theta * 180 / CV_PI);
        send_data.push_back(armors[min_index].m_distance);
        send_data.push_back(output + 0.2);///#1 #5 -0.5
        pSerialApp->send(hitcrt::SerialApp::SEND_ASSIST_AIM, send_data);

//        for (int i = 0; i < send_data.size(); ++i) {
//            cout << send_data[i] << endl;
//        }
        t2 = ((double)cv::getTickCount() - t1) / cv::getTickFrequency();
        t1 = (double)cv::getTickCount();
        fps = 1.0 / t2;
        cout << "sendAngle = " << sendAngle << endl;
        cout << " X Y = " << armors[min_index].m_X << "  " << armors[min_index].m_Y << endl;
        cout << "pitchAngle = " << m_pitchAngle * 180 / CV_PI << endl;
        cout << " eject_data =" << armors[min_index].m_eject_theta * 180 / CV_PI << endl;
        cout << "---------------------------------------------" << endl;
        cout << "predict " << output - 0.5 <<endl;
        cout << "normal  " << sendAngle - 0.5 <<endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~fps " << fps << endl;
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
        boost::this_thread::sleep(boost::posix_time::milliseconds(500));
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
            if(fabs(tempFlag-1)<1e-6){
                FLAG_ASSIST_AIM = 1;
            }else if(fabs(tempFlag-2)<1e-6){
                FLAG_ASSIST_AIM = 2;
            }
            else if(fabs(tempFlag)<1e-6){
                FLAG_ASSIST_AIM = 0;
            }
            AssitMutex.unlock();
        }
        else if(eReceiveFlag == hitcrt::SerialApp::RECEIVE_PITCH_ANGLE)
        {
            pitchMutex.lock();
            float tempPitchAngle = data.front();
//            cout << "pitchAngle = " << tempPitchAngle << endl;
            if(tempPitchAngle < hitcrt::Param::MAX_ROBOT_PITCH * 180 / CV_PI
               && tempPitchAngle > hitcrt::Param::MIN_ROBOT_PITCH * 180 / CV_PI){
                pitchAngle = tempPitchAngle * CV_PI / 180;
            }
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