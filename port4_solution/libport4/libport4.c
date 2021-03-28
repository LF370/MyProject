#include "libport4.h"

#include<ogr_core.h>
#include<gdal_alg.h>
#include<ogr_srs_api.h>




int calcDist(double _x1, double _y1, double _x2, double _y2,  OGRSpatialReferenceH _srf, double * _dist )
{
    int errcode = 0;
     double x1 = _x1;
     double y1 = _y1;
     double x2 = _x2;
     double y2 = _y2;    
     
    OGRGeometryH p1;
    OGRGeometryH p2;

    char *p_wkt1 = (char*)malloc( MAX_BUFFER );
    char *p_wkt2 = (char*)malloc( MAX_BUFFER );       
    

    //sprintf( p_wkt1, "POINT(%20.10lf %20.10lf)", x1,y1 );
    //sprintf( p_wkt2, "POINT(%20.10lf %20.10lf)", x2,y2 );
    sprintf( p_wkt1, "LINESTRING(%20.10lf %20.10lf,%20.10lf %20.10lf)",x1,y1,x2,y2);
    
    char *d1 = p_wkt1;
    char *d2 = p_wkt2;
    if( _srf != NULL )
    {
        char *p_buff = NULL;
        OSRExportToWkt( _srf, &p_buff );
     //   printf("epsg:%s", p_buff);
    }

    OGRErr ret1 = OGR_G_CreateFromWkt( &p_wkt1, _srf, &p1 );
    //OGRErr ret2 = OGR_G_CreateFromWkt( &p_wkt2, _srf, &p2 );

    if ( ret1 != OGRERR_NONE 
    //|| ret2 != OGRERR_NONE 
    ) {
         errcode = 1;
         goto clear;
     }
     else
     {
         //(*_dist) = OGR_G_Distance( p1, p2 );
         (*_dist) = OGR_G_Length( p1 );
         OGR_G_DestroyGeometry( p1 );
         //OGR_G_DestroyGeometry( p2 );    

         errcode = 0;
     }

clear:    
    free( d1 );
    //free( d2 );   
final:
          
     return errcode;

}

DLL_EXPORT int proj2spheroid(double* _x1, double* _y1, int _src_srid, int _tag_srid )
{
     OGRSpatialReferenceH src_srid = OSRNewSpatialReference(NULL);
     OGRSpatialReferenceH tag_srid = OSRNewSpatialReference(NULL);

     OSRImportFromEPSG( src_srid, _src_srid );
     OSRImportFromEPSG( tag_srid, _tag_srid );     

     OGRCoordinateTransformationH p_trs =  OCTNewCoordinateTransformation( src_srid, tag_srid );

     int errcode = OCTTransform( p_trs, 1, _y1, _x1,NULL);
     
     OSRRelease( src_srid );
     OSRRelease( tag_srid );

     // 统一的错误返回码
     errcode = errcode == 1? 0:1;

     return errcode;    

}


 DLL_EXPORT int calcPlaneDist( double _x1, double _y1, double _x2, double _y2, double * _dist )
 {
     return calcDist(_x1,_y1, _x2, _y2, NULL, _dist );
 }


DLL_EXPORT int calcSpheroidDist( double _x1, double _y1, double _x2, double _y2, double * _dist )
{
     OGRSpatialReferenceH src_srid = OSRNewSpatialReference(NULL);
     OSRImportFromEPSG( src_srid, 4326 );

     return calcDist( _x1,_y1, _x2,_y2, src_srid, _dist );
}



