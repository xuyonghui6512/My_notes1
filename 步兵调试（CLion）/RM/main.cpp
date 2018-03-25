#include <iostream>
#include <sstream>
#include <iomanip>
#include <sys/time.h>

#include "ArmorDetect/ArmorDetect.h"
#include "ArmorDetect/Predictor.h"

#include "capset/myVideoCap.h"

using namespace std;
using namespace cv;

int main() {

//    hitcrt::ArmorDetect armorDetect;
//    hitcrt::Predictor predictor;
//    hitcrt::myVideoCap cap0("/dev/video1",640,480,120);
//    Mat frame;
//    double t1=0,t2=0;
//    double fps;
//    int num = 0;
//    while(1)
//    {
//        t2 = ((double)cv::getTickCount() - t1) / cv::getTickFrequency();
//        t1 = (double)cv::getTickCount();
////        fps = 1.0 / t2;
//        std::cout<<"running time(ms):"<<t2 * 1000<<std::endl;
//        struct timeval st,en;
//        gettimeofday(&st,NULL);
//        cap0.VideoGrab(frame);
//        imshow("frame",frame);
//
//
//        char ch = waitKey(1);
//        if(ch == 'q')
//            break;
//        vector<hitcrt::Armor> armors;
//        armorDetect.Apply(armors, frame);
//        if(armors.size() > 0) {         // 有armor
//            float min_distance = 100000;
//            int min_index = 0;
//            for (int j = 0; j < armors.size(); ++j) {
//                if(armors[j].m_distance < min_distance)
//                {
//                    min_distance = armors[j].m_distance;
//                    min_index = j;
//                }
//            }
//
//            double now_time = static_cast<double>(st.tv_sec) + static_cast<double>(st.tv_usec) / 1000000.0;
//            predictor.setRecord(armors[min_index].m_center_uv.x - 320, now_time);
//            double output = predictor.predict(now_time+0.01);
//            cout << "output = " << output << endl;
//            cout <<"---------------------------------" << endl;
//        }
//
//
//    }
//////////////////////////////////////////////////////////////////////////////////////
    hitcrt::ArmorDetect armorDetect;
    hitcrt::Predictor predictor;
    for (int i = 6; i < 500; ++i) {
        stringstream ss;
        ss << "/home/kx/project/RM/image/img_" << setw(3)<<  setfill('0') << i << ".jpg";
        string str;
        ss >> str;
        cout << str.c_str() << endl;
        Mat img_raw = imread(str.c_str());
        vector<hitcrt::Armor> armors;
        struct timeval st,en;
        gettimeofday(&st,NULL);

        armorDetect.Apply(armors, img_raw, 10*CV_PI/180);

        float min_distance = 100000;
        int min_index = 0;
        for (int j = 0; j < armors.size(); ++j) {
            if(armors[j].m_distance < min_distance)
            {
                min_distance = armors[j].m_distance;
                min_index = j;
            }
        }


//        if(armors.size() >= 1)
//        {
//            return -1;
//        }
        gettimeofday(&en,NULL);
        cout << "all time = " << en.tv_usec - st.tv_usec << endl;
        cout << "------------------------------------------" << endl;

        if(armors.size() < 1)
            continue;



        double now_time = static_cast<double>(st.tv_sec) + static_cast<double>(st.tv_usec) / 1000000.0;
        predictor.setRecord(armors[min_index].m_center_uv.x - 320, i*0.016);
        cout << "record = " << armors[min_index].m_center_uv.x-320 << endl;
        double output = predictor.predict(i*0.016+0.016);
        cout << "output = " << output << endl;
        cout << "distancce = " << armors[min_index].m_distance << endl;
////////////////////////////////////////////////////////////////////////////////////////////////
//        hitcrt::ArmorDetect armorDetect;
//        hitcrt::Predictor predictor;
//        cv::VideoCapture cap("/home/xuduo/lab/RM/image/videoFirstTryImportant01.avi");
//    Mat img_raw;
//        for (int i = 1; i < 800; ++i) {
//
//            cap >> img_raw;
//            resize(img_raw, img_raw, cv::Size(640,480));
//            vector<hitcrt::Armor> armors;
//            struct timeval st,en;
//            gettimeofday(&st,NULL);
//
//            armorDetect.Apply(armors, img_raw,10*CV_PI/180);
//
////        hitcrt::Armor& armor_send = judgeSendedArmor(armors);
//            float min_distance = 100000;
//            int min_index = 0;
//            for (int j = 0; j < armors.size(); ++j) {
//                if(armors[j].m_distance < min_distance)
//                {
//                    min_distance = armors[j].m_distance;
//                    min_index = j;
//                }
//            }
//
//
////        if(armors.size() >= 1)
////        {
////            return -1;
////        }
//            gettimeofday(&en,NULL);
//            cout << "all time = " << en.tv_usec - st.tv_usec << endl;
//            cout << "------------------------------------------" << endl;
//
//            if(armors.size() < 1)
//                continue;
//
//
//
//            double now_time = static_cast<double>(st.tv_sec) + static_cast<double>(st.tv_usec) / 1000000.0;
//            predictor.setRecord(armors[min_index].m_center_uv.x - 320, i*0.016);
//            cout << "record = " << armors[min_index].m_center_uv.x-320 << endl;
//            double output = predictor.predict(i*0.016+0.016);
//            cout << "output = " << output << endl;
//            cout << "distance = " << armors[min_index].m_distance << endl;
//
    }





    return 0;
}