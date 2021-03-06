//
// Created by xuxuxu on 18-3-27.
//

#include "my_bar_code.h"

namespace mybar_code{
        string Bar_code::get_dealing_date() {
        time_t rawtime;
        struct tm *ptminfo;

        time(&rawtime);
        ptminfo = localtime(&rawtime);
        stringstream ss;
        ss<<ptminfo->tm_year + 1900<<"-"<<ptminfo->tm_mon + 1<<"-"<<ptminfo->tm_mday<<
            "  "<<ptminfo->tm_hour<<":"<<ptminfo->tm_min<<":"<<ptminfo->tm_sec;
            return ss.str();
    }
        string Bar_code::dealing_date=Bar_code::get_dealing_date();



    void Bar_code::bar_code_show(Bar_code& _bar_code) {
        cout<<"处理日期为： "<<_bar_code.dealing_date<<endl;
        cout<<"条形码的信息为："<<endl<<_bar_code.code_info<<endl;


    }

}