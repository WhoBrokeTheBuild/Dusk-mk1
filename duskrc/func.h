#ifndef DUSK_FUNC_H
#define DUSK_FUNC_H

#include <cstdio>

#include <string>
#include <algorithm>

using std::string;

void error( const string& msg, const bool& fatal = true );
string parse_ext( const string& str );

#endif // DUSK_FUNC_H
