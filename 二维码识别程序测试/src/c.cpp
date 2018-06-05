
#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;


    Point Center_cal(vector<vector<Point> > contours, int i) //近似寻找轮廓中心
    {
        int centerx=0,centery=0,n=contours[i].size();
        centerx = (contours[i][n/8].x + contours[i][n*2/8].x + contours[i][3*n/8].x + contours[i][4*n/8].x + contours[i][n*5/8].x + contours[i][6*n/8].x+ contours[i][7*n/8].x+contours[i][n-1].x)/8;
        centery = (contours[i][n/8].y + contours[i][n*2/8].y + contours[i][3*n/8].y +contours[i][n*4/8].y + contours[i][n*5/8].y + contours[i][6*n/8].y+ contours[i][7*n/8].y+ contours[i][n-1].y)/8;
        Point point1=Point(centerx,centery);
        return point1;
    }
   /////二维码处理
    bool Find_QBar_RotateRect(Mat& inputImg,Point2f oritented_pt,RotatedRect output)
   {

       Mat srcImg=inputImg.clone();
       Mat srcGray;
       cvtColor(srcImg,srcGray,CV_RGB2GRAY);

       blur(srcGray,srcGray,Size(3,3));
       Mat threshold_img,close_img;
       threshold(srcGray,threshold_img,180,255,CV_THRESH_BINARY);
       imshow("二值",threshold_img);
       Mat element=getStructuringElement(MORPH_RECT,Size(7,7));//得到自定义核
       erode(threshold_img,threshold_img,element);
       Mat element1=getStructuringElement(MORPH_RECT,Size(3,3));//得到自定义核
       dilate(threshold_img,close_img,element1);
       imshow("222",threshold_img);

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
       drawContours(inputImg,contours2,findnum,Scalar(0,0,125),5);
       output = minAreaRect(contours2[findnum]);//最大轮廓的最小外接矩形
       Point2f rect[4];//用来取外接矩形的四个定点
       Point2f rectlftop,rectrhtop,rectlfub,rectrhub;
       output.points(rect);  //把最小外接矩形四个端点复制给rect数组

       for (int j = 0; j < 4; j++) {
           line(inputImg, rect[j], rect[(j + 1) % 4], Scalar(0, 0, 255), 2, 8);  //绘制最小外接矩形每条边
       }
       imshow("1",inputImg);
       return true;

   }
int main() {
    Mat src = imread("/home/xuxuxu/b/二维码测试图片/5.jpg");
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
    Point2f oritented_pt;
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
    for (int i = 0; i < contours2.size(); i++)
        drawContours(src_all, contours2, i, CV_RGB(0, 255, 255), 5);
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
        oritented_pt.x = (max_x + min_x) / 2;
        oritented_pt.y = (max_y + min_y) / 2;
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
            RotatedRect ll;
            oritented_pt.x = (max_x + min_x) / 2;
            oritented_pt.y = (max_y + min_y) / 2;
            cout<<"oritented_pt:("<<oritented_pt.x<<","<<oritented_pt.y<<")"<<endl;
            Find_QBar_RotateRect(src,oritented_pt,ll);
            waitKey(0);
            return true;
        }
}
    return false;
   }
