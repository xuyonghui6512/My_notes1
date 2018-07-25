//
// Created by xiaoyang on 18-4-20.
//

#ifndef RM_CAMERA_PYLON_H
#define RM_CAMERA_PYLON_H

#endif //RM_CAMERA_PYLON_H

#include <pylon/PylonIncludes.h>
#include <pylon/gige/BaslerGigEInstantCamera.h>
#include "opencv/cv.hpp"
#include "opencv2/opencv.hpp"

using namespace Basler_GigECameraParams;
using namespace Pylon;
using namespace std;
using namespace cv;
typedef Pylon::CBaslerGigEInstantCamera Camera_t;

class camera_pylon{

public:
    camera_pylon(Camera_t& camera);
    ~camera_pylon();
    Mat grab(Camera_t& camera);
    int IMAGE_WIDTH = 1280;
    int IMAGE_HEIGHT = 720;
    int FRAME_FPS = 120;
    int explosure;
    CDeviceInfo info;
    String_t DEVICE_NUM;
    CBaslerGigEGrabResultPtr ptrGrabResult;
    CImageFormatConverter formatConverter;
    CPylonImage pylonImage;
private:
    bool GAMMA_ENABLE = true;
    bool GAIN_ENABLE = false;
    float GAMMA_VALUE = 0.7;
    bool GAIN_AUTO = false;
    int GAIN_INIT_VALUE = 0;
    int INIT_EXPOSURE_TIME = 1000;
    float FRONT_YOFFSET_INIT = 0;
    int exitCode = 0;


};