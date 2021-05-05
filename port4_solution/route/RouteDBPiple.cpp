#include"RouteDBPiple.h"

int CRouteDBPiple::createPiple() const
{
    const char *shp_fmt = "SHAPE_ENCODING";
    int ret = initPiple(shp_fmt);
    if( ret == 0 ) return 0;        

    ret = openPiple( m_piple_driver.c_str(), m_piple_connector.c_str());

    return ret;
}

int CRouteDBPiple::initSqlCmdBuilder( string _xml_fna )
{
    return m_sqlcmd_builder.open( _xml_fna );    
}

int CRouteDBPiple::close() const
{
    return closePiple();
}

int CRouteDBPiple::getfld( RECORD _rec, int _n, FLDVALUE& _value ) const
{
     regex sep(g_token_sepator);
     sregex_token_iterator i_p( _rec.cbegin(), _rec.cend(), sep, -1 );
     sregex_token_iterator e;    
    vector<string> fields;   
    copy( i_p, e, back_inserter(fields));
    if( _n > fields.size() || _n < 1 ) return -1;
    else _value = fields[ _n-1 ];
    return 1;    
}

int CRouteDBPiple::collectLaneEdge( )
{
    vector<string> tables;
    string sql_cmd;
    // = "select rvid, id,rsecseq, num, source,target from tb_l_edge order by rvid,rsecseq,num";    
    int ret = m_sqlcmd_builder.getSqlCmd("Query","SEL_LOAD_ROUTE_EDGE", sql_cmd);
    if( ret ) return 0;
    cout <<sql_cmd << endl;

    ret = runSQL( sql_cmd, tables,false);

    regex sep("[ \t\n]*[:][ \t\n]*");
    for_each( tables.begin(), tables.end(), [&sep, this](string _ele){
        
        sregex_token_iterator i_p( _ele.cbegin(), _ele.cend(), sep, -1 );
        sregex_token_iterator e;
        string rvid = *i_p;
        
        auto& rec_list = m_data_set.RvID2LedgeListMap()[rvid];
        rec_list.push_back( _ele );  
    });
    return (int) m_data_set.RvID2LedgeListMap().size();
}


int CRouteDBPiple::filterLaneEdgeByR( TOKEN _rvid, int _secnum, vector<TOKEN>& _lvid )
{
    auto itr = m_data_set.RvID2LedgeListMap().find( _rvid );
    if( itr != m_data_set.RvID2LedgeListMap().end() )
    {
        auto& edge_vec = itr->second;
        regex sep(g_token_sepator);

        copy_if( edge_vec.begin(),edge_vec.end(), back_inserter(_lvid), [_secnum,this ](RECORD e){
            string fld_value;
            if( getfld( e, 3, fld_value) == -1 ) return false;
            else
                return (atoi( fld_value.c_str() ) == _secnum) ? true: false;        
        });        
        
    return _lvid.size();
    }
    else{
        return -1;
    }
}


