//
// Created by xuduo on 17-7-3.
//

#include "Predictor.h"

#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;

namespace  hitcrt{

void Predictor::setRecord(double _value, double _time) {
    if(m_history_time.size() < m_history_max_size) {
        m_history_time.push_back(_time);
        m_history_value.push_back(_value);
    }else{
        m_history_time.push_back(_time);
        m_history_value.push_back(_value);
        m_history_time.pop_front();
        m_history_value.pop_front();
    }

}

    double Predictor::predict(double _time) {
        list<double>::const_iterator it_in = m_history_time.begin();
        double latest_value = m_history_value.back();
        if(abs(latest_value) < 0.8 || m_history_value.size() < m_history_max_size)  //5个像素以内不再预测
        {
//            cout << "predict return target move slowly latest_value" << abs(latest_value) << endl;
            return latest_value;
        }
        if(m_history_time.back() - *it_in > 1.0)  //时间太长,可能不是同一个装甲
        {
            cout << "predict return time out " << endl;
            return latest_value;
        }
        list<double>::const_iterator it_out = m_history_value.begin();
        list<double>::const_iterator prev_out = it_out;
        double max_o = -500000, min_o = 500000;
        for(list<double>::const_iterator it = it_out, it_i = it_in; it != m_history_value.end(); ++it, ++it_i){
            if(max_o < *it)
                max_o = *it;
            if(min_o > *it)
                min_o = *it;
            if(abs(*it - *prev_out) > 5.0){     //连续两帧角度不高于5度
                cout << "predict return target move roughly " << endl;
                return latest_value;
            }
            prev_out = it;
            //printf("(%2f,%2f) ", *it, *it_i);
        }
//        cout << "angle gap " << max_o - min_o << endl;
//        if (max_o - min_o < 5.0)      // angle gap must lager than 3 degree, 否则没有必要
//        {
//            cout << "predict return gap too small " << endl;
//            return latest_value;
//        }
        cv::Mat A(m_history_max_size,3,CV_64F);
        cv::Mat b(m_history_max_size,1,CV_64F);
        double * b_data = (double *) b.data;
        double * A_data = (double *) A.data;
        for (; it_in != m_history_time.end(); ++A_data, ++b_data, ++it_in, ++it_out){
            *A_data = (*it_in-_time) * (*it_in-_time);
            *(++A_data) = (*it_in-_time);
            *(++A_data) = 1;
            *b_data = *it_out;
        }
        cv::Mat A_t = A.t();
        cv::Mat w = (A_t*A).inv()*A_t * b;
        double predict_angle = w.at<double>(2);
        const double max_gap = 3.0;
        if(predict_angle - latest_value > max_gap)      //确定极值
            predict_angle = latest_value + max_gap;
        else if(predict_angle - latest_value < -max_gap)
            predict_angle = latest_value - max_gap;
        return predict_angle;

    }


}
