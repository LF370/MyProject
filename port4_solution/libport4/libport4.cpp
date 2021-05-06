#include "libport4.h"
#include<string>
#include<sstream>
#include<algorithm>
#include<iostream>
#include <ogr_geometry.h>
#include<ogrsf_frmts.h>
#include<cpl_config.h>
#include<cpl_conv.h>

using namespace std;

static GDALDataset * g_pDS(NULL);


DLL_EXPORT int hitPolygon( double _x1, double _y1, const std::vector<std::pair<double,double>>& _polygon )
{
    OGRSpatialReference srf;
    srf.importFromEPSG( 4326 );

    OGRGeometry *p_geo_face = NULL;
    OGRGeometry *p_geo_pt = NULL;

    stringstream sst;
    sst <<"POLYGON((";
    for_each( _polygon.begin(), _polygon.end(),[&sst](pair<double,double> ele ){
        sst.precision(20);
        sst << ele.first <<" "<< ele.second<<",";
    });
    string st_wkt = sst.str();
    st_wkt.pop_back();
    st_wkt.push_back(')');
    st_wkt.push_back(')');

    cout << st_wkt.c_str()<< endl;
  

    // 构造多边形对象
    auto err = OGRGeometryFactory::createFromWkt(st_wkt.c_str(), &srf, &p_geo_face );
    if( err != OGRERR_NONE ) return -1;

    // 构造点对象
    sst.clear();
    stringstream sst1;
    sst1.precision(20);
    sst1 <<"POINT("<< _x1 <<" " <<  _y1 <<")";
    st_wkt = sst1.str();
    cout << st_wkt.c_str()<< endl;
    err = OGRGeometryFactory::createFromWkt( st_wkt.c_str(), &srf, &p_geo_pt );
    if( err != OGRERR_NONE ) return -2;

    OGRBoolean ret = p_geo_face->Contains( p_geo_pt );

    return ret == TRUE? 1:0;

}
DLL_EXPORT int initPiple( const char *_driver_str)
{
    GDALAllRegister();
    CPLSetConfigOption( _driver_str,"" );
    return 1;
}

DLL_EXPORT int openPiple( const char* _piple_na )
{    
    g_pDS = (GDALDataset*)GDALOpenEx( _piple_na, GDAL_OF_VECTOR, NULL,NULL,NULL);
    return g_pDS? 1:0;
}

DLL_EXPORT int openPiple( const char *_driver, const char* _piple_n )
{     

    GDALDriver *poDriver = GetGDALDriverManager()->GetDriverByName( _driver );

    if( poDriver == NULL )
    {
        cout <<"Init pg failed!!!"<< endl;
        return 0;
    }      

    g_pDS = poDriver->Create( _piple_n,0,0,0,GDT_Unknown,NULL);
    return g_pDS? 1:0;
   
}

DLL_EXPORT int closePiple( )
{
    GDALClose( g_pDS );
    return 1;
}

DLL_EXPORT int getFeatureList( int n, vector<string>& _feature_ls )
{
    OGRLayer* ogr_layer = g_pDS->GetLayer(0);

    OGRFeatureDefn *ogr_fdef = ogr_layer->GetLayerDefn();

    int fld_n = ogr_fdef->GetFieldCount();

    vector<string> fld_name_tbl (fld_n);

    for( int i = 0; i < fld_n; i++ )
    {
        OGRFieldDefn* field = ogr_fdef->GetFieldDefn( i );
        _feature_ls.push_back( field->GetNameRef());
    }
    

    return (int) _feature_ls.size();
}

DLL_EXPORT int getFeatureCount()
{
    OGRLayer* p_layer = g_pDS->GetLayer(0);
    return p_layer->GetFeatureCount();
}

DLL_EXPORT int getFeatureValue( char * _fld_na, vector<string>& _values )
{
    int fld_i = 0;    
    OGRLayer* p_layer = g_pDS->GetLayer(0);
    p_layer->ResetReading();

    if( (fld_i = p_layer->FindFieldIndex( _fld_na ,FALSE)) ==-1)
    {
        return -1;
    }
    OGRFeature * p_feature (NULL);

    int fld_size = getFeatureCount();
    _values.reserve( fld_size );

    while( (p_feature = p_layer->GetNextFeature()) !=NULL )
    {        
         _values.push_back( p_feature->GetFieldAsString( fld_i ));   

    }

        return 1;

}

DLL_EXPORT int getFeatureGeom(std::vector< string >& _wkt_tbl)
{
    OGRLayer* p_layer = g_pDS->GetLayer(0);
    p_layer->ResetReading();

    
    OGRFeature * p_feature (NULL);

    int fld_size = getFeatureCount();
    _wkt_tbl.reserve( fld_size );

    while( (p_feature = p_layer->GetNextFeature()) !=NULL )
    {        
         OGRGeometry* p_geom = p_feature->GetGeometryRef();
         
         char *pszwkt = NULL;
         p_geom->exportToWkt(&pszwkt);
         _wkt_tbl.push_back( string(pszwkt ));
    }

     return 1;


}

DLL_EXPORT int runSQL(string _sql)
{    
    OGRLayer* p_layer = g_pDS->ExecuteSQL( _sql.c_str(), NULL, NULL );
    return p_layer? 1:0;    
}

DLL_EXPORT int runSQL(string _sql, string& _ret_value )
{    
    OGRLayer* p_layer = g_pDS->ExecuteSQL( _sql.c_str(), NULL, NULL );
    if( p_layer == 0 ) return 0;

    p_layer->ResetReading();     
     OGRFeatureDefn * fld_def = p_layer->GetLayerDefn();
     
     
     OGRFeature * fld;
     int row = 0;
     if ( (fld = p_layer->GetNextFeature() ) != NULL )
     {         
         _ret_value = fld->GetFieldAsString( 0 );
         return 1;
     }
     else
     {
         return 0;
     }  
    
}

    // 收集记录集合
DLL_EXPORT int runSQL( std::string _sql, std::vector<std::string>& _table , bool _geom_flg, int _bash  )
{
     OGRLayer* p_layer = g_pDS->ExecuteSQL( _sql.c_str(), NULL, NULL );
     if( p_layer == 0 ) return 0;

     p_layer->ResetReading();     
     OGRFeatureDefn * fld_def = p_layer->GetLayerDefn();
     int n_fld = fld_def->GetFieldCount();
     
     OGRFeature * fld;
     int row = 0;
     while(  (fld = p_layer->GetNextFeature() ) != NULL && ( _bash < 0 ? 1: ( row <_bash)) )
     {
         string values="";
         for( int i = 0; i< n_fld; i++ )
         {
             values += fld->GetFieldAsString( i );
             values +=":";             
         }

         if( _geom_flg )
         {
             OGRGeometry* p_geom = fld->GetGeometryRef();
             char *pszwkt = NULL;
             p_geom->exportToWkt(&pszwkt);
             values += string( pszwkt );         
         }
         else
         {
             values.pop_back();
         }       
         row++;      
         _table.push_back( values );
     }
     return _table.size();
}