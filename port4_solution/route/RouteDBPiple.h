#ifndef _ROUTE_PIPLE_H 
#define _ROUTE_PIPLE_H

#include<vector>
#include<iostream>
#include<iterator>
#include<algorithm>
#include<string>
#include<regex>

#include"../libport4/libport4.h"
#include"SqlCmdBuilder.h"

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
    // 打开一个管道
    int createPiple() const ;
    // 关闭一个管道
    int close() const;

    int initSqlCmdBuilder(string _xml_filena);

    public:
    string& pipleConnector() { return m_piple_connector; }
    string& pipleDriver() { return m_piple_driver; }

    public:   
    // SQL 业务
    // 收集所有的车道关联关系
    int collectLaneEdge();

    // SQL 业务
    // 获取给定点最近的拓扑顶点
    int getNearestVertic( double _x, double _y, double _z, bool _se, int& _vertic_id );
    
    
    
    // _secum 0 : the first section
    //        1..n : the section 
    //        -1: the last section
    int filterLaneEdgeByR( TOKEN _rvid, int _secnum, vector<TOKEN>& _lvid_tb );

    


    private:
    // 记录集处理工具
    int getfld( RECORD _rec, int _n, FLDVALUE& _value ) const ;

    private:
    CRouteDataSet m_data_set;

    string m_piple_connector;
    string m_piple_driver;

    CSqlCmdBuilder m_sqlcmd_builder;


};

#endif