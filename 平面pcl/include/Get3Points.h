//
// Created by xuxuxu on 18-7-20.
//

#ifndef PCL_VIEW_GET3POINTS_H
#define PCL_VIEW_GET3POINTS_H
#include <iostream>
#include <pcl/common/common_headers.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/console/parse.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include<opencv2/opencv.hpp>

namespace FIT_PL
{
    void Get_3Points(Eigen::Vector3d& a,Eigen::Vector3d& b,Eigen::Vector3d& c );
}
#endif //PCL_VIEW_GET3POINTS_H
