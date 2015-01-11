#ifndef DUSK_FUCNTIONS_H
#define DUSK_FUCNTIONS_H

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

inline void LogError( const string& source, const string& msg )
{
    cout << "[" << source << "] Error: " << msg << endl;
}

inline void LogInfo( const string& source, const string& msg )
{
    cout << "[" << source << "] Info: " << msg << endl;
}

#endif // DUSK_FUCNTIONS_H
