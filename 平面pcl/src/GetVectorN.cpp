//
// Created by xuxuxu on 18-7-19.
//

#include "GetVectorN.h"
namespace FIT_PL {

    Eigen::Vector3d Get_N(Eigen::Vector3d a, Eigen::Vector3d b,
               Eigen::Vector3d c) {
        Eigen::Vector3d am, bm;
        am=a-b;
        bm=a-c;
        return am.cross(bm);//法向量

    }
}