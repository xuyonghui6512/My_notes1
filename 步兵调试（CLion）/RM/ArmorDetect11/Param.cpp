//
// Created by xuduo on 17-7-2.
//

#include "Param.h"

namespace  hitcrt{
    float Param::MAX_PITCH  = 45*3.1416/180;        //最大的仰角，即灯柱不应该高于某个角度
    float Param::MAX_LIGHT_BAR_AREA = 600;          //灯柱最大像素数目
    float Param::MIN_LIGHT_BAR_AREA = 2;            //灯柱最小像素数目
    cv::Mat Param::KK = cv::Mat(3,3,CV_64FC1);
    cv::Mat Param::DISTORT = cv::Mat(5,1,CV_64FC1);
    cv::Mat Param::MAPX ;
    cv::Mat Param::MAPY ;
    float Param::MAX_DISTANCE = 6000.0f;
    float Param::FOCAL_LENGTH = 8.0f;            //焦距8mm镜头
    float Param::DXDY = 0.0f;
    float Param::OFFSET_X = 147.8f;              //相机原点相对于云台坐标系的X坐标
    float Param::OFFSET_Y = 46.5f;               //相机原点相对于云台坐标系的Y坐标
    float Param::OFFSET_Z = -57.0f;              //相机原点相对于云台坐标系的Z坐标
    float Param::VELOCITY = 15000.0f;//21000     //子弹速度
    float Param::OFFSET_EJECT_Z = -44.0f;        //枪口相对于转轴中心的高度差
    float Param::MAX_ROBOT_PITCH = 30.0 * CV_PI / 180;    //机器人最大仰角
    float Param::MIN_ROBOT_PITCH = -30.0 * CV_PI / 180;   //机器人最小仰角

}
