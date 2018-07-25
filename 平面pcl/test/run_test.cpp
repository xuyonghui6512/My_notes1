
#include "GetVectorN.h"
#include"Get3Points.h"

int main(int argc, char **argv) {

    while(1) {
        Eigen::Vector3d N, a, b, c;
        FIT_PL::Get_3Points(a, b, c);
        N = FIT_PL::Get_N(a, b, c);
        std::cout << N << endl;
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr pc_ptr(new pcl::PointCloud<pcl::PointXYZRGB>);
        pc_ptr->width = 10000;
        pc_ptr->height = 1;
        pc_ptr->is_dense = false;
        pc_ptr->resize(pc_ptr->height * pc_ptr->width);
        size_t num = pc_ptr->size();
        for (size_t i = 0; i < num; ++i) {
            pc_ptr->points[i].x = rand() / (RAND_MAX + 1.0);
            pc_ptr->points[i].y = rand() / (RAND_MAX + 1.0);
            pc_ptr->points[i].z =
                    (N[0] * (a[0] - pc_ptr->points[i].x) + N[1] * (a[1] - pc_ptr->points[i].y)) / N[2] + a[2];
            pc_ptr->points[i].r = 255;
            pc_ptr->points[i].g = 255;
            pc_ptr->points[i].b = 255;

        }

        pcl::visualization::CloudViewer viewer("test");
        viewer.showCloud(pc_ptr);
        while (!viewer.wasStopped()) {
            if(cv::waitKey(27) >= 0)
            break;


        };

        //return 0;
    }


}