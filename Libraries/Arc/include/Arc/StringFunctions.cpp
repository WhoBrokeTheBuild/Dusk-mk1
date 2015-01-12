#include "StringFunctions.h"

const size_t Arc::StringBadPosition = string::npos;
const size_t Arc::StringBadLength   = string::npos;

string Arc::Arc_Basename( const string& path )
{
	char splitString = (path.find("\\") != StringBadPosition ? '\\' : '/');

	ArrayList<string> parts = Arc_StringSplit(path, splitString);

	if (parts.isEmpty())
		return "";

	return parts[parts.getSize() - 1];
}

string Arc::Arc_Dirname( const string& path )
{
	if (path.size() <= 1)
		return path;

	string tmpPath = path;

	char splitString = (tmpPath.find("\\") != StringBadPosition ? '\\' : '/');

	tmpPath.erase(std::find(tmpPath.rbegin(), tmpPath.rend(), splitString).base(), tmpPath.end());

	if (tmpPath.back() == splitString)
		tmpPath.pop_back();

	return tmpPath;
}

string Arc::Arc_FileExtension( const string& path )
{
	ArrayList<string> filenameParts = Arc_StringSplit(Arc_Basename(path), '.');

	string ext = filenameParts.getBack();
	Arc_StringToLower(ext);

	return ext;
}

void Arc::Arc_StringToLower( string& str )
{
	for (unsigned int i = 0; i < str.length(); ++i)
		str[i] = tolower(str[i]);
}

void Arc::Arc_StringToUpper( string& str )
{
	for (unsigned int i = 0; i < str.length(); ++i)
		str[i] = toupper(str[i]);
}

void Arc::Arc_StringUCWords( string& str )
{
	if (str.length() == 0)
		return;

	str[0] = toupper(str[0]);

	for (unsigned int i = 1; i < str.length(); ++i)
		if (str[i - 1] == ' ')
			str[i] = toupper(str[i]);
}

void Arc::Arc_StringUCFirst( string& str )
{
	if (str.length() == 0)
		return;

	str[0] = toupper(str[0]);
}

string Arc::Arc_StringGetUCWords( const string& str )
{
	string newStr = str;
	Arc_StringUCWords(newStr);
	return newStr;
}

string Arc::Arc_StringGetUCFirst( const string& str )
{
	string newStr = str;
	Arc_StringUCFirst(newStr);
	return newStr;
}

void Arc::Arc_TrimLeft( string& str )
{
	if (str.length() == 0)
		return;

	int end = -1;
	for (unsigned int i = 0; i < str.length(); ++i)
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\r' && str[i] != '\n')
		{
			end = i;
			break;
		}
	}

	if (end != -1)
	{
		str = Arc_Substring(str, end);
	}
}

void Arc::Arc_TrimRight( string& str )
{
	if (str.length() == 0)
		return;

	int start = -1;
	for (int i = str.length() - 1; i >= 0; --i)
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\r' && str[i] != '\n')
		{
			start = i + 1;
			break;
		}
	}

	if (start != -1)
	{
		str = Arc_Substring(str, 0, start);
	}
}

string Arc::Arc_GetTrimLeft( const string& str )
{
	string newStr = str;
	Arc_TrimLeft(newStr);
	return newStr;
}

string Arc::Arc_GetTrimRight( const string& str )
{
	string newStr = str;
	Arc_TrimRight(newStr);
	return newStr;
}

string Arc::Arc_GetTrim( const string& str )
{
	string newStr = str;
	Arc_Trim(newStr);
	return newStr;
}

Arc::ArrayList<string> Arc::Arc_StringSplit( const string& str, const string& sep, const int& limit /*= -1 */ )
{
	ArrayList<string> stringParts;

	unsigned int lastEnd = 0;
	for (unsigned int i = 0; i < str.length(); ++i)
	{
		bool check = true;
		for (unsigned int j = 0; j < sep.length(); ++j)
		{
			if (str[i + j] != sep[j])
			{
				check = false;
				break;
			}
		}

		if (check)
		{
			if (limit != -1 && stringParts.getSize() >= (unsigned)limit - 1)
				break;

			stringParts.add(str.substr(lastEnd, i - lastEnd));
			lastEnd = i + sep.length();
		}
	}

	if (lastEnd < str.length())
	{
		stringParts.add(str.substr(lastEnd));
	}

	return stringParts;
}

string Arc::Arc_StringJoin( const string& glue, const ArrayList<string>& pieces )
{
	string str;

	for (unsigned int i = 0; i < pieces.getSize(); ++i)
	{
		str += pieces[i];
		if (i != pieces.getSize() - 1)
			str += glue;
	}

	return str;
}

int Arc::Arc_StringReplaceNext( string& str, const string& search, const string& replace )
{
	unsigned int pos = str.find(search);

	if (pos == StringBadPosition)
		return -1;

	str.replace(pos, search.length(), replace);

	return pos;
}

int Arc::Arc_StringReplaceAll( string& str, const string& search, const string& replace )
{
	unsigned int pos = str.find(search);
	unsigned int count = 0;

	// TODO(sdl.slane@gmail.com): Prevent replacing the same text repeatedly
	while (pos != StringBadPosition)
	{
		str.replace(pos, search.length(), replace);
		pos = str.find(search);
		count++;
	}

	return count;
}

string Arc::Arc_Substring( const string& str, const unsigned int& begin, const int& maxLength /*= -1 */ )
{
	if (begin >= str.length())
		return "";

	unsigned int fullMaxLength = (maxLength < 0 ? StringBadLength : unsigned(maxLength));

	return str.substr(begin, fullMaxLength);
}

