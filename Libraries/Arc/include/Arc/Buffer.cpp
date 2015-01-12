#include "Buffer.h"

Arc::Buffer::Buffer( const char* buffer, unsigned int size )
{
	setDataFromBuffer(buffer, size);
}

Arc::Buffer::Buffer( const string& text )
{
	setDataFromString(text);
}

Arc::Buffer::Buffer( std::istream& stream )
{
	setDataFromStream(stream);
}

bool Arc::Buffer::setDataFromStream( std::istream& stream )
{
	clear();
	return appendDataFromStream(stream);
}

void Arc::Buffer::setDataFromBuffer( const char* buffer, unsigned int size )
{
	clear();
	m_Buffer.resize(m_Buffer.getSize() + size + 1, 0);
	m_Buffer.assign(buffer, buffer + size);
	m_EndOfUsed = size;
}

void Arc::Buffer::setDataFromString( const string& text )
{
	setDataFromBuffer(text.c_str(), text.size());
}

void Arc::Buffer::setDataFromStringWithLength( const string& text )
{
	clear();
	appendShort(text.size());
	appendString(text);
}

void Arc::Buffer::appendBuffer( const Buffer& other )
{
	appendBuffer(&(other.m_Buffer[0]), other.getFullSize());
}

void Arc::Buffer::appendBuffer( const char* buffer, unsigned int size )
{
	if (m_EndOfUsed + size >= m_Buffer.getSize())
		m_Buffer.resize(m_EndOfUsed + size + 1);

	m_Buffer.insert(m_Buffer.itBegin() + m_EndOfUsed, buffer, buffer + size);
	m_EndOfUsed += size;
	m_Buffer[m_EndOfUsed + 1] = 0;
}

bool Arc::Buffer::appendDataFromStream( std::istream& stream )
{
	if (stream.bad())
		return false;

	const int TMP_BUFFER_SIZE = 4096;

	char tmp_buffer[TMP_BUFFER_SIZE];
	std::streamsize size = getFullSize();
	std::streamsize n = 0;
	do
	{
		stream.read(tmp_buffer, TMP_BUFFER_SIZE);
		n = stream.gcount();

		if (m_EndOfUsed + n > size)
		{
			std::streamsize overflow = (m_EndOfUsed + n) - size;
			m_Buffer.resize((unsigned int)(size + overflow + 1), 0);
		}

		memcpy(&(m_Buffer[0]) + m_EndOfUsed, tmp_buffer, (unsigned int)n);
		m_EndOfUsed += unsigned(n);

		if ( ! stream )
			break;
	}
	while (n > 0);

	return true;
}

bool Arc::Buffer::writeToStream( std::ostream& stream ) const
{
	if (stream.bad())
		return false;

	// Ignore trailing 0 for strings
	stream.write(&m_Buffer[0], m_Buffer.getSize() - 1);
	return true;
}

void Arc::Buffer::clear( void )
{
	m_EndOfUsed = 0;
	m_ReadIndex = 0;
	m_Buffer.resize(1);
	m_Buffer[0] = 0;
}

string Arc::Buffer::getText( void ) const
{
	if (m_Buffer.isEmpty())
		return "";

	return &m_Buffer[0];
}

void Arc::Buffer::resize( long size )
{
	if (m_EndOfUsed > unsigned(size))
		m_EndOfUsed = size;

	if (m_ReadIndex > unsigned(size))
		m_ReadIndex = size;

	m_Buffer.resize(size + 1);
	m_Buffer.getBack() = 0;
}

Arc::Buffer& Arc::Buffer::operator=( const string& text )
{
	setDataFromString(text);
	return *this;
}

string Arc::Buffer::readNextString( unsigned int size )
{
	if (endOfBuffer())
		return string();

	string val = readStringAt(m_ReadIndex, size);
	m_ReadIndex += size;
	return val;
}

string Arc::Buffer::readNextStringWithLength( void )
{
	if (endOfBuffer())
		return string();

	string val = readStringWithLengthAt(m_ReadIndex);
	m_ReadIndex += sizeof(short); // For the string length stored in the buffer
	m_ReadIndex += val.length() + 1;
	return val;
}

string Arc::Buffer::readNextLine( void )
{
	if (endOfBuffer())
		return false;

	string val = readLineAt(m_ReadIndex);
	m_ReadIndex += val.length() + 1;
	return val;
}

bool Arc::Buffer::readNextBool( void )
{
	if (endOfBuffer())
		return false;

	bool val = readBoolAt(m_ReadIndex);
	m_ReadIndex += sizeof(bool);
	return val;
}

short Arc::Buffer::readNextShort( void )
{
	if (endOfBuffer())
		return 0;

	short val = readShortAt(m_ReadIndex);
	m_ReadIndex += sizeof(short);
	return val;
}

int Arc::Buffer::readNextInt( void )
{
	if (endOfBuffer())
		return 0;

	int val = readIntAt(m_ReadIndex);
	m_ReadIndex += sizeof(int);
	return val;
}

long Arc::Buffer::readNextLong( void )
{
	if (endOfBuffer())
		return 0;

	long val = readLongAt(m_ReadIndex);
	m_ReadIndex += sizeof(long);
	return val;
}

char Arc::Buffer::readNextChar( void )
{
	if (endOfBuffer())
		return '\0';

	char val = readCharAt(m_ReadIndex);
	m_ReadIndex += sizeof(char);
	return val;
}

float Arc::Buffer::readNextFloat( void )
{
	if (endOfBuffer())
		return 0.0f;

	float val = readFloatAt(m_ReadIndex);
	m_ReadIndex += sizeof(float);
	return val;
}

double Arc::Buffer::readNextDouble( void )
{
	if (endOfBuffer())
		return 0.0;

	double val = readDoubleAt(m_ReadIndex);
	m_ReadIndex += sizeof(double);
	return val;
}

string Arc::Buffer::readStringAt( unsigned long offset, unsigned int size )
{
	char* buffer = new char[size + 1];

	memcpy(buffer, &(m_Buffer[0]) + offset, size);

	buffer[size] = '\0';
	string data = string(buffer);

	delete[] buffer;

	return data;
}

string Arc::Buffer::readStringWithLengthAt( unsigned long offset )
{
	short size = readShortAt(offset);
	return readStringAt(offset + sizeof(short), size);
}

string Arc::Buffer::readLineAt( unsigned long offset )
{
	unsigned long index = offset;
	unsigned long endOfLine = 0;
	while (index < m_EndOfUsed)
	{
		if (m_Buffer[index] == '\n')
		{
			endOfLine = index;
			break;
		}

		index++;
	}

	if (endOfLine == 0)
		return string();

	return readStringAt(offset, endOfLine - offset);
}

bool Arc::Buffer::readBoolAt( unsigned long offset )
{
	bool val;
	memcpy(&val, &(m_Buffer[0]) + offset, sizeof(bool));
	return val;
}

short Arc::Buffer::readShortAt( unsigned long offset )
{
	short val;
	memcpy(&val, &(m_Buffer[0]) + offset, sizeof(short));
	return val;
}

int Arc::Buffer::readIntAt( unsigned long offset )
{
	int val;
	memcpy(&val, &(m_Buffer[0]) + offset, sizeof(int));
	return val;
}

long Arc::Buffer::readLongAt( unsigned long offset )
{
	long val;
	memcpy(&val, &(m_Buffer[0]) + offset, sizeof(long));
	return val;
}

char Arc::Buffer::readCharAt( unsigned long offset )
{
	char val;
	memcpy(&val, &(m_Buffer[0]) + offset, sizeof(char));
	return val;
}

float Arc::Buffer::readFloatAt( unsigned long offset )
{
	float val;
	memcpy(&val, &(m_Buffer[0]) + offset, sizeof(float));
	return val;
}

double Arc::Buffer::readDoubleAt( unsigned long offset )
{
	double val;
	memcpy(&val, &(m_Buffer[0]) + offset, sizeof(double));
	return val;
}
