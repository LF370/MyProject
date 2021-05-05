#include "SqlCmdBuilder.h"

CSqlCmdBuilder::CSqlCmdBuilder( )
:m_p_root_node(nullptr), m_p_xml_doc( nullptr)
{

}

int CSqlCmdBuilder::open(string _xml_filena)
{
    m_p_xml_doc = new TiXmlDocument();
    if (!(m_p_xml_doc->LoadFile( _xml_filena ) ))
    {
        return 1;
    }

    m_p_root_node = m_p_xml_doc->RootElement();
    if( !m_p_root_node ) return 2;

    return 0;

}

int CSqlCmdBuilder::getSqlCmd( string _section, string _Identity, string& _sql_cmd )
{
    TiXmlNode* item = m_p_root_node->FirstChild( _section );
    if( !item ) return 1;

    auto* child = item->FirstChildElement( _Identity );
    if( !child ) return 2;
    _sql_cmd = child->GetText();
    return 0;   


}



