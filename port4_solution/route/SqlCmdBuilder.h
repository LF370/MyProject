#ifndef _SQL_CMD_BUILDER_H
#define _SQL_CMD_BUILDER_H
#include <string>
#include <tinyxml.h>
using namespace std;

class CSqlCmdBuilder
{
public:
    CSqlCmdBuilder();

public:
    int open(string _xml_filena );

    int getSqlCmd(string _section, string _identify, string& _sql_cmd );

private:
    TiXmlDocument *m_p_xml_doc;
    TiXmlElement *m_p_root_node;
    string m_xml_filena;
};
#endif