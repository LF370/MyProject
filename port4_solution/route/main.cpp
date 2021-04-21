#include<vector>
#include<iostream>
#include<iterator>
#include<algorithm>
#include<regex>

#include"../libport4/libport4.h"
using namespace std;

typedef string token;
typedef string record;
typedef string wkt;

class CRouteDataSet
{
    public:
    map<token,vector<record>>& RvID2LedgeListMap()
    {
        return m_rvid_ledgelist_map;
    }    
    private:
    map< token, vector<record>>  m_rvid_ledgelist_map;    
};

class CRouteRPath
{
    public:
    vector<token>& Path() { return m_rvid_pth;}
    wkt getFullPathLine() const {
        wkt  full_path_line;
        
        for(auto& e:m_rvid_pth)
        {
            auto itr = m_rvid_geo_map.find( e );
            if ( itr != m_rvid_geo_map.end() ) full_path_line+=itr->second;
        }
        return full_path_line;

    }   


    
  private:
  vector<token> m_rvid_pth;
  map<token, wkt> m_rvid_geo_map;

};
CRouteDataSet dataset;

int getfldn( record _rec, int n, string& _value )
{
     regex sep("[ \t\n]*[:][ \t\n]*");
     sregex_token_iterator i_p( _rec.cbegin(), _rec.cend(), sep, -1 );
     sregex_token_iterator e;    
    vector<string> fields;   
    copy( i_p, e, back_inserter(fields));
    if( n > fields.size() || n < 1 ) return -1;
    else _value = fields[n-1];
    return 1;    
}

int collectlaneEdge( )
{
    vector<string> tables;
    string sql_cmd = "select rvid, id,rsecseq, num, source,target from tb_l_edge order by rvid,rsecseq,num";
    cout <<sql_cmd.c_str() << endl;
    int ret = runSQL( sql_cmd, tables,false);

    regex sep("[ \t\n]*[:][ \t\n]*");
    for_each( tables.begin(), tables.end(), [&sep](string _ele){
        
        sregex_token_iterator i_p( _ele.cbegin(), _ele.cend(), sep, -1 );
        sregex_token_iterator e;
        string rvid = *i_p;
        auto& rec_list = dataset.RvID2LedgeListMap()[rvid];
        rec_list.push_back( _ele );  
    });
    return 0;
}


int filterLaneEdge( token _rvid, unsigned int _rsec, vector<token>& _lvid )
{
    auto itr = dataset.RvID2LedgeListMap().find( _rvid );
    if( itr != dataset.RvID2LedgeListMap().end() )
    {
        auto& edge_vec = itr->second;
        regex sep("[ \t\n]*[:][ \t\n]*");

        copy_if( edge_vec.begin(),edge_vec.end(), back_inserter(_lvid), [_rsec](record e){
            string fld_value;
            if( getfldn( e, 3, fld_value) == -1 ) return false;
            else
                return atoi( fld_value.c_str() ) == _rsec? true: false;        
        });        
        
    return _lvid.size();
    }
    else{
        return -1;
    }
}



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

    collectlaneEdge();

    auto& map = dataset.RvID2LedgeListMap();
    for( auto itr = map.begin(); itr != map.end(); ++itr )
    {
        cout<<"==========>"<<itr->first<<"<================="<< endl;
        auto& vec = itr->second;
      //  copy( vec.begin(), vec.end(),ostream_iterator<string>(cout,"\n"));
    }

    vector<token> vv;

    filterLaneEdge("721138899999457296",3,vv);

    copy( vv.begin(), vv.end(), ostream_iterator<string>(cout,"\n"));


}
