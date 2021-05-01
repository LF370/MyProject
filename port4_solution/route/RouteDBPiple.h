#ifndef _ROUTE_PIPLE_H 
#define _ROUTE_PIPLE_H

#include<vector>
#include<iostream>
#include<iterator>
#include<algorithm>
#include<string>
#include<regex>

#include"../libport4/libport4.h"

using namespace std;

typedef string TOKEN;
typedef string RECORD;
typedef string WKT;
typedef string FLDVALUE;

const string g_token_sepator ("[ \t\n]*[:][ \t\n]*");

class CRouteDataSet
{
    public:
    map<TOKEN,vector<RECORD>>& RvID2LedgeListMap()
    {
        return m_rvid_ledgelist_map;
    }    
    private:
    map< TOKEN, vector<RECORD>>  m_rvid_ledgelist_map;    
};

class CRouteRPath
{
    public:
    vector<TOKEN>& Path() { return m_rvid_pth;}
    WKT getFullPathLine() const {
        WKT  full_path_line;
        
        for(auto& e:m_rvid_pth)
        {
            auto itr = m_rvid_geo_map.find( e );
            if ( itr != m_rvid_geo_map.end() ) full_path_line+=itr->second;
        }
        return full_path_line;
    }       
  private:
  vector<TOKEN> m_rvid_pth;
  map<TOKEN, WKT> m_rvid_geo_map;

};


class CRouteDBPiple
{
    public:



    public:

    

    int collectLaneEdge();
    
    
    // _secum 0 : the first section
    //        1..n : the section 
    //        -1: the last section
    int filterLaneEdgeByR( TOKEN _rvid, int _secnum, vector<TOKEN>& _lvid_tb );


    private:
    int getfld( RECORD _rec, int _n, FLDVALUE& _value ) const ;

    private:

    CRouteDataSet m_data_set;



};

#endif