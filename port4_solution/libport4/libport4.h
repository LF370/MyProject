#ifndef _LIBPORT4_H
#define _LIBPORT4_H

#define MAX_BUFFER 1024
#define DLL_EXPORT __attribute__ ((visibility("default")))


#ifdef __cplusplus 
extern "C"{    
#endif
    // 提供纯C 语言版本
    int proj2spheroid(double* _x1, double* _y1, int src_srid, int tag_srid );
    int calcPlaneDist( double _x1, double _y1, double _x2, double _y2, double * _dist );
    int calcSpheroidDist( double _x1, double _y1, double _x2, double _y2, double * _dist );
#ifdef __cplusplus 
}
#endif
#ifdef __cplusplus
#include<vector>
#include<string>
//  提供C++ 版本
    int hitPolygon( double _x1, double _y1, const std::vector<std::pair<double,double>>& _polygon );

// 读取符合OGR标准文件
    // 初始化环境
    int initPiple( const char *_driver_str);
    // 打开一个管道（就是链接一个shp或其它数据源)
    int openPiple( const char *_piple_na );

    // 打开一个管道
    int openPiple( const char *_driver, const char* _piple_n );
    // 关闭一个管道
    int closePiple();
    // 获取记录数量
    int getFeatureCount();
    // 获取属性列表
    int getFeatureList( int n, std::vector<std::string>& _feature_ls );
    // 获取某指定属性的集合
    int getFeatureValue( const char* _fld_na, std::vector<std::string>& _values );
    // 获取几何形状几何，返回wkt 标准字符串
    int getFeatureGeom( std::vector< std::string >& _wkt_tbl);

    // 执行SQL 指令, 无返回值
    int runSQL( std::string _sql);

    // 执行SQL 指令，有返回值，如调用存储过程
    int runSQL( std::string _sqlcmd, std::string& _ret_value );

    // 收集记录集合
    // _geom_flg ：是否加载geom字段
    int runSQL( std::string _sql, std::vector<std::string>& _table , bool _geom_flg= false, int bash=-1 ) ;
    
#endif 


#endif