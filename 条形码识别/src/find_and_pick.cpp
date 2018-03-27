//
// Created by xuxuxu on 18-3-27.
//
#include "find_and_pick.h"
#include "opencv2/opencv.hpp"
namespace mybar_code{
    void CodeDetect::Zbar_It(Mat& img,Bar_code& _bar_code) {
        ImageScanner scanner;
        stringstream ss;//用于记录信息
        scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);
        Mat image = img.clone();
        Mat imageGray;
        cvtColor(image,imageGray,CV_RGB2GRAY);
        int width = imageGray.cols;
        int height = imageGray.rows;
        uchar *raw = (uchar *)imageGray.data;
        Image imageZbar(width, height, "Y800", raw, width * height);
        scanner.scan(imageZbar); //扫描条码
        Image::SymbolIterator symbol = imageZbar.symbol_begin();
        if(imageZbar.symbol_begin()==imageZbar.symbol_end())
        {
            threshold(imageGray,imageGray,200,255,1);
            raw = (uchar *)imageGray.data;
            Image imageZbar(width, height, "Y800", raw, width * height);
            scanner.scan(imageZbar); //扫描条码
            Image::SymbolIterator symbol = imageZbar.symbol_begin();
            if(imageZbar.symbol_begin()==imageZbar.symbol_end()) {
                cout << "查询条码失败，请检查图片！" << endl;
            }
            for(;symbol != imageZbar.symbol_end();++symbol)
            {
//                cout<<"类型："<<endl<<symbol->get_type_name()<<endl<<endl;
//                cout<<"条码："<<endl<<symbol->get_data()<<endl<<endl;
                ss<<"类型："<<"  "<<symbol->get_type_name()<<endl<<endl;
                ss<<"条码："<<"  "<<symbol->get_data()<<endl<<endl;
            }
        }
        for(;symbol != imageZbar.symbol_end();++symbol)
        {
//            cout<<"类型："<<endl<<symbol->get_type_name()<<endl<<endl;
//            cout<<"条码："<<endl<<symbol->get_data()<<endl<<endl;
            ss<<"类型："<<"  "<<symbol->get_type_name()<<endl;
            ss<<"条码："<<"  "<<symbol->get_data()<<endl;
        }
        _bar_code.code_info=ss.str();
        imshow("Source Image",imageGray);
        waitKey();
        imageZbar.set_data(nullptr,0);
    }
}
