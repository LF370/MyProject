#include<stdio.h>
#include "libport4.h"
//==========this is github=============//
int main(void)
{
    double dist = 0;
    printf("------------------This is a test stub-----------------\n");
    double x1 = 121.65182861167608;
    double y1 = 31.33557059614903;
    double x2 = 121.65179541635946;
    double y2 = 31.335588787755604;
    double x11 = x1, y11 = y1, x22 = x2, y22 = y2;
    int errcode = ( proj2spheroid( &x1,&y1, 4326,4549 ) || proj2spheroid( &x2,&y2, 4326,4549 ) );
    if( errcode != 0 )
    {
        printf("Transform xy failed......\n");
        return 0;
    }    
    
    errcode = calcPlaneDist(x1,y1,x2,y2,&dist ) ;
    if( errcode == 0 )
    {       
        printf("两点距离:%10.6lf\n", dist );
    }
    else{
        printf("计算部件构建失败\n");     

    }
    double dist1 = 0;
    errcode = calcSpheroidDist( x11,y11,x22,y22,&dist );
    if( errcode == 0 )
    {       
        printf("两点距离:%10.6lf\n", dist );
    }
    else{
        printf("计算部件构建失败\n");     

    }


    return errcode;
   
}
