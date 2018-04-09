 


#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {

    Mat srcImg = imread("/home/xuxuxu/b/二维码测试图片/17.jpg");
    Mat srcGray;
    cvtColor(srcImg, srcGray, CV_RGB2GRAY);
    Mat grad_x, grad_y;
    Sobel(srcGray, grad_x, CV_32F, 1, 0, -1);//求x方向梯度
    imshow("grad_x", grad_x);
    Sobel(srcGray, grad_y, CV_32F, 0, 1, -1);//y方向梯度
    imshow("grad_y", grad_y);
    Mat gradient;
    subtract(grad_x, grad_y, gradient);

    convertScaleAbs(gradient, gradient);//得到包含高水平梯度和低竖直梯度的图像区域
    imshow("gradient", gradient);
    Mat blur_img;
    blur(gradient, blur_img, Size(9, 9));//模糊
    Mat threshold_img;
    threshold(blur_img, threshold_img, 210, 255, CV_THRESH_BINARY);
    imshow("threshold_img", threshold_img);
    Mat kernel;
    kernel = getStructuringElement(MORPH_RECT, Size(33, 11));//需要找到最佳值
    Mat close_img;
    morphologyEx(threshold_img, close_img, MORPH_CLOSE, kernel);//闭运算
    imshow("close_img1", close_img);
    Mat element = getStructuringElement(MORPH_RECT, Size(11, 11));//得到自定义核
    erode(close_img, close_img, element);
    Mat element1 = getStructuringElement(MORPH_RECT, Size(13, 13));//得到自定义核
    dilate(close_img, close_img, element1);
    imshow("close_img2", close_img);
    std::vector<std::vector<Point> > contours;
    std::vector<Vec4i> hierarchy;
    findContours(close_img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);//得到轮廓
    imshow("close_img3", close_img);
    /*找到最大轮廓*/
    int findmaxsize = 3;
    int num;
    std::vector<Point> max_Contour,max_Contour2;//最大轮廓与次大轮廓
    std::vector<vector<Point> > max_Contour1;

    for (int i = 0; i < contours.size(); i++) {
        if (max_Contour.size() < contours[i].size()) {
            max_Contour = contours[i];
            num=i;
        }

    }
    max_Contour1.push_back(max_Contour);
    for (int i = 0; i < contours.size(); i++) {
        if (max_Contour2.size() < contours[i].size()) {
            if(i!=num)
            max_Contour2 = contours[i];
        }

    }
    max_Contour1.push_back(max_Contour2);
    cout<<max_Contour1[1].size()<<endl;
    RotatedRect bar_code_rect[2];
    if (max_Contour.size() < 10) {
        std::cout << "这不是条形码" << std::endl;
    } else {
        for(int j=0;j<2;j++) {

            bar_code_rect[j] = minAreaRect(max_Contour1[j]);//最大轮廓的最小外接矩形

            Point2f rect[4];//用来取外接矩形的四个定点
            Point2f rectlftop, rectrhtop, rectlfub, rectrhub;
            circle(srcGray, Point(bar_code_rect[j].center.x,
                                  bar_code_rect[j].center.y), 5,
                   Scalar(0, 255, 0), -1, 8);
            bar_code_rect[j].points(rect);  //把最小外接矩形四个端点复制给rect数组

            for (int k = 0; k < 4; k++) {
                line(srcImg, rect[k], rect[(k + 1) % 4], Scalar(0, 0, 255), 2, 8);  //绘制最小外接矩形每条边
            }
            cout<<"1111111111111111111"<<endl;
        }
    }

		imshow("origin",srcImg);

		waitKey(0);

}
