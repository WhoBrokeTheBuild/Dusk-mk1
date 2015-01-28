#ifndef DUSK_FUNC_H
#define DUSK_FUNC_H

#include <cstdio>

#include <string>
#include <algorithm>

#include "InterTexture.h"

using std::string;

void error( const string& msg, const bool& fatal = true );
string parse_ext( const string& str );
string format_float( const float& val );
void copy_pixels( void* source, void* dest, const unsigned int& x, const unsigned int& y,
                  const unsigned int& pitch, const unsigned short& bytesPerPixel, const bool& reverse );
bool import_image( const string& filename, InterTexture* pTexture );

#endif // DUSK_FUNC_H
