//
// Created by xuduo on 17-7-7.
//


#include "../ArmorDetect/serialapp.h"

int main()
{
    hitcrt::SerialApp* pSerialApp = new hitcrt::SerialApp("/dev/ttyUSB0", 115200);
    std::vector<float> sendData;
    sendData.push_back(1.0);
    std::cout << "test Serial "<<std::endl;
    while(1)
    {
//        pSerialApp->send(hitcrt::SerialApp::SEND_HEART_BEAT);
        std::cout << "while 1 "<< std::endl;
        hitcrt::SerialApp::RECEIVE_FLAG eReceiveFlag;
        std::vector<float> data;
        pSerialApp->receive(eReceiveFlag, data);
        std::cout<< "eReceiveFlag= " << eReceiveFlag <<std::endl;
        std::cout<< "data.front= " <<data.front()<<std::endl;
        sleep(1);
    }
}
