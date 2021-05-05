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
    
    CRouteDBPiple route_piple;

    route_piple.pipleDriver() = "PostgreSQL";
    route_piple.pipleConnector() =  "PG:dbname=port4_0329 host=localhost port=5432 user=lifei password=lifei";

    int ret = route_piple.createPiple();
    if( ret != 0 ){
        cout <<"open successfuly!"<< endl;
    }
    else{
        cout <<"open failed!"<< endl;
        return 0;
    }

    int err = route_piple.initSqlCmdBuilder( "SqlCmd.xml");
    if( err )
    {
        cout <<"Initliza sql xml fault!" << endl;
        return 0;
    }

    

    int loadsz = route_piple.collectLaneEdge();
    cout <<"Collected finished.........."<< loadsz << endl;


    route_piple.close();    
  

  

}
