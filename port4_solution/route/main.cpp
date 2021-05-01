#include<vector>
#include<iostream>
#include<iterator>
#include<algorithm>
#include<regex>
#include"RouteDBPiple.h"
#include"../libport4/libport4.h"
using namespace std;


int main(void )
{	    
    const char *shp_fmt = "SHAPE_ENCODING";
    int ret = initPiple(shp_fmt);

    const char* pg_conn_str = "PG:dbname=port4_0329 host=localhost port=5432 user=lifei password=lifei";
    const char* p_drive_na = "PostgreSQL";

    ret = openPiple( p_drive_na, pg_conn_str );

    if( ret != 0 ){
        cout <<"open successfuly!"<< endl;
    }
    else{
        cout <<"open failed!"<< endl;
        return 0;
    }

    CRouteDBPiple db_piple;


  

}
