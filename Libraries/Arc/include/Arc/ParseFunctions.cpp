#include "ParseFunctions.h"

short Arc::Arc_ParseShort( const string& str )
{
	static std::stringstream ss;
	ss.clear();
	ss.str(str);

	short val;
	ss >> val;

	return val;
}

int Arc::Arc_ParseInt( const string& str )
{
	static std::stringstream ss;
	ss.clear();
	ss.str(str);

	int val;
	ss >> val;

	return val;
}

long Arc::Arc_ParseLong( const string& str )
{
	static std::stringstream ss;
	ss.clear();
	ss.str(str);

	long val;
	ss >> val;

	return val;
}

float Arc::Arc_ParseFloat( const string& str )
{
	static std::stringstream ss;
	ss.clear();
	ss.str(str);

	float val;
	ss >> val;

	return val;
}

double Arc::Arc_ParseDouble( const string& str )
{
	static std::stringstream ss;
	ss.clear();
	ss.str(str);

	double val;
	ss >> val;

	return val;
}

bool Arc::Arc_ParseBool( const string& str )
{
	if (Arc_StringGetLower(str) == "true" || Arc_ParseInt(str) == 1)
		return true;

	return false;
}
