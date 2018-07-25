//
// Created by xuxuxu on 18-7-20.
//

#include "Get3Points.h"
namespace FIT_PL {

    void Get_3Points(Eigen::Vector3d& a,Eigen::Vector3d& b,Eigen::Vector3d& c )
    {
        double d,e,f;
        cout<<"请输入第一个点的坐标： "<<endl<<"x= ";
        cin>>d;
        cout<<endl<<"y= ";
        cin>>e;
        cout<<endl<<"z= ";
        cin>>f;
        a<<d,e,f;
        cout<<"请输入第二个点的坐标： "<<endl<<"x= ";
        cin>>d;
        cout<<endl<<"y= ";
        cin>>e;
        cout<<endl<<"z= ";
        cin>>f;
        b<<d,e,f;
        cout<<"请输入第三个点的坐标： "<<endl<<"x= ";
        cin>>d;
        cout<<endl<<"y= ";
        cin>>e;
        cout<<endl<<"z= ";
        cin>>f;
        c<<d,e,f;

    }
}