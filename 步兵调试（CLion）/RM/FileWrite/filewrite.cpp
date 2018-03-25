#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    cv::FileStorage fs("/home/kx/project/RM/Param.yaml", FileStorage::WRITE);
    int imageWidth= 5;
    int imageHeight= 10;
    fs << "imageWidth" << imageWidth;
    fs << "imageHeight" << imageHeight;
    fs.release();
}