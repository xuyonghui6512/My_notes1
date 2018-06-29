//
// Created by xuduo on 17-7-2.
//

#include "ArmorDetect.h"
#include <sys/time.h>

using namespace std;
using namespace cv;

namespace hitcrt{

    ArmorDetect::ArmorDetect(){
        cv::FileStorage fs;
        fs.open("/home/xuxuxu/步兵调试（CLion）/RM/camera.yml", cv::FileStorage::READ);
        assert(fs.isOpened());
        fs["camera_matrix"] >> Param::KK;
        fs["distortion_coefficients"] >> Param::DISTORT;
        Param::DXDY = (Param::KK.at<double>(0,0) + Param::KK.at<double>(1,1)) / 2.0;
        loadTemplate();
#ifdef _DEBUG
        cout << "KK = " << Param::KK;
        cout << "DISTORT = " << Param::DISTORT;
#endif
    }
// 载入模板
    void ArmorDetect::loadTemplate() {
        m_hereo_template = imread("/home/xuxuxu/步兵调试（CLion）/RM/template/big_template.bmp");
        cvtColor(m_hereo_template, m_hereo_template, CV_RGB2GRAY);
        cv::threshold(m_hereo_template, m_hereo_template, 128, 255, THRESH_OTSU);

        m_infantry_template = imread("/home/xuxuxu/步兵调试（CLion）/RM/template/small_template.bmp");
        cvtColor(m_infantry_template, m_infantry_template, CV_RGB2GRAY);
        cv::threshold(m_infantry_template, m_infantry_template, 128, 255, THRESH_OTSU);

        m_RFID_template = imread("/home/xuxuxu/步兵调试（CLion）/RM/template/small_template_heng.bmp");
        cvtColor(m_RFID_template, m_RFID_template, CV_RGB2GRAY);
        cv::threshold(m_RFID_template, m_RFID_template, 128, 255, THRESH_OTSU);
    }

// 模板匹配
    void ArmorDetect::templateMatch(std::vector<Armor> &_armors) {
//        for (int i = 0; i < _armors.size(); ++i) {

        for(std::vector<Armor>::iterator it = _armors.begin(); it != _armors.end();)  //迭代器，遍历并选择序列中的对象
        {
            Armor& armor_tmp = *it;
            std::vector<cv::Point2f> corners;
            corners.push_back(armor_tmp.m_upper_left);
            corners.push_back(armor_tmp.m_upper_right);
            corners.push_back(armor_tmp.m_bottom_left);
            corners.push_back(armor_tmp.m_bottom_right);

            Rect imgRect  = cv::boundingRect(corners);  //输入点集，得到外接矩形

            std::vector<cv::Point2f> dst_pt;
            cv::Mat template_img;
            if(armor_tmp.m_type == Armor::RFID){
                template_img = m_RFID_template;
            }
            else if(armor_tmp.m_type == Armor::INFANTRY) {
                template_img = m_infantry_template;
            }else{
                template_img = m_hereo_template;
            }

            dst_pt.push_back(Point2f(0,0));
            dst_pt.push_back(Point2f(template_img.cols,0));
            dst_pt.push_back(Point2f(0,template_img.rows));
            dst_pt.push_back(Point2f(template_img.cols, template_img.rows));

            //根据输入和输出点获得图像透视变换的矩阵，这里的输出点是模板图上的点
            cv::Mat transmtx = cv::getPerspectiveTransform(corners, dst_pt);


            cv::Mat img_perspective;
            cv::warpPerspective(m_frame, img_perspective, transmtx, template_img.size());
            cvtColor(img_perspective, img_perspective, CV_RGB2GRAY);
            cv::threshold(img_perspective, img_perspective, 128, 255, THRESH_OTSU);

            assert(img_perspective.size() == template_img.size());


            int non_zero_num = 0;
            for (int j = 0; j < img_perspective.rows; ++j) {
                uchar* p1 = img_perspective.ptr<uchar>(j);
                uchar* p2 = template_img.ptr<uchar>(j);
                for (int k = 0; k < img_perspective.cols; ++k) {
                    if(p1[k]*p2[k] + (255-p1[k])*(255-p2[k]) > 0)//检验像素相同的点
                        ++non_zero_num;
                }
            }

            float ratio = non_zero_num*1.0 / template_img.cols / template_img.rows;//重复率

//            cout << "non_zero_num = " << non_zero_num << endl;
//            cout << "ratio" << ratio << endl;
            if(ratio < 0.80)
            {
                _armors.erase(it);//忽略目标
            } else{
                ++it;
            }


//#ifdef _DEBUG
//            imshow("raw", m_frame(imgRect));
//            imshow("perspective", img_perspective);
//            waitKey(0);
//#endif

        }


    }

    void ArmorDetect::calculateXY(std::vector<Armor> &_armors) {



        for (int i = 0; i < _armors.size(); ++i) {
            Armor& armor_tmp = _armors[i];
            float theta = -atan((armor_tmp.m_center_uv.y - 240) / Param::DXDY );
//            cout << "theta = " << theta << endl;
//            cout << "m_pitch = " << m_pitch << endl;
//            cout << "m_distance = "<< armor_tmp.m_distance << endl;
            float Fcx = armor_tmp.m_distance * cos(theta) + Param::OFFSET_X;
            float Fcy = armor_tmp.m_distance * sin(theta) + Param::OFFSET_Z;
            armor_tmp.m_X = cos(-m_pitch)*Fcx + sin(-m_pitch) * Fcy;
            armor_tmp.m_Y = -sin(-m_pitch)*Fcx + cos(-m_pitch) * Fcy;
//            cout << "Fcx = " << Fcx << endl;
//            cout << "Fcy = " << Fcy << endl;
//            cout << "armor_tmp.m_X = " << armor_tmp.m_X << endl;
//            cout << "armor_tmp.m_Y = " << armor_tmp.m_Y << endl;
        }
    }


    bool ArmorDetect::parallel(LightBar bar1, LightBar bar2)
    {
        double product = fabs(bar1.line_6f[0] * bar2.line_6f[1] - bar1.line_6f[1] * bar2.line_6f[0]);
        if(product > sin(5.0 / 180 * 3.1415926))//若不平行
            return false;
        double length1 = bar1.line_6f[4];
        double length2 = bar2.line_6f[4];
        if(length1 < length2 * 0.6 || length2 < length1 * 0.6)      //两者大致相等（若不相等）
            return false;
        double length = (length1 + length2) / 2;
        double scale = fabs(log10(length1 / length2));
        double distance = sqrt(pow(bar1.line_6f[2] - bar2.line_6f[2], 2) + pow(bar1.line_6f[3] - bar2.line_6f[3], 2));
//        cout << distance << endl;
//        cout << fabs(bar1.line_6f[2] - bar2.line_6f[2]) << endl;
//        cout << fabs(bar1.line_6f[3] - bar2.line_6f[3]) << endl;
        if(fabs(bar1.line_6f[2] - bar2.line_6f[2]) / distance < 0.9) //cos(theta) = 0.5 即两个灯条之间的距离基本上都是由横向确定的
            return false;
        if(fabs(bar1.line_6f[3] - bar2.line_6f[3]) / distance > 0.5) // 滤除对角线灯条
            return false;

        if(distance > 6.0*length || distance < 0.5*length)
            return false;
        if(scale > 0.3)
            return false;
        return true;
    }

    bool ArmorDetect::hengparallel(LightBar bar1, LightBar bar2)
    {
        double product = fabs(bar1.line_6f[0] * bar2.line_6f[1] - bar1.line_6f[1] * bar2.line_6f[0]);
        if(product > sin(5.0 / 180 * 3.1415926))
            return false;
        double length1 = bar1.line_6f[4];
        double length2 = bar2.line_6f[4];
        if(length1 < length2 * 0.6 || length2 < length1 * 0.6)      //两者大致相等
            return false;
        double length = (length1 + length2) / 2;
        double scale = fabs(log10(length1 / length2));
        double distance = sqrt(pow(bar1.line_6f[2] - bar2.line_6f[2], 2) + pow(bar1.line_6f[3] - bar2.line_6f[3], 2));
//        cout << distance << endl;
//        cout << fabs(bar1.line_6f[2] - bar2.line_6f[2]) << endl;
//        cout << fabs(bar1.line_6f[3] - bar2.line_6f[3]) << endl;
        if(fabs(bar1.line_6f[3] - bar2.line_6f[3]) / distance < 0.9) //cos(theta) = 0.5 即两个灯条之间的距离基本上都是由横向确定的
            return false;
        if(fabs(bar1.line_6f[2] - bar2.line_6f[2]) / distance > 0.5) // 滤除对角线灯条
            return false;

        if(distance > 6.0*length || distance < 0.5*length)
            return false;
        if(scale > 0.3)
            return false;
        return true;


    }

    void ArmorDetect::showImage(std::vector<Armor> &_armors) {
        Scalar color = Scalar(255, 255, 0);
        Mat img = m_frame.clone();
        for (int i = 0; i < _armors.size(); i++){
            circle(img, _armors[i].m_center_uv, 10, color);
            stringstream ss;
            ss << i;
            String num(ss.str());
            putText(img, num, _armors[i].m_center_uv, FONT_HERSHEY_SIMPLEX, 1, color);
            circle(img, _armors[i].m_upper_left, 7, color);
            circle(img, _armors[i].m_bottom_right, 7, color);
//            cout << _armors[i].m_leftBar.m_contourArea << endl;
//            cout << _armors[i].m_rightBar.m_contourArea << endl;
        }
        imshow("raw_frame", m_frame);
        imshow("eee", img);
        waitKey(1);
//        imshow("ddd", img_b);
    }

    void ArmorDetect::calculateEjectTheta(std::vector<Armor> &_armors){
        float G = 9800.0f;
//        cout << "velocity = " << Param::VELOCITY << endl;
        for (int i = 0; i < _armors.size(); ++i) {
            Armor& armor_tmp = _armors[i];
//            cout << "m_pitch = " << m_pitch << endl;
//            float overx = armor_tmp.m_X - (cos(m_pitch)*Param::OFFSET_X + (-sin(m_pitch))*Param::OFFSET_EJECT_Z);
//            float overy = armor_tmp.m_Y - (sin(m_pitch)*Param::OFFSET_X + (cos(m_pitch))*Param::OFFSET_EJECT_Z);
//
////            armor_tmp.m_X -= 147.0f;
////            armor_tmp.m_Y += 44.0f;
////            cout << "-1/2*G*armor_tmp.m_X*armor_tmp.m_X = " << -1/2*G << endl;
//            cout << "overx = " << overx << endl;
//            cout << "overy = " << overy << endl;
//
//            float A = -1.0f/2*G*overx*overx / (Param::VELOCITY*Param::VELOCITY);
//            float B = overx;
//            float C = -1.0f/2*G*overx*overx / (Param::VELOCITY*Param::VELOCITY) - overy;
//
//            cout << "A = "  << A << endl;
//            cout << "B = "  << B << endl;
//            cout << "C = "  << C << endl;
//
//            cout << "B*B-4*A*C = " << B*B-4*A*C << endl;
//
//            float tanTheta = (-B+sqrt(B*B-4*A*C)) / 2 / A;
//            armor_tmp.m_eject_theta = atan(tanTheta)*180 / CV_PI;
//            cout << "m_eject_theta = " << armor_tmp.m_eject_theta << endl;
/////////////////////////////////////////////////////////////////////////////////////
            float startIterAngle = 0;
            for (int j = 0; j < 100; ++j) {
                float overx = armor_tmp.m_X - (cos(startIterAngle)*Param::OFFSET_X + (-sin(startIterAngle))*Param::OFFSET_EJECT_Z);
                float overy = armor_tmp.m_Y - (sin(startIterAngle)*Param::OFFSET_X + (cos(startIterAngle))*Param::OFFSET_EJECT_Z);
                float A = -1.0f/2*G*overx*overx / (Param::VELOCITY*Param::VELOCITY);
                float B = overx;
                float C = -1.0f/2*G*overx*overx / (Param::VELOCITY*Param::VELOCITY) - overy;
                float tanTheta = (-B+sqrt(B*B-4*A*C)) / 2 / A;
                float tmpTheta = atan(tanTheta);
                if(fabs(startIterAngle - tmpTheta) < 0.02*CV_PI / 180){
                    armor_tmp.m_eject_theta = tmpTheta;
                    break;
                } else{
                    startIterAngle = tmpTheta;
                }

            }

            armor_tmp.m_eject_theta = startIterAngle;

        }


    }



    bool ArmorDetect::Apply(std::vector<Armor> &_armors, cv::Mat &_frame, float _pitch) {
        assert(_pitch < 2);     //注意这里是弧度

        m_frame = _frame;
        m_pitch = _pitch;

        struct timeval st,en;

        int height = _frame.rows;
        int width = _frame.cols;
        Mat img_b(height, width, CV_8U, Scalar(0));
        Mat img = _frame.clone();
        cvtColor(img, img, CV_RGB2GRAY);
        Moments moment;
        vector<Point> points_led;
        vector<Point2f> points_mask;
        points_mask.reserve(1000);
        int points_mask_size_max=6000;
        for (int i = 0; i < height; i++) {
            uchar* p_raw  = img.ptr<uchar>(i);
            uchar* p_mask = img_b.ptr<uchar>(i);

            for(int j = 0;j < width; j++){
                if(p_raw[j]>150 && p_raw[j] < 256) {
                    p_mask[j] = 255;
                    //如果原图某点有一定亮度，把img_b对应点变成白色，并把该点保存到points_mask中
                    if(points_mask.size()<points_mask_size_max){
                        points_mask.push_back(Point2f(j,i));
                    }
                }
            }
        }

//        cv::dilate(img_b, img_b,cv::Mat());
//                    cout<<"points_mask size = " <<points_mask.size()<<endl;

        Mat mask = img_b.clone();
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
        findContours(mask, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
        if (contours.size() < 2 || contours.size() >400){
//            cout<<"coutous size wrong!    "<<contours.size()<<endl;
            return false;
        }

//        imshow("mask",mask);
//        waitKey(1);

        std::vector<LightBar> bars,hengbars;
//        cout << "contours_size() = " << contours.size() << endl;
        for (int i = 0; i < contours.size(); ++i) {     //遍历所有轮廓，找到灯柱轮廓，并将灯柱轮廓内的点保存
//            gettimeofday(&st,NULL);
            LightBar bar;      //左右灯柱
            LightBar hengbar;  //上下灯柱
            bar.m_contour = contours[i];

            bar.m_contourArea = contourArea(contours[i]);///



            if(bar.m_contourArea > hitcrt::Param::MAX_LIGHT_BAR_AREA || bar.m_contourArea < hitcrt::Param::MIN_LIGHT_BAR_AREA)
                continue;  //结束当前循环
            bar.m_rotateRect = minAreaRect(contours[i]);

            float length = max(bar.m_rotateRect.size.height, bar.m_rotateRect.size.width);
            float thick = min(bar.m_rotateRect.size.height, bar.m_rotateRect.size.width);
            if (thick > 0.5 * length||thick<0.05*length)///0.3
                continue;

            ////////////////////////////////////////////////////////////////////////////
            if(points_mask.size()<points_mask_size_max){
                bar.m_insidePoints.reserve(points_mask.size());
                for (int j = 0; j < points_mask.size(); ++j) {
                    double is_in_contour = pointPolygonTest(contours[i], points_mask[j], false);  //判断点是否在轮廓内
                    if (is_in_contour >= 0){
                        bar.m_insidePoints.push_back(points_mask[j]);
                    }
                }

//            gettimeofday(&en,NULL);
//            cout << "time template_match = " << en.tv_usec - st.tv_usec << endl;
                if (bar.m_insidePoints.size() < 2)
                    continue;
                Vec4f line_4f_tmp;

                fitLine(bar.m_insidePoints, line_4f_tmp, CV_DIST_L2, 0, 0.01, 0.01);

                if(fabs(line_4f_tmp[0])>0.7*fabs(line_4f_tmp[1]))   //根据拟合直线的方向向量进行判断
                {
                    hengbar = bar;
                    hengbar.line_6f = Vec6f(line_4f_tmp[0], line_4f_tmp[1], line_4f_tmp[2], line_4f_tmp[3], length,0);
                    float lefter = 10000, righter = -1;
                    for (int j = 0; j < hengbar.m_insidePoints.size(); ++j) {
                        if(hengbar.m_insidePoints[j].x < lefter){
                            lefter = hengbar.m_insidePoints[j].x;
                            hengbar.m_upper = hengbar.m_insidePoints[j];
                        }
                        if(hengbar.m_insidePoints[j].x > righter){
                            righter = hengbar.m_insidePoints[j].x;
                            hengbar.m_bottom = hengbar.m_insidePoints[j];
                        }

                    }
                }
                hengbars.push_back(hengbar);

                if (fabs(line_4f_tmp[0]) > 0.5 * fabs(line_4f_tmp[1]))  //斜率  如果不满足此条件 则是左右灯柱
                {
                    continue;
                }

                bar.line_6f = Vec6f(line_4f_tmp[0], line_4f_tmp[1], line_4f_tmp[2], line_4f_tmp[3], length,0);

                float upper = 10000, lower = -1;
                for (int j = 0; j < bar.m_insidePoints.size(); ++j) {
                    if(bar.m_insidePoints[j].y < upper){
                        upper = bar.m_insidePoints[j].y;
                        bar.m_upper = bar.m_insidePoints[j];
                    }
                    if(bar.m_insidePoints[j].y > lower){
                        lower = bar.m_insidePoints[j].y;
                        bar.m_bottom = bar.m_insidePoints[j];
                    }

                }
#ifdef _DEBUG
                Point pt1(line_4f_tmp[2] + 100 * line_4f_tmp[0], line_4f_tmp[3] + 100 * line_4f_tmp[1]);
            Point pt2(line_4f_tmp[2] - 100 * line_4f_tmp[0], line_4f_tmp[3] - 100 * line_4f_tmp[1]);
            Scalar color = Scalar(255, 255, 0);
            line(img, pt1, pt2, color);

#endif
            }

            //////////////////////////////////////////////////////////////////////////////////
            else{
//                cout << "2222222222222" <<endl;
                Vec4f line_4f_tmp;
                fitLine(bar.m_contour, line_4f_tmp, CV_DIST_L2, 0, 0.01, 0.01);
                if (fabs(line_4f_tmp[0]) > 0.5 * fabs(line_4f_tmp[1]))//斜率
                    continue;
                bar.line_6f = Vec6f(line_4f_tmp[0], line_4f_tmp[1], line_4f_tmp[2], line_4f_tmp[3], length,0);
                float upper = 10000, lower = -1;
                for (int j = 0; j < bar.m_contour.size(); ++j) {
                    if(bar.m_contour[j].y < upper){
                        upper = bar.m_contour[j].y;
                        bar.m_upper = bar.m_contour[j];
                    }
                    if(bar.m_contour[j].y > lower){
                        lower = bar.m_contour[j].y;
                        bar.m_bottom = bar.m_contour[j];
                    }

                }
#ifdef _DEBUG
                Point pt1(line_4f_tmp[2] + 100 * line_4f_tmp[0], line_4f_tmp[3] + 100 * line_4f_tmp[1]);
            Point pt2(line_4f_tmp[2] - 100 * line_4f_tmp[0], line_4f_tmp[3] - 100 * line_4f_tmp[1]);
            Scalar color = Scalar(255, 255, 0);
            line(img, pt1, pt2, color);

#endif
            }


            ////////////////////////////////////////////////////////////////////////////////

            bars.push_back(bar);
        }

        vector<int> henglabels;
        std::vector<Armor> _heng_armors;
        if(hengbars.size() >= 2){
            partition(hengbars, henglabels,hengparallel);
            int search_flag[20] = { 0 };
            for (int i = 0; i < henglabels.size(); i++) {
                if (search_flag[i])
                    continue;
                int sum = 0;
                int index[2] = {-1};
                for (int j = 0; j < henglabels.size(); j++) {
                    if (henglabels[i] == henglabels[j]) {
                        sum++;
                        if (sum == 2) {
                            index[0] = j;
                        }
                        if (sum == 3) {
                            index[1] = j;
                        }
//                    index = j;
//                    search_flag[index] = 1;
                        search_flag[j] = 1;
                    }
                }
                if (sum == 2) {
                    Armor armor_tmp;
                    armor_tmp.m_center_uv = Point2f((bars[i].line_6f[2] + bars[index[0]].line_6f[2]) / 2,
                                                    (bars[i].line_6f[3] + bars[index[0]].line_6f[3]) / 2);
                    if (bars[i].line_6f[3] > bars[index[0]].line_6f[3]) {
                        armor_tmp.m_leftBar = bars[index[0]];
                        armor_tmp.m_rightBar = bars[i];
                    } else {
                        armor_tmp.m_leftBar = bars[i];
                        armor_tmp.m_rightBar = bars[index[0]];
                    }

                    armor_tmp.m_upper_left = armor_tmp.m_leftBar.m_upper;
                    armor_tmp.m_bottom_left = armor_tmp.m_rightBar.m_upper;
                    armor_tmp.m_upper_right = armor_tmp.m_leftBar.m_bottom;
                    armor_tmp.m_bottom_right = armor_tmp.m_rightBar.m_bottom;
//                    armor_tmp.judgeHereoInfantry(armor_type);
                    armor_tmp.m_type = Armor::INFANTRY;
//                cout << armor_tmp.m_type << endl;
                    armor_tmp.calculateRT();
//                cout << "distance = " << armor_tmp.m_distance << endl;
                    if (armor_tmp.m_distance < Param::MAX_DISTANCE) {
                        _heng_armors.push_back(armor_tmp);
                    }

                }
            }
        }
        if(bars.size() < 2)
            return false;
        vector<int> labels;
        partition(bars, labels,parallel);


        int search_flag[20] = { 0 };
        for (int i = 0; i < labels.size(); i++) {
            if (search_flag[i])
                continue;
            int sum = 0;
            int index[2] = {-1};
            for (int j = 0; j < labels.size(); j++) {
                if (labels[i] == labels[j]) {
                    sum++;
                    if(sum==2){
                        index[0]=j;
                    }
                    if(sum==3){
                        index[1]=j;
                    }
//                    index = j;
//                    search_flag[index] = 1;
                    search_flag[j] = 1;
                }
            }
            if (sum == 2) {
                Armor armor_tmp;
                armor_tmp.m_center_uv = Point2f((bars[i].line_6f[2] + bars[index[0]].line_6f[2]) / 2,
                                                (bars[i].line_6f[3] + bars[index[0]].line_6f[3]) / 2);
                if (bars[i].line_6f[2] > bars[index[0]].line_6f[2]) {
                    armor_tmp.m_leftBar = bars[index[0]];
                    armor_tmp.m_rightBar = bars[i];
                } else {
                    armor_tmp.m_leftBar = bars[i];
                    armor_tmp.m_rightBar = bars[index[0]];
                }

                armor_tmp.m_upper_left = armor_tmp.m_leftBar.m_upper;
                armor_tmp.m_bottom_left = armor_tmp.m_leftBar.m_bottom;
                armor_tmp.m_upper_right = armor_tmp.m_rightBar.m_upper;
                armor_tmp.m_bottom_right = armor_tmp.m_rightBar.m_bottom;
                armor_tmp.judgeHereoInfantry(armor_type);
//                cout << armor_tmp.m_type << endl;
                armor_tmp.calculateRT();
//                cout << "distance = " << armor_tmp.m_distance << endl;
                if(armor_tmp.m_distance < Param::MAX_DISTANCE){
                    _armors.push_back(armor_tmp);
                }

            }
            if(sum==3){
                ///平行线平行度最高
                double product1 = fabs(bars[i].line_6f[0] * bars[index[0]].line_6f[1] - bars[i].line_6f[1] * bars[index[0]].line_6f[0]);
                double product2 = fabs(bars[i].line_6f[0] * bars[index[1]].line_6f[1] - bars[i].line_6f[1] * bars[index[1]].line_6f[0]);
                double product3 = fabs(bars[index[0]].line_6f[0] * bars[index[1]].line_6f[1] - bars[index[0]].line_6f[1] * bars[index[1]].line_6f[0]);
                vector<double> product{product1,product2,product3};
                sort(product.begin(),product.end());///从小到大排序
                int id[2]={-1};
                if(fabs(product[0]-product1)<1e-6){
                    id[0]=i;
                    id[1]=index[0];
                }
                else if(fabs(product[0]==product2)<1e-6){
                    id[0]=i;
                    id[1]=index[1];
                }
                else if(fabs(product[0]==product3)<1e-6){
                    id[0]=index[0];
                    id[1]=index[1];
                }

                ///平行线距离最近
                double distance1 = sqrt(pow(bars[i].line_6f[2] - bars[index[0]].line_6f[2], 2) + pow(bars[i].line_6f[3] - bars[index[0]].line_6f[3], 2));
                double distance2 = sqrt(pow(bars[i].line_6f[2] - bars[index[1]].line_6f[2], 2) + pow(bars[i].line_6f[3] - bars[index[1]].line_6f[3], 2));
                double distance3 = sqrt(pow(bars[index[0]].line_6f[2] - bars[index[1]].line_6f[2], 2) + pow(bars[index[0]].line_6f[3] - bars[index[1]].line_6f[3], 2));
                vector<double> distance{distance1,distance2,distance3};
                sort(distance.begin(),distance.end());
                int id_distance[2]={-1};
                if(fabs(distance[0]-distance1)<1e-6){
                    id_distance[0]=i;
                    id_distance[1]=index[0];
                }
                else if(fabs(distance[0]-distance2)<1e-6){
                    id_distance[0]=i;
                    id_distance[1]=index[1];
                }
                else if(fabs(distance[0]-distance3)<1e-6){
                    id_distance[0]=index[0];
                    id_distance[1]=index[1];
                }

                if(!(id[0]==id_distance[0]&&id[1]==id_distance[1]))
                    continue;

                Armor armor_tmp;
                armor_tmp.m_center_uv = Point2f((bars[id[0]].line_6f[2] + bars[id[1]].line_6f[2]) / 2,
                                                (bars[id[0]].line_6f[3] + bars[id[1]].line_6f[3]) / 2);
                if (bars[id[0]].line_6f[2] > bars[id[1]].line_6f[2]) {
                    armor_tmp.m_leftBar = bars[id[1]];
                    armor_tmp.m_rightBar = bars[id[0]];
                } else {
                    armor_tmp.m_leftBar = bars[id[0]];
                    armor_tmp.m_rightBar = bars[id[1]];
                }

                armor_tmp.m_upper_left = armor_tmp.m_leftBar.m_upper;
                armor_tmp.m_bottom_left = armor_tmp.m_leftBar.m_bottom;
                armor_tmp.m_upper_right = armor_tmp.m_rightBar.m_upper;
                armor_tmp.m_bottom_right = armor_tmp.m_rightBar.m_bottom;
                armor_tmp.judgeHereoInfantry(armor_type);
//                cout << armor_tmp.m_type << endl;
                armor_tmp.calculateRT();
//                cout << "distance = " << armor_tmp.m_distance << endl;
                if(armor_tmp.m_distance < Param::MAX_DISTANCE){
                    _armors.push_back(armor_tmp);
                }

            }
//            cout << "sum "<<sum<<endl;
        }

        templateMatch(_heng_armors);
        templateMatch(_armors);
        if(_heng_armors.size()>0){
            for(int k=0;k < _armors.size();k++){
                for(int p=0; p <_heng_armors.size();p++){
                    if(sqrt((_armors[k].m_center_uv.x-_heng_armors[p].m_center_uv.x)*(_armors[k].m_center_uv.x-_heng_armors[p].m_center_uv.x)+(_armors[k].m_center_uv.y-_heng_armors[p].m_center_uv.y)*(_armors[k].m_center_uv.y-_heng_armors[p].m_center_uv.y))<5){
                        cout<<"RFID"<<endl;
                        _armors.erase(_armors.begin()+k);
                    }
                }
            }

        }
        calculateXY(_armors);
        calculateEjectTheta(_armors);


#ifdef _DEBUG
        Scalar color = Scalar(255, 255, 0);
        for (int i = 0; i < _armors.size(); i++){
            circle(img, _armors[i].m_center_uv, 10, color);
            stringstream ss;
            ss << i;
            String num(ss.str());
            putText(img, num, _armors[i].m_center_uv, FONT_HERSHEY_SIMPLEX, 1, color);
            circle(img, _armors[i].m_upper_left, 7, color);
            circle(img, _armors[i].m_bottom_right, 7, color);
//            cout << _armors[i].m_leftBar.m_contourArea << endl;
//            cout << _armors[i].m_rightBar.m_contourArea << endl;
        }

        imshow("eee", img);
        imshow("ddd", img_b);
        waitKey(0);
#endif



    }


//    bool ArmorDetect::Apply(std::vector<Armor> &_armors, cv::Mat &_frame) {
//
//        int height = _frame.rows;
//        int width = _frame.cols;
////        int channels = _frame.channels();
//        Mat img_b(height, width, CV_8U, Scalar(0));
//        Mat img = _frame.clone();
//        cvtColor(img, img, CV_RGB2GRAY);
//        Moments moment;
//        vector<Point> points_led;
//        vector<Point2f> points_mask;
//        points_mask.reserve(1000);
//        for (int i = 0; i < height; i++) {
//            uchar* p_raw  = img.ptr<uchar>(i);
//            uchar* p_mask = img_b.ptr<uchar>(i);
//
//            for(int j = 0;j < width; j++){
//                if(p_raw[j]>150 && p_raw[j] < 256)
//                {
//                    p_mask[j] = 255;
//                    points_mask.push_back(Point2f(j,i));
//                }
//            }
//        }
//
//        Mat mask = img_b.clone();
//        vector<vector<Point> > contours;
//        vector<Vec4i> hierarchy;
//        findContours(mask, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
//        vector<Vec6f> lines;
//        if (contours.size() < 2 || contours.size() >40){
////            cout<<"coutous size wrong!    "<<contours.size()<<endl;
//            return false;
//        }
//
//        double maxarea = 0;
//        for (int i = 0; i < contours.size(); i++){
//            double area = contourArea(contours[i]);
//            if (area > maxarea && area < 500)
//                maxarea = area;
//        }
//
//        for (int i = 0; i < contours.size(); i++) {
//            float area = contourArea(contours[i]);
//            if ( area < 0.01 * maxarea || area > 500)
//                continue;
//            vector<Point2f> points_on_line;
//            Vec4f line_4f_tmp;
//            Vec6f line_6f_tmp;
//            moment = moments(contours[i], false);
//            Point center_contour(moment.m10 / moment.m00, moment.m01 / moment.m00);
//            points_led.push_back(center_contour);
//
//            for (int j = 0; j < points_mask.size(); j++){
//                double is_in_contour = pointPolygonTest(contours[i], points_mask[j], false);
//                if (is_in_contour >= 0){
//                    points_on_line.push_back(points_mask[j]);
//                }
//            }
//            if (points_on_line.size() < 2)
//                continue;
//            fitLine(points_on_line, line_4f_tmp, CV_DIST_L2, 0, 0.01, 0.01);
//            if (fabs(line_4f_tmp[0]) > 0.5 * fabs(line_4f_tmp[1]))//2
//            {
//                continue;
//            }
//            RotatedRect contour_rect = minAreaRect(contours[i]);
//            float length = max(contour_rect.size.height, contour_rect.size.width);
//            float thick = min(contour_rect.size.height, contour_rect.size.width);
//            if (thick > 0.5 * length||thick<0.1*length)///0.3
//            {
////                    cout<<"thick>0.6 length!"<<"thick="<<thick<<"  length="<<length<<endl;
//                continue;
//            }
//            line_6f_tmp = Vec6f(line_4f_tmp[0], line_4f_tmp[1], line_4f_tmp[2], line_4f_tmp[3], length,0);
//            lines.push_back(line_6f_tmp);
//#ifdef _DEBUG
//            Point pt1(line_4f_tmp[2] + 100 * line_4f_tmp[0], line_4f_tmp[3] + 100 * line_4f_tmp[1]);
//            Point pt2(line_4f_tmp[2] - 100 * line_4f_tmp[0], line_4f_tmp[3] - 100 * line_4f_tmp[1]);
//            Scalar color = Scalar(255, 255, 0);
//            line(img, pt1, pt2, color);
//#endif
//        }
//
//        vector<int> labels;
//        if (lines.size() < 2)
//        {
////                cout<<"lines.size<2       "<<lines.size()<<endl;
//            return false;
//        }
//        partition(lines, labels,parallel);
//
//        vector<Point2f> armor_centers;
//        int search_flag[20] = { 0 };
//        for (int i = 0; i < labels.size(); i++){
//            if (search_flag[i])continue;
//            int sum = 0;
//            int index = -1;
//            for (int j = 0; j < labels.size(); j++){
//                if (labels[i] == labels[j]){
//                    sum++;
//                    index = j;
//                    search_flag[index] = 1;
//                }
//            }
//            if (sum == 2){
//                Armor armor_tmp;
//                armor_tmp.m_center_uv = Point2f((lines[i][2] + lines[index][2]) / 2, (lines[i][3] + lines[index][3]) / 2);
////                armor_tmp.m_distance
////                armor_centers.push_back();
//            }
//
//        }
//        if(armor_centers.size()<1)
//            return false;
//#ifdef _DEBUG
//        Scalar color = Scalar(255, 255, 0);
//        for (int i = 0; i < armor_centers.size(); i++){
//            circle(img, armor_centers[i], 10, color);
//            stringstream ss;
//            ss << i;
//            String num(ss.str());
//            putText(img, num, armor_centers[i], FONT_HERSHEY_SIMPLEX, 1, color);
//        }
//
//        imshow("eee", img);
//        imshow("ddd", img_b);
//        waitKey(0);
//#endif
//    }
}
