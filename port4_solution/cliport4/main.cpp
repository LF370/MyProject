#include<vector>
#include<iostream>
#include<iterator>
#include<algorithm>

#include"../libport4/libport4.h"
using namespace std;

int main(void )
{	    
    double dist = 0;
    printf("------------------This is a test stub-----------------\n");
    char *driver = "SHAPE_ENCODING";
    int ret = initPiple(driver);
    char *piple_na = "/mnt/d/HDI.0X/data/shp/V20210208/lane_vector.shp";
    ret = openPiple( piple_na );

    vector<string> fld_nam_list;

    ret = getFeatureList( 1, fld_nam_list );

    for_each( fld_nam_list.begin(), fld_nam_list.end(),[]( string _na){

        cout <<_na.c_str() <<endl;

        
    });

    int feature_sz = getFeatureCount();
    vector<string> values;
   // ret = getFeatureValue( "rvid", values );
   ret = getFeatureGeom( values );
    cout <<"Feature size:"<< feature_sz << endl;
    copy( values.begin(), values.end(), ostream_iterator<string>(cout,"\n"));

    closePiple();
    


    
    







    
    #if 0
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
    errcode = calcSpheroidDist( x1,y1,x2,y2,&dist );
    if( errcode == 0 )
    {       
        printf("两点距离:%10.6lf\n", dist );
    }
    else{
        printf("计算部件构建失败\n");     

    }
    #endif

    ///
#if 0
    vector<pair<double,double>> polygon;
    
    polygon.push_back(make_pair(121.64725740959481,31.331267449549674)) ;
    polygon.push_back(make_pair(121.64727000108442,31.331284691559066)) ;
    polygon.push_back(make_pair(121.6473239128142,31.331255684813822));
    polygon.push_back(make_pair(121.64731110497914,31.3312380848898));
    polygon.push_back(make_pair(121.64725740959481,31.331267449549674));

    double x = 121.6472612;
    double y = 31.3312588;

    int ret = hitPolygon( x,y, polygon );

    cout << ret << endl;


    #endif




    return 0;

}
