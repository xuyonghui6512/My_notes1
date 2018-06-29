//
// Created by xuduo on 17-7-2.
//

#ifndef RM_ARMOR_H
#define RM_ARMOR_H

#include <opencv2/opencv.hpp>

#include "Param.h"

namespace hitcrt {
struct LightBar{
    LightBar(){}
    ~LightBar(){}
    std::vector<cv::Point> m_contour;//光柱的轮廓
    float m_contourArea;
    std::vector<cv::Point2f> m_insidePoints;//光柱内点
    cv::RotatedRect m_rotateRect;
    cv::Vec6f line_6f;
    cv::Point2f m_upper;//光柱的上部
    cv::Point2f m_bottom;//光柱的下部
};


class Armor {
public:
    Armor(){}
    ~Armor(){}
    typedef enum type{
        INFANTRY = 0,   //大装甲
        HERO            //小装甲
    }TYPE;
    static float hereo_width;
    static float hereo_height;
    static float infantry_width;
    static float infantry_height;
    TYPE m_type;
    float m_distance;   //装甲到相机的直线距离
    float m_X;            //装甲到相机的水平距离
    float m_Y;            //装甲到相机的垂直距离
    float m_theta;        //atan(Y/X)
    float m_eject_theta;   //发射时的pitch角度
    cv::Point2f m_center_uv;    //中心点在图像中的位置
    LightBar m_leftBar;
    LightBar m_rightBar;

    cv::Point2f m_upper_left;
    cv::Point2f m_upper_right;
    cv::Point2f m_bottom_left;
    cv::Point2f m_bottom_right;

    cv::Mat m_R;
    cv::Mat m_T;

    void calculateRT();
    void judgeHereoInfantry(bool& armor_type);
};
}

#endif //RM_ARMOR_H
