//
// Created by xuduo on 17-7-2.
//

#include "Armor.h"

using namespace std;
using namespace cv;

namespace hitcrt{
    float Armor::hereo_width = 230;      //大装甲宽度
    float Armor::hereo_height = 55;      //大装甲高度
    float Armor::infantry_width = 135;   //小装甲宽度
    float Armor::infantry_height = 55;   //小装甲高度

    void Armor::calculateRT() {

        vector<Point3f> objectPoints;  //Array of object points in the object coordinate space

        if (m_type == INFANTRY){
            objectPoints.push_back(Point3f(0,0,0));
            objectPoints.push_back(Point3f(Armor::infantry_width,0,0));
            objectPoints.push_back(Point3f(0,Armor::infantry_height,0));
            objectPoints.push_back(Point3f(Armor::infantry_width,Armor::infantry_height,0));
        }else{
            objectPoints.push_back(Point3f(0,0,0));
            objectPoints.push_back(Point3f(Armor::hereo_width,0,0));
            objectPoints.push_back(Point3f(0,Armor::hereo_height,0));
            objectPoints.push_back(Point3f(Armor::hereo_width,Armor::hereo_height,0));
        }

        vector<Point2f> imagePoints;  //Array of corresponding image points
        imagePoints.push_back(m_upper_left);
        imagePoints.push_back(m_upper_right);
        imagePoints.push_back(m_bottom_left);
        imagePoints.push_back(m_bottom_right);

        cv::solvePnP(objectPoints, imagePoints, Param::KK, Param::DISTORT, m_R, m_T);  //得到相机外参
//        cout << "m_T " << m_T<< endl;
        m_distance = cv::norm(m_T);  //通过平移向量计算装甲到相机的直线距离
    }

    void Armor::judgeHereoInfantry(bool& armor_type) {  //一个非常粗糙的版本
        if(armor_type==true)
            m_type = INFANTRY;
        else
            m_type = HERO;
//        m_type = INFANTRY;
    }


}
