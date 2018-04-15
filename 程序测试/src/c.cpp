
#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {

    Mat srcImg = imread("/home/xuxuxu/b/二维码测试图片/38.jpg");
    clock_t start_time = clock();
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
    //imshow("gradient", gradient);
    Mat blur_img;
    blur(gradient, blur_img, Size(9, 9));//模糊
    //imshow("blur",blur_img);
    Mat threshold_img;
    threshold(blur_img, threshold_img, 240, 255, CV_THRESH_BINARY); //首先选择较高阈值进行定位
    //imshow("threshold_img", threshold_img);
    Mat kernel;
    kernel = getStructuringElement(MORPH_RECT, Size(33, 11));//需要找到最佳值
    Mat close_img;
    morphologyEx(threshold_img, close_img, MORPH_CLOSE, kernel);//闭运算
    //imshow("close_img1", close_img);
    Mat element = getStructuringElement(MORPH_RECT, Size(11, 11));//得到自定义核
    erode(close_img, close_img, element);
    Mat element1 = getStructuringElement(MORPH_RECT, Size(33, 33));//得到自定义核
    dilate(close_img, close_img, element1);
   // imshow("close_img2", close_img);
    std::vector<std::vector<Point> > contours;
    std::vector<Vec4i> hierarchy;
    findContours(close_img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);//得到轮廓
   // imshow("close_img3", close_img);
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
    }
    threshold(blur_img, threshold_img, 220, 255, CV_THRESH_BINARY);//放宽阈值寻找条形码轮廓
    morphologyEx(threshold_img, close_img, MORPH_CLOSE, kernel);//闭运算
    erode(close_img, close_img, element);
    dilate(close_img, close_img, element1);
    findContours(close_img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    ////////////////////////////////////////
    int findmaxsize = 3;
    int num,num1;
    std::vector<Point> max_Contour1,max_Contour2,max_Contour3;//最大轮廓与次大轮廓以及第三大轮廓
    std::vector<vector<Point> > max_Contour;

    for (int i = 0; i < contours.size(); i++) {
        if (max_Contour1.size() < contours[i].size()) {
            max_Contour1 = contours[i];
            num=i;
        }

    }
    max_Contour.push_back(max_Contour1);
    for (int i = 0; i < contours.size(); i++) {
        if (max_Contour2.size() < contours[i].size()) {
            if(i!=num) {
                max_Contour2 = contours[i];
                num1=i;
            }
        }

    }
    if(float(max_Contour2.size())/float(max_Contour1.size())>0.7)
        max_Contour.push_back(max_Contour2);
    for (int i = 0; i < contours.size(); i++) {
        if (max_Contour3.size() < contours[i].size()) {
            if(i!=num&&i!=num1) {
                max_Contour3 = contours[i];
            }
        }

    }
    if(float(max_Contour3.size())/float(max_Contour2.size())>0.7)
        max_Contour.push_back(max_Contour3);
    cout<<"轮廓的数目："<<max_Contour.size()<<endl;
    RotatedRect bar_code_rect[3];//旋转矩阵
    int findnum;
    float firststandard=10000000;
    if (max_Contour1.size() < 10) {
        std::cout << "这不是条形码" << std::endl;
    } else {
        for(int j=0;j<max_Contour.size();j++) {

            bar_code_rect[j] = minAreaRect(max_Contour[j]);//最大轮廓的最小外接矩形
            float distance=(place_rect.center.x-bar_code_rect[j].center.x)*(place_rect.center.x-bar_code_rect[j].center.x)
            +(place_rect.center.y-bar_code_rect[j].center.y)*(place_rect.center.y-bar_code_rect[j].center.y);
            if(distance<firststandard)
            {
                firststandard=distance;
                findnum=j;
            }
            Point2f rect[4];//用来取外接矩形的四个定点
            circle(srcGray, Point(bar_code_rect[j].center.x,
                                  bar_code_rect[j].center.y), 5,
                   Scalar(0, 255, 0), -1, 8);
            bar_code_rect[j].points(rect);  //把最小外接矩形四个端点复制给rect数组
           // cout<<bar_code_rect[j].angle<<endl;
            for (int k = 0; k < 4; k++) {
                line(srcImg, rect[k], rect[(k + 1) % 4], Scalar(0, 0, 255), 2, 8);  //绘制最小外接矩形每条边
            }
        }
    }
    Point2f rect_dst[4],rect_rotated[4];//用来取外接矩形的四个定点后面要对其进行旋转
    circle(srcGray, Point(bar_code_rect[findnum].center.x,
                          bar_code_rect[findnum].center.y), 5,
           Scalar(0, 255, 0), -1, 8);
    bar_code_rect[findnum].points(rect_dst);  //把最小外接矩形四个端点复制给rect数组

    for (int k = 0; k < 4; k++) {
        line(srcImg, rect_dst[k], rect_dst[(k + 1) % 4], Scalar(0, 255, 255), 2, 8);  //绘制最小外接矩形每条边
    }
    ////////////////////////////////////////////////////////
//    Rect boundRect;
//    boundRect=boundingRect(max_Contour[findnum]);
    rectangle(srcImg, Point(bar_code_rect[findnum].boundingRect().x, bar_code_rect[findnum].boundingRect().y), Point(bar_code_rect[findnum].boundingRect().x
             + bar_code_rect[findnum].boundingRect().width, bar_code_rect[findnum].boundingRect().y + bar_code_rect[findnum].boundingRect().height), Scalar(0, 255, 0), 2, 8);
    ////////////////////////////////////////////////////////
    /* 旋转矫正部分代码*/
    cout<<bar_code_rect[findnum].angle<<endl;
    float  angle=bar_code_rect[findnum].angle;
    if (0< abs(angle) && abs(angle)<=45)
             angle = angle;//负数，顺时针旋转
            else if (45< abs(angle) && abs(angle)<90)
        angle = 90 -  abs(angle);//正数，逆时针旋转
    cout<<bar_code_rect[findnum].boundingRect().x<<","
        <<bar_code_rect[findnum].boundingRect().y<<endl;
    Point2f center = bar_code_rect[findnum].center;  //定义旋转中心坐标
             double angle0 = angle;
             double scale = 1;
             Mat roateM(Size(2, 3), CV_32FC1);
              roateM = getRotationMatrix2D(center, angle0, scale);  //获得旋转矩阵,顺时针为负，逆时针为正
            cout<<"旋转矩阵："<<roateM<<endl;
            cout<<"sin(angle):"<<sin(angle*CV_PI/180)<<endl;
    cout<<angle<<endl;
    Mat rotatedImg1,rotatedImg2;
             warpAffine(srcImg, rotatedImg1, roateM, srcImg.size()); //仿射变换
    for(int i=0;i<4;i++)//找到对应的旋转点//
    {
        rect_rotated[i].x=(rect_dst[i].x-center.x)*cos(angle*CV_PI/180)+
                (rect_dst[i].y-center.y)*sin(angle*CV_PI/180)+center.x;
        rect_rotated[i].y=-(rect_dst[i].x-center.x)*sin(angle*CV_PI/180)+
                          (rect_dst[i].y-center.y)*cos(angle*CV_PI/180)+center.y;
        circle(rotatedImg1,rect_rotated[i],5,Scalar(255,255,255));
        circle(rotatedImg1,rect_dst[i],10,Scalar(255,255,255));

    }
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
        warpAffine(srcImg, rotatedImg2, roateM, srcImg.size()); //仿射变换
        angle=angle-90;
        for(int i=0;i<4;i++)//找到对应的旋转点//
        {
            rect_rotated[i].x=(rect_dst[i].x-center.x)*cos(angle*CV_PI/180)+
                              (rect_dst[i].y-center.y)*sin(angle*CV_PI/180)+center.x;
            rect_rotated[i].y=-(rect_dst[i].x-center.x)*sin(angle*CV_PI/180)+
                              (rect_dst[i].y-center.y)*cos(angle*CV_PI/180)+center.y;
            circle(rotatedImg2,rect_rotated[i],5,Scalar(255,255,255));
            circle(rotatedImg2,rect_dst[i],10,Scalar(255,255,255));

        }
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
    }
    Mat theObject;
    if(rotatedImg2.empty()) {
        //imshow("旋转后的图", rotatedImg1);
        theObject=rotatedImg1.clone();
    }
    else {
       // imshow("旋转后的图1", rotatedImg2);
        theObject=rotatedImg2.clone();
    }
    /////////////////////////////////////////////////
    clock_t end_time = clock();
    std::cout<<"Runing time is:"<<static_cast<double>(end_time - start_time)/CLOCKS_PER_SEC*1000<<"ms"<<std::endl;
		imshow("origin",theObject(Rect(min_x,min_y,max_x-min_x,max_y-min_y)));

		waitKey(0);

}
