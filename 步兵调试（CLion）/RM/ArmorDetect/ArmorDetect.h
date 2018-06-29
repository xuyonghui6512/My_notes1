//
// Created by xuduo on 17-7-2.
//

#ifndef RM_ARMORDETECT_H
#define RM_ARMORDETECT_H

#include <opencv2/opencv.hpp>

#include "Armor.h"

namespace hitcrt{

class ArmorDetect {
public:
    ArmorDetect();
    ~ArmorDetect(){}
    bool Apply(std::vector<Armor>& _armors, cv::Mat& _frame, float _pitch);
    void showImage(std::vector<Armor> &_armors);
    void showResults();
    bool armor_type = true; /// small_armor=true big_armor=false

private:
    static bool parallel(LightBar bar1, LightBar bar2);
    void templateMatch(std::vector<Armor>& _armors);    //用模板匹配剔除异常
    void loadTemplate();
    void calculateXY(std::vector<Armor>& _armors);
    void calculateEjectTheta(std::vector<Armor>& _armors);


    void setPitch();
    void getPitch();

private:
    volatile float m_now_pitch;     //当前仰角,注意这个变量随时可以修改,访问需要加入锁,建议速度小于10Hz
    cv::Mat m_hereo_template;
    cv::Mat m_infantry_template;
    cv::Mat m_frame;
    float m_pitch;

};


}





#endif //RM_ARMORDETECT_H
