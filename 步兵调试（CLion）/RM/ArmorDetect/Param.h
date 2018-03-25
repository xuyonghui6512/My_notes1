//
// Created by xuduo on 17-7-2.
//

#ifndef RM_PARAM_H
#define RM_PARAM_H

#include <opencv2/opencv.hpp>

namespace hitcrt {
class Param {
public:
    typedef enum{
        RED = 0,
        BLUE
    }eFIELD;

    static float MAX_PITCH;     //最大的仰角，即灯柱不应该高于某个角度
    static float MAX_ROBOT_PITCH;   //机器人最大仰角
    static float MIN_ROBOT_PITCH;   //机器人最小仰角
    static float MAX_LIGHT_BAR_AREA;    //灯柱最大像素数目
    static float MIN_LIGHT_BAR_AREA;    //灯柱最小像素数目
    static cv::Mat KK;               //内参矩阵
    static cv::Mat DISTORT;          //畸变参数
    static cv::Mat MAPX;
    static cv::Mat MAPY;
    static float MAX_DISTANCE;
    static float FOCAL_LENGTH;   //焦距8mm镜头
    static float DXDY;
    static float OFFSET_X;  //相机原点相对于云台坐标系的X坐标
    static float OFFSET_Y;  //相机原点相对于云台坐标系的Y坐标
    static float OFFSET_Z;  //相机原点相对于云台坐标系的Z坐标
    static float VELOCITY;  //子弹速度
    static float OFFSET_EJECT_Z;    //枪口相对于转轴中心的高度差
};
}

#endif //RM_PARAM_H
