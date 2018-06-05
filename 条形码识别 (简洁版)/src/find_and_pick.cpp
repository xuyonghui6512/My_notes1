//
// Created by xuxuxu on 18-3-27.
//
#include "my_bar_code.h"
#include "find_and_pick.h"
#include "opencv2/opencv.hpp"
namespace mybar_code{

    /////Zbar提取信息///////////////////////////////////////////////////////////////////////////////
    bool CodeDetect::Zbar_It(Mat& img,Bar_code& _bar_code)
    {
        ImageScanner scanner;
        stringstream ss;//用于记录信息
        scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);
        Mat image = img.clone();

        Mat imageGray;
        cvtColor(image,imageGray,CV_RGB2GRAY);
//        imshow("jj",image);
//        waitKey(0);
        int width = imageGray.cols;
        int height = imageGray.rows;
        uchar *raw = (uchar *)imageGray.data;
        Image imageZbar(width, height, "Y800", raw, width * height);
        scanner.scan(imageZbar); //扫描条码
        Image::SymbolIterator symbol = imageZbar.symbol_begin();
        if(imageZbar.symbol_begin()==imageZbar.symbol_end())
        {
            threshold(imageGray,imageGray,235,255,1);
            raw = (uchar *)imageGray.data;
            Image imageZbar(width, height, "Y800", raw, width * height);
            scanner.scan(imageZbar); //扫描条码
            Image::SymbolIterator symbol = imageZbar.symbol_begin();
            if(imageZbar.symbol_begin()==imageZbar.symbol_end()) {
                cout << "查询条码失败，请检查图片！" << endl;
                return 0;
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
        //imshow("Source Image",imageGray);
//        waitKey();
        imageZbar.set_data(nullptr,0);
        return 1;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////
    //找到所提取轮廓的中心点
//在提取的中心小正方形的边界上每隔边长长个像素提取一个点的坐标，求所提取八个点的平均坐标（即为小正方形的大致中心）

    Point CodeDetect::Center_cal(vector<vector<Point> > contours, int i)
    {
        int centerx=0,centery=0,n=contours[i].size();
        centerx = (contours[i][n/8].x + contours[i][n*2/8].x + contours[i][3*n/8].x + contours[i][4*n/8].x + contours[i][n*5/8].x + contours[i][6*n/8].x+ contours[i][7*n/8].x+contours[i][n-1].x)/8;
        centery = (contours[i][n/8].y + contours[i][n*2/8].y + contours[i][3*n/8].y +contours[i][n*4/8].y + contours[i][n*5/8].y + contours[i][6*n/8].y+ contours[i][7*n/8].y+ contours[i][n-1].y)/8;
        Point point1=Point(centerx,centery);
        return point1;
    }
   /////判断是否为二维码///////////////////////////////////////////////////////////////////////////////
   void CodeDetect::Judge_QRCode(Mat &img, Bar_code &_bar_code)
   {
       Mat src = img.clone();
       resize(src,src,Size(800,600));//标准大小
       Mat src_gray;
       Mat src_all=src.clone();
       Mat threshold_output;
       vector<vector<Point> > contours,contours2,contours3;
       vector<Vec4i> hierarchy;
       //预处理
       cvtColor( src, src_gray, CV_BGR2GRAY );
       blur( src_gray, src_gray, Size(3,3) ); //模糊，去除毛刺
       threshold( src_gray, threshold_output, 100, 255, THRESH_OTSU );
       //寻找轮廓
       //第一个参数是输入图像 2值化的
       //第二个参数是内存存储器，FindContours找到的轮廓放到内存里面。
       //第三个参数是层级，**[Next, Previous, First_Child, Parent]** 的vector
       //第四个参数是类型，采用树结构
       //第五个参数是节点拟合模式，这里是全部寻找
       findContours( threshold_output, contours, hierarchy,  CV_RETR_TREE, CHAIN_APPROX_NONE, Point(0, 0) );
       //轮廓筛选
       int c=0,ic=0,area=0;
       int parentIdx=-1;
       for( int i = 0; i< contours.size(); i++ )
       {
           //hierarchy[i][2] != -1 表示不是最外面的轮廓
           if (hierarchy[i][2] != -1 && ic==0)
           {
               parentIdx = i;
               ic++;
           }
           else if (hierarchy[i][2] != -1)
           {
               ic++;
           }
               //最外面的清0
           else if(hierarchy[i][2] == -1)
           {
               ic = 0;
               parentIdx = -1;
           }
           //找到定位点信息
           if ( ic >= 2)
           {
               contours2.push_back(contours[parentIdx]);
               ic = 0;
               parentIdx = -1;
           }
       }
       //填充定位点
       for(int i=0; i<contours2.size(); i++)
           drawContours( src_all, contours2, i,  CV_RGB(0,255,255) , 1 );
      // cout<<contours2.size()<<endl;
       /////////////////////////////////
//    vector<Rect> boundRect(contours2.size());  //定义外接矩形集合
//    vector<RotatedRect> box(contours2.size()); //定义最小外接矩形集合
//    Point2f rect[4];
       if(contours2.size()==3)//如果已经得到了
       {
           Point point[3];
           for (int i = 0; i < contours2.size(); i++) {
               point[i] = Center_cal(contours2, i);
           }

           line(src_all, point[0], point[1], Scalar(0, 0, 255), 2);
           line(src_all, point[1], point[2], Scalar(0, 0, 255), 2);
           line(src_all, point[0], point[2], Scalar(0, 0, 255), 2);
           _bar_code.m_type=mybar_code::Bar_code::two_dim_code;
           cout<<"这是二维码"<<endl;
       }
       else {
           int nn = 0;//记录次数
           for (int i = 0; i < contours2.size(); i++) {
//     box[i] = minAreaRect(Mat(contours2[i]));  //计算每个轮廓最小外接矩形
//     boundRect[i] = boundingRect(Mat(contours2[i]));
//     circle(src_all, Point(box[i].center.x, box[i].center.y), 5, Scalar(0, 255, 0), -1, 8);  //绘制最小外接矩形的中心点
//     box[i].points(rect);  //把最小外接矩形四个端点复制给rect数组
//     rectangle(src_all, Point(boundRect[i].x, boundRect[i].y),
//                    Point(boundRect[i].x + boundRect[i].width,
//                     boundRect[i].y + boundRect[i].height), Scalar(0, 255, 0), 2, 8);
               for (int j = 0; j < contours2.size(); j++) {
                   //cout << double(contours2[i].size()) / double(contours2[j].size()) << endl;
                   if (double(contours2[i].size()) / double(contours2[j].size()) < 1.1 &&
                       double(contours2[i].size()) / double(contours2[j].size()) > 0.9) {
                       // cout<<double(contours2[i].size())/double(contours2[j].size())<<endl;  //运用三个正方形的轮廓点
                       nn++;
                   }
               }
               if (nn == 3) {
                   contours3.push_back(contours2[i]);
                   _bar_code.m_type=mybar_code::Bar_code::two_dim_code;
                   cout<<"这是二维码"<<endl;
               }
               if(nn>3) ////////注意将来要在这里处理大于3的情况！！！！！
               {
                   continue;
               }
               nn = 0;
//     for(int j=0; j<4; j++)
//     {
//     line(src_all, rect[j], rect[(j+1)%4], Scalar(0, 0, 255), 2, 8);  //绘制最小外接矩形每条边
//     }
           }
           ////////////////////
           //连接定位点
          // cout << contours3.size();
           Point point[3];
           for (int i = 0; i < contours3.size(); i++) {
               point[i] = Center_cal(contours3, i);
           }

           line(src_all, point[0], point[1], Scalar(0, 0, 255), 2);
           line(src_all, point[1], point[2], Scalar(0, 0, 255), 2);
           line(src_all, point[0], point[2], Scalar(0, 0, 255), 2);
       }

//       imshow( "结果", src_all );
//       waitKey(0);
   }



    //寻找一副图中的二维码定位点/////////////////////////////////////////////////////////////////////
    bool CodeDetect::Find_QRCode_Oriented_Point(Mat &_img,Point2f& oriented_pt)
    {
        resize(_img, _img, Size(800, 600));//标准大小  //实际情况实际分析
        Mat src = _img.clone();
        resize(src, src, Size(800, 600));//标准大小
        Mat src_gray;
        Mat src_all = src.clone();
        Mat threshold_output;
        vector<vector<Point> > contours1, contours2, contours3;
        vector<Vec4i> hierarchy;
        //预处理
        cvtColor(src, src_gray, CV_BGR2GRAY);
        blur(src_gray, src_gray, Size(3, 3)); //模糊，去除毛刺
        threshold(src_gray, threshold_output, 100, 255, THRESH_OTSU);
        //寻找轮廓
        //第一个参数是输入图像 2值化的
        //第二个参数是内存存储器，FindContours找到的轮廓放到内存里面。
        //第三个参数是层级，**[Next, Previous, First_Child, Parent]** 的vector
        //第四个参数是类型，采用树结构
        //第五个参数是节点拟合模式，这里是全部寻找
        findContours(threshold_output, contours1, hierarchy, CV_RETR_TREE, CHAIN_APPROX_NONE, Point(0, 0));
        //轮廓筛选
        int c = 0, ic = 0, area = 0;
        int parentIdx = -1;
        Point2f point[3];
        for (int i = 0; i < contours1.size(); i++) {
            //hierarchy[i][2] != -1 表示不是最外面的轮廓
            if (hierarchy[i][2] != -1 && ic == 0) {
                parentIdx = i;
                ic++;
            } else if (hierarchy[i][2] != -1) {
                ic++;
            }
                //最外面的清0
            else if (hierarchy[i][2] == -1) {
                ic = 0;
                parentIdx = -1;
            }
            //找到定位点信息
            if (ic >= 2) {
                contours2.push_back(contours1[parentIdx]);
                ic = 0;
                parentIdx = -1;
            }
        }
        //填充定位点
//        for (int i = 0; i < contours2.size(); i++)
//            drawContours(src_all, contours2, i, CV_RGB(0, 255, 255), 5);
        if (contours2.size() == 3)//如果已经得到了
        {
            for (int i = 0; i < contours2.size(); i++) {
                point[i] = Center_cal(contours2, i);
            }

//           line(src_all, point[0], point[1], Scalar(0, 0, 255), 2);
//           line(src_all, point[1], point[2], Scalar(0, 0, 255), 2);
//           line(src_all, point[0], point[2], Scalar(0, 0, 255), 2);
//           cout<<"这是二维码"<<endl;
            float max_x, max_y, min_x, min_y;
            max_x = max_y = 0;
            min_x = min_y = 10000;
            for (int i = 0; i < 3; i++) {
                if (min_x > point[i].x)
                    min_x = point[i].x;
                if (min_y > point[i].y)
                    min_y = point[i].y;
                if (max_x < point[i].x)
                    max_x = point[i].x;
                if (max_y < point[i].y)
                    max_y = point[i].y;
            }
            oriented_pt.x = (max_x + min_x) / 2;
            oriented_pt.y = (max_y + min_y) / 2;
            return true;

        } else {
            int nn = 0;//记录次数
            for (int i = 0; i < contours2.size(); i++) {
//     box[i] = minAreaRect(Mat(contours2[i]));  //计算每个轮廓最小外接矩形
//     boundRect[i] = boundingRect(Mat(contours2[i]));
//     circle(src_all, Point(box[i].center.x, box[i].center.y), 5, Scalar(0, 255, 0), -1, 8);  //绘制最小外接矩形的中心点
//     box[i].points(rect);  //把最小外接矩形四个端点复制给rect数组
//     rectangle(src_all, Point(boundRect[i].x, boundRect[i].y),
//                    Point(boundRect[i].x + boundRect[i].width,
//                     boundRect[i].y + boundRect[i].height), Scalar(0, 255, 0), 2, 8);
                for (int j = 0; j < contours2.size(); j++) {
                    //cout << double(contours2[i].size()) / double(contours2[j].size()) << endl;
                    if (double(contours2[i].size()) / double(contours2[j].size()) < 1.1 &&
                        double(contours2[i].size()) / double(contours2[j].size()) > 0.9) {
                        // cout<<double(contours2[i].size())/double(contours2[j].size())<<endl;  //运用三个正方形的轮廓点
                        nn++;
                    }
                }
                if (nn == 3) {
                    contours3.push_back(contours2[i]);
                    cout << "这是二维码" << endl;
                }
                if (nn > 3) ////////注意将来要在这里处理大于3的情况！！！！！
                {
                    continue;
                }
                nn = 0;
//     for(int j=0; j<4; j++)
//     {
//     line(src_all, rect[j], rect[(j+1)%4], Scalar(0, 0, 255), 2, 8);  //绘制最小外接矩形每条边
//     }
            }
            ////////////////////
            //连接定位点
            // cout << contours3.size();
//
            if(contours3.size()==3) {
                for (int i = 0; i < contours3.size(); i++) {
                    point[i] = Center_cal(contours3, i);
                }
//
//           line(src_all, point[0], point[1], Scalar(0, 0, 255), 2);
//           line(src_all, point[1], point[2], Scalar(0, 0, 255), 2);
//           line(src_all, point[0], point[2], Scalar(0, 0, 255), 2);

                //寻找定位点
                float max_x, max_y, min_x, min_y;
                max_x = max_y = 0;
                min_x = min_y = 10000;
                for (int i = 0; i < 3; i++) {
                    if (min_x > point[i].x)
                        min_x = point[i].x;
                    if (min_y > point[i].y)
                        min_y = point[i].y;
                    if (max_x < point[i].x)
                        max_x = point[i].x;
                    if (max_y < point[i].y)
                        max_y = point[i].y;
                }
                oriented_pt.x = (max_x + min_x) / 2;
                oriented_pt.y = (max_y + min_y) / 2;
                cout<<"oritented_pt:("<<oriented_pt.x<<","<<oriented_pt.y<<")"<<endl;
                return true;
            }
        }
        return false;
    }
    //找到条形码的定位旋转矩形//////////////////////////////////////////////////////////////////////////
    bool CodeDetect::barcode_oriented(Mat &img,RotatedRect& findrect) {
        Mat srcImg = img.clone();
        Mat srcGray;
        cvtColor(srcImg, srcGray, CV_RGB2GRAY);

        Mat grad_x, grad_y;
        Sobel(srcGray, grad_x, CV_32F, 1, 0, -1);//求x方向梯度
        //imshow("grad_x", grad_x);
        Sobel(srcGray, grad_y, CV_32F, 0, 1, -1);//y方向梯度
        //imshow("grad_y", grad_y);
        Mat gradient;
        subtract(grad_x, grad_y, gradient);
        //imshow("gradient1", gradient);
        convertScaleAbs(gradient, gradient);//得到包含高水平梯度和低竖直梯度的图像区域
//       imshow("gradient", gradient);
        Mat blur_img;
        blur(gradient, blur_img, Size(9, 9));//模糊
//        imshow("blur",blur_img);
        Mat threshold_img;
        int thres=245;//thres用来控制阈值，
        int count=0;//count用来计高阈值时的亮点数
        int timer=4;
        while (timer--) {
            threshold(blur_img, threshold_img, thres, 255, CV_THRESH_BINARY); //首先选择较高阈值进行定位  //245
            for(int i=0;i<threshold_img.rows;i++)
            {
                uchar* data=threshold_img.ptr<uchar>(i);
                for(int j=0;j<threshold_img.cols;j++)
                {
                    if(data[j]==255)
                        count++;
                }
            }
            cout<<"亮点数"<<count<<endl;
            if(count>500)
                break;
            else {
                count = 0;
                thres=thres-15;
            }
        }
//        imshow("high_threshold_img", threshold_img);
        Mat kernel;
        kernel = getStructuringElement(MORPH_RECT, Size(33, 11));//需要找到最佳值////
        Mat close_img;
        morphologyEx(threshold_img, close_img, MORPH_CLOSE, kernel);//闭运算
        //imshow("close_img1", close_img);
        Mat element = getStructuringElement(MORPH_RECT, Size(11, 11));//得到自定义核
        erode(close_img, close_img, element);
        Mat element1 = getStructuringElement(MORPH_RECT, Size(33, 33));//得到自定义核
        dilate(close_img, close_img, element1);
//        imshow("close_img2", close_img);
        std::vector<std::vector<Point> > contours;
        std::vector<Vec4i> hierarchy;
        findContours(close_img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);//得到轮廓
//         imshow("high_close_img3", close_img);
        RotatedRect place_rect;//定位矩形
        /*找到最大轮廓*/
        //////////////////////////////////高阈值定位
        if(contours.size()>0) {
            std::vector<Point> place_Contour;
            for (int i = 0; i < contours.size(); i++) {
                if (place_Contour.size() < contours[i].size())
                    place_Contour = contours[i];
            }


            place_rect = minAreaRect(place_Contour);
            cout << "定位点：" << place_rect.center << endl;
//            circle(img,place_rect.center,5,Scalar(0,0,255));
//            imshow("Point",img);
        }
        else{
            return false;
        }
        threshold(blur_img, threshold_img, thres-25, 255, CV_THRESH_BINARY);//放宽阈值寻找条形码轮廓 //230
       // imshow("thr_low",threshold_img);
        morphologyEx(threshold_img, close_img, MORPH_CLOSE, kernel);//闭运算
        //imshow("thr1",close_img);
        erode(close_img, close_img, element);
        dilate(close_img, close_img, element1);
        findContours(close_img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        cout<<img.cols<<"////222222222222222"<<endl;
        ////////////////////////////////////////
        if(contours.size()>0&&place_rect.center.x>100&&
                place_rect.center.y>50&&place_rect.center.x<img.cols-100
                &&place_rect.center.y<img.rows-50) {
            int num, num1;
            std::vector<Point> max_Contour1, max_Contour2, max_Contour3;//最大轮廓与次大轮廓以及第三大轮廓
            std::vector<vector<Point> > max_Contour;

            for (int i = 0; i < contours.size(); i++) {
                if (max_Contour1.size() < contours[i].size()) {
                    max_Contour1 = contours[i];
                    num = i;
                }

            }
            max_Contour.push_back(max_Contour1);
            for (int i = 0; i < contours.size(); i++) {
                if (max_Contour2.size() < contours[i].size()) {
                    if (i != num) {
                        max_Contour2 = contours[i];
                        num1 = i;
                    }
                }

            }
            if (float(max_Contour2.size()) / float(max_Contour1.size()) > 0.7)
                max_Contour.push_back(max_Contour2);
            for (int i = 0; i < contours.size(); i++) {
                if (max_Contour3.size() < contours[i].size()) {
                    if (i != num && i != num1) {
                        max_Contour3 = contours[i];
                    }
                }

            }
            if (float(max_Contour3.size()) / float(max_Contour2.size()) > 0.7)
                max_Contour.push_back(max_Contour3);
            cout << "轮廓的数目：" << max_Contour.size() << endl;
            RotatedRect bar_code_rect[3];//旋转矩阵
            int findnum;
            float firststandard = 10000000;
            if (max_Contour1.size() < 10) {
                std::cout << "这不是条形码" << std::endl;
            } else {
                for (int j = 0; j < max_Contour.size(); j++) {

                    bar_code_rect[j] = minAreaRect(max_Contour[j]);//最大轮廓的最小外接矩形
                    float distance = (place_rect.center.x - bar_code_rect[j].center.x) *
                                     (place_rect.center.x - bar_code_rect[j].center.x)
                                     + (place_rect.center.y - bar_code_rect[j].center.y) *
                                       (place_rect.center.y - bar_code_rect[j].center.y);
                    if (distance < firststandard) {
                        firststandard = distance;
                        findnum = j;
                    }

                    Point2f rect[4];//用来取外接矩形的四个定点
                    circle(srcGray, Point(bar_code_rect[j].center.x,
                                          bar_code_rect[j].center.y), 5,
                           Scalar(0, 255, 0), -1, 8);
                    bar_code_rect[j].points(rect);  //把最小外接矩形四个端点复制给rect数组
                    cout << bar_code_rect[j].angle << endl;
                    for (int k = 0; k < 4; k++) {
                        line(srcImg, rect[k], rect[(k + 1) % 4], Scalar(0, 0, 255), 2, 8);  //绘制最小外接矩形每条边
                    }
                }
            }
            Point2f rect_dst[4];//用来取外接矩形的四个定点
            circle(srcGray, Point(bar_code_rect[findnum].center.x,
                                  bar_code_rect[findnum].center.y), 5,
                   Scalar(0, 255, 0), -1, 8);
            bar_code_rect[findnum].points(rect_dst);  //把最小外接矩形四个端点复制给rect数组
            cout << bar_code_rect[findnum].angle << endl;
            for (int k = 0; k < 4; k++) {
                line(srcImg, rect_dst[k], rect_dst[(k + 1) % 4], Scalar(0, 255, 255), 2, 8);  //绘制最小外接矩形每条边
            }
            // imshow("origin",srcImg);
            findrect= bar_code_rect[findnum];//
            cout<<"11111111111111111111111111 "<<findrect.size.area()<<endl;
            if(findrect.size.area()>50000||findrect.size.area()<14000)
                return false;
            return true;
        }
        else
            return false;

    }
///////////////////////////对找到的旋转矩形区域进行旋转矫正///////////////////////////////////////////////
    bool CodeDetect::Rotate_and_Find_barcode(RotatedRect& findrect,Mat& input,Mat& output)
    {
        Point2f rect_dst[4],rect_rotated[4];
        findrect.points(rect_dst);
        float  angle=findrect.angle;
        if (0< abs(angle) && abs(angle)<=45)
            angle = angle;//负数，顺时针旋转
        else if (45< abs(angle) && abs(angle)<90)
            angle = 90 -  abs(angle);//正数，逆时针旋转
        Point2f center = findrect.center;  //定义旋转中心坐标
        double angle0 = angle;
        double scale = 1;
        Mat roateM(Size(2, 3), CV_32FC1);
        cout<<"//*"<<1<<endl;
        roateM = getRotationMatrix2D(center, angle0, scale);  //获得旋转矩阵,顺时针为负，逆时针为正
        cout<<"//*"<<2<<endl;
        Mat rotatedImg1,rotatedImg2;
        warpAffine(input, rotatedImg1, roateM, input.size()); //仿射变换
        cout<<"//*"<<3<<endl;
        for(int i=0;i<4;i++)//找到对应的旋转点//
        {
            rect_rotated[i].x=(rect_dst[i].x-center.x)*cos(angle*CV_PI/180)+
                              (rect_dst[i].y-center.y)*sin(angle*CV_PI/180)+center.x;
            rect_rotated[i].y=-(rect_dst[i].x-center.x)*sin(angle*CV_PI/180)+
                              (rect_dst[i].y-center.y)*cos(angle*CV_PI/180)+center.y;
//            circle(rotatedImg1,rect_rotated[i],5,Scalar(255,255,255));
//            circle(rotatedImg1,rect_dst[i],10,Scalar(255,255,255));

        }
        cout<<"//*"<<4<<endl;
        /*寻找矩形4个定点对应的点*/
        float min_x=10000,min_y;
        min_y=10000;
        float max_x=0;
        float max_y=0;
        //找到左上角的点
        for(int i=0;i<4;i++)
        {
            if(rect_rotated[i].x<min_x)
                min_x=rect_rotated[i].x;
            if(rect_rotated[i].y<min_y)
                min_y=rect_rotated[i].y;
            if(rect_rotated[i].x>max_x)
                max_x=rect_rotated[i].x;
            if(rect_rotated[i].y>max_y)
                max_y=rect_rotated[i].y;

        }

        cout<<"左上角的点为：（"<<min_x<<","<<min_y<<")"<<endl;
        cout<<"右下角的点为：（"<<max_x<<","<<max_y<<")"<<endl;
        if((max_x-min_x)<(max_y-min_y))
        {
            roateM = getRotationMatrix2D(center, angle0-90, scale);
            warpAffine(input, rotatedImg2, roateM, input.size()); //仿射变换
            angle=angle-90;
            for(int i=0;i<4;i++)//找到对应的旋转点//
            {
                rect_rotated[i].x=(rect_dst[i].x-center.x)*cos(angle*CV_PI/180)+
                                  (rect_dst[i].y-center.y)*sin(angle*CV_PI/180)+center.x;
                rect_rotated[i].y=-(rect_dst[i].x-center.x)*sin(angle*CV_PI/180)+
                                  (rect_dst[i].y-center.y)*cos(angle*CV_PI/180)+center.y;
//                circle(rotatedImg2,rect_rotated[i],5,Scalar(255,255,255));
//                circle(rotatedImg2,rect_dst[i],10,Scalar(255,255,255));

            }
            cout<<"//*"<<5<<endl;
            min_x=10000;
            min_y=10000;
            max_x=0;
            max_y=0;
            for(int i=0;i<4;i++)
            {
                if(rect_rotated[i].x<min_x)
                    min_x=rect_rotated[i].x;
                if(rect_rotated[i].y<min_y)
                    min_y=rect_rotated[i].y;
                if(rect_rotated[i].x>max_x)
                    max_x=rect_rotated[i].x;
                if(rect_rotated[i].y>max_y)
                    max_y=rect_rotated[i].y;

            }
            cout<<"//*"<<6<<endl;
        }
        Mat theObject;
        Rect roi;//设置roi
        int tt=60;
        if(0 <= min_x-tt-5 &&
           max_x+tt+5 <= theObject.cols &&
           0 <= min_y-tt-5 &&
           max_y+tt+5 <= theObject.rows)
//            output=theObject(Rect(min_x-tt,min_y-tt,max_x-min_x+2*tt,max_y-min_y+2*tt));
            roi=Rect(min_x-tt,min_y-tt,max_x-min_x+2*tt,max_y-min_y+2*tt);
        else
            roi=Rect(min_x,min_y,max_x-min_x,max_y-min_y);
        if((0 <= roi.x && 0 <= roi.width &&
                roi.x + roi.width <= input.cols &&
                0 <= roi.y && 0 <= roi.height &&
                roi.y + roi.height <= input.rows)) {
            if (rotatedImg2.empty() && (!rotatedImg1.empty())) {
                //imshow("旋转后的图", rotatedImg1);
                theObject = rotatedImg1.clone();
                output=theObject(roi);
                return true;
            } else if (!rotatedImg2.empty()) {
                // imshow("旋转后的图1", rotatedImg2);
                theObject = rotatedImg2.clone();

                output = theObject(roi);

                return true;
            } else
                return false;
            /////////////////////////////////////////////////
            ///////////////////寻找更为宽泛的ROI区域///////////
        }
        cout<<"//*"<<7<<endl;
        return false;


    }


    ///////////////寻找二维码的旋转定位矩形//////////////////
    bool CodeDetect::Find_QRCode_RotateRect(Mat& inputImg, Point2f oritented_pt,RotatedRect& output)
    {
        Mat srcImg=inputImg.clone();
        Mat srcGray;
        cvtColor(srcImg,srcGray,CV_RGB2GRAY);

        blur(srcGray,srcGray,Size(3,3));
        //imshow("srcGray",srcGray);
        Mat threshold_img,close_img;
        threshold(srcGray,threshold_img,180,255,CV_THRESH_BINARY);
        //imshow("二值",threshold_img);
        waitKey();
        Mat element=getStructuringElement(MORPH_RECT,Size(7,7));//得到自定义核
        erode(threshold_img,threshold_img,element);
        Mat element1=getStructuringElement(MORPH_RECT,Size(3,3));//得到自定义核
        dilate(threshold_img,close_img,element1);
        //imshow("222",threshold_img);

        std::vector<std::vector<Point> > contours1,contours2;
        std::vector<Vec4i> hierarchy;
        findContours(close_img,contours1,hierarchy,RETR_LIST,CHAIN_APPROX_NONE);
        for(int i=0;i<contours1.size();i++)
        {
            if(contours1[i].size()>200) {
                contours2.push_back(contours1[i]);
                drawContours(inputImg,contours1,i,Scalar(255,0,0),1);
            }
        }
        cout<<contours2.size()<<endl;
        float min_distance=100000;
        int findnum;
        for(int i=0;i<contours2.size();i++) {
            for (int j=0;j<contours2[i].size();j++){
                if(min_distance>(abs(contours2[i][j].x-oritented_pt.x)+
                                 abs(contours2[i][j].y-oritented_pt.y)))
                {
                    min_distance=abs(contours2[i][j].x-oritented_pt.x)+
                                 abs(contours2[i][j].y-oritented_pt.y);
                    findnum=i;
                }
            }
        }
        cout<<findnum<<endl;
//        drawContours(inputImg,contours2,findnum,Scalar(0,0,125),5);
        output = minAreaRect(contours2[findnum]);//最大轮廓的最小外接矩形
        Point2f rect[4];//用来取外接矩形的四个定点
        Point2f rectlftop,rectrhtop,rectlfub,rectrhub;
        output.points(rect);  //把最小外接矩形四个端点复制给rect数组

//        for (int j = 0; j < 4; j++) {
//            line(inputImg, rect[j], rect[(j + 1) % 4], Scalar(0, 0, 255), 2, 8);  //绘制最小外接矩形每条边
//        }
        imshow("1",inputImg);
        return true;
    }
}





