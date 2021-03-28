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
    int initPiple( char *_driver_str);
    // 打开一个管道（就是链接一个shp或其它数据源)
    int openPiple( char *_piple_na );
    // 关闭一个管道
    int closePiple();
    // 获取记录数量
    int getFeatureCount();
    // 获取属性列表
    int getFeatureList( int n, std::vector<std::string>& _feature_ls );
    // 获取某指定属性的集合
    int getFeatureValue( char* _fld_na, std::vector<std::string>& _values );
    // 获取几何形状几何，返回wkt 标准字符串
    int getFeatureGeom( std::vector< std::string >& _wkt_tbl);
#endif 


#endif