//
// Created by xuduo on 17-7-2.
//

#include "Param.h"

namespace  hitcrt{
    float Param::MAX_PITCH  = 45*3.1416/180;
    float Param::MAX_LIGHT_BAR_AREA = 600;
    float Param::MIN_LIGHT_BAR_AREA = 2;
    cv::Mat Param::KK = cv::Mat(3,3,CV_64FC1);
    cv::Mat Param::DISTORT = cv::Mat(5,1,CV_64FC1);
    cv::Mat Param::MAPX ;
    cv::Mat Param::MAPY ;
    float Param::MAX_DISTANCE = 6000.0f;
    float Param::FOCAL_LENGTH = 8.0f;
    float Param::DXDY = 0.0f;
    float Param::OFFSET_X = 147.8f;
    float Param::OFFSET_Y = 46.5f;
    float Param::OFFSET_Z = -57.0f;
    float Param::VELOCITY = 15000.0f;//21000
    float Param::OFFSET_EJECT_Z = -44.0f;
    float Param::MAX_ROBOT_PITCH = 30.0 * CV_PI / 180;
    float Param::MIN_ROBOT_PITCH = -30.0 * CV_PI / 180;

}
