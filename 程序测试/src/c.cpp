#include<opencv2/opencv.hpp>
#include<iostream>;
#include <time.h>
using namespace cv;


int main(int argc,char**argv)
{
    clock_t start_time = clock();
    Mat srcImg=imread("/home/xuxuxu/b/二维码测试图片/13.jpg");
    Mat srcGray;
    cvtColor(srcImg,srcGray,CV_RGB2GRAY);
    Mat grad_x,grad_y;
    Sobel(srcGray,grad_x,CV_32F,1,0,-1);//求x方向梯度
    Sobel(srcGray,grad_y,CV_32F,0,1,-1);//y方向梯度
    Mat gradient;
    subtract(grad_x,grad_y,gradient);

    convertScaleAbs(gradient,gradient);//得到包含高水平梯度和低竖直梯度的图像区域
    Mat blur_img;
    blur(gradient,blur_img,Size(9,9));//模糊
    Mat threshold_img;
    threshold(blur_img,threshold_img,210,255,CV_THRESH_BINARY);
    Mat kernel;
    kernel=getStructuringElement(MORPH_RECT,Size(21,7));
    Mat close_img;
    morphologyEx(threshold_img,close_img,MORPH_CLOSE,kernel);//闭运算
    Mat element=getStructuringElement(MORPH_RECT,Size(11,11));//得到自定义核
    erode(close_img,close_img,element);
    Mat element1=getStructuringElement(MORPH_RECT,Size(15,15));//得到自定义核
    dilate(close_img,close_img,element1);
    std::vector<std::vector<Point> > contours;
    std::vector<Vec4i> hierarchy;
    findContours(close_img,contours,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);//得到轮廓
    /*找到最大轮廓*/
    std::vector<Point> max_Contour;
    for(int i=0;i<contours.size();i++)
    {
        if(max_Contour.size()<contours[i].size())
            max_Contour=contours[i];
    }
    if(max_Contour.size()<20)
    {
        std::cout<<"这不是条形码"<<std::endl;
    }
    else {
        RotatedRect bar_code_rect = minAreaRect(max_Contour);//最大轮廓的最小外接矩形
        Point2f rect[4];//用来取外接矩形的四个定点
        circle(srcImg, Point(bar_code_rect.center.x,
                             bar_code_rect.center.y), 5,
               Scalar(0, 255, 0), -1, 8);
        bar_code_rect.points(rect);  //把最小外接矩形四个端点复制给rect数组

        for (int j = 0; j < 4; j++) {
            line(srcImg, rect[j], rect[(j + 1) % 4], Scalar(0, 0, 255), 2, 8);  //绘制最小外接矩形每条边
        }
        imshow("原图", srcGray);
        imshow("结果图", srcImg);
    }
    clock_t end_time = clock();
    std::cout<<"Runing time is:"<<static_cast<double>(end_time - start_time)/CLOCKS_PER_SEC*1000<<"ms"<<std::endl;
    waitKey(0);


}
