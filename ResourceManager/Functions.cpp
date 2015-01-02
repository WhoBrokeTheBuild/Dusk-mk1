#include "Functions.h"

void error( const string& msg, const bool& fatal /*= true*/ )
{
    printf("Error: %s\n", msg.c_str());
    if (fatal)
        exit(1);
}

string parse_ext( const string& str )
{
    size_t period_pos = str.rfind('.');

    if (period_pos == string::npos)
        return "";

    string ext = str.substr(period_pos + 1);

    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    return ext;
}
