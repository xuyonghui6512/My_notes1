//
// Created by xiaoyang on 18-4-20.
//

#include "camera_pylon.h"

using namespace std;
using namespace cv;

camera_pylon::camera_pylon(Camera_t& camera) {

    FileStorage fs;
    fs.open("/home/base2/CLionProjects/TestBasler/camera_pylon_8mm_21630206.yml",cv::FileStorage::READ);
    fs["image_width"] >> IMAGE_WIDTH;
    fs["image_height"] >> IMAGE_HEIGHT;
    fs["frame_fps"] >> FRAME_FPS;
    fs["explosure"] >> INIT_EXPOSURE_TIME;
    //确定输出像素格式
    formatConverter.OutputPixelFormat = PixelType_BGR8packed;
    // 创建一个Pylonlmage后续将用来创建OpenCV images
    Pylon::PylonAutoInitTerm autoInitTerm;              /** 优先保证其最先开始初始化  **/
    camera.Open();
    if(camera.IsOpen()){
        cout<<"camera open successfully"<<endl;
    } else{
        cout<<"camera open failed"<<endl;
    }
    camera.PixelFormat.SetValue(PixelFormat_BayerRG8);
    camera.BalanceWhiteAuto.SetValue(BalanceWhiteAuto_Continuous);
    if(GAMMA_ENABLE)    /**启用 GAMMA 校正 **/
    {
        camera.GammaEnable.SetValue(true);
        camera.GammaSelector.SetValue(GammaSelector_User);
        camera.Gamma.SetValue(GAMMA_VALUE);

    }
    else
    {
        camera.GammaEnable.SetValue(false);
    }
    if(GAIN_ENABLE)
    {
        if(GAIN_AUTO)
        {
            camera.GainAuto.SetValue(GainAuto_Continuous);
        }
        else
        {
            camera.GainAuto.SetValue(GainAuto_Off);
            camera.GainSelector.SetValue(GainSelector_DigitalAll);
            camera.GainRaw.SetValue(GAIN_INIT_VALUE);
        }
    }
    else
    {
        camera.GainAuto.SetValue(GainAuto_Off);
        camera.GainSelector.SetValue(GainSelector_DigitalAll);
        camera.GainRaw.SetValue(0);
    }
    camera.GevSCPSPacketSize.SetValue(9000);
    camera.Width.SetValue(IMAGE_WIDTH);
    camera.Height.SetValue(IMAGE_HEIGHT);
    camera.OffsetY.SetValue(FRONT_YOFFSET_INIT);
    camera.ExposureMode.SetValue(ExposureMode_Timed);
    camera.ExposureTimeAbs.SetValue(INIT_EXPOSURE_TIME);
    camera.AcquisitionMode.SetValue(AcquisitionMode_Continuous);
    camera.AcquisitionFrameRateEnable.SetValue(false);//true
    camera.AcquisitionFrameRateAbs.SetValue(FRAME_FPS);
    camera.StartGrabbing(GrabStrategy_LatestImages);//GrabStrategy_LatestImages

}

Mat camera_pylon::grab(Camera_t& camera) {
    camera.RetrieveResult( 5000, ptrGrabResult, TimeoutHandling_ThrowException);//1000000
    Mat img_temp;
    formatConverter.Convert(pylonImage, ptrGrabResult);
    img_temp = cv::Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3,
                           (uint8_t *) pylonImage.GetBuffer());
    return img_temp;
}

camera_pylon::~camera_pylon() = default;
