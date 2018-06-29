//
// Created by xuduo on 17-7-3.
//

#ifndef RM_PREDICTOR_H
#define RM_PREDICTOR_H

#include <list>

namespace hitcrt{
class Predictor {
public:
    Predictor(int _history_size = 5) : m_history_max_size(_history_size) { }
    void setRecord(double value, double time);
    double predict(double time);
    void clear(){
        m_history_value.clear();
        m_history_time.clear();
    }
private:
    std::list<double> m_history_value;
    std::list<double> m_history_time;
    int m_history_max_size;
};
}



#endif //RM_PREDICTOR_H
