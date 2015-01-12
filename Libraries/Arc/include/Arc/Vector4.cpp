#include "Vector4.h"

Arc::Vector4 Arc::Vector4::ZERO = Vector4(0.0f);

Arc::Vector4 Arc::Vector4::ONE = Vector4(1.0f);

Arc::Vector4 Arc::Vector4::NEGATIVE_ONE = Vector4(-1.0f);

void Arc::Vector4::normalize( void )
{
	float length = getLength();
	if (length != 0)
	{
		m_X /= length;
		m_Y /= length;
		m_Z /= length;
		m_W /= length;
	}
}

Arc::Vector4 Arc::Vector4::getNormalized( void )
{
	Vector4 copy = *this;
	copy.normalize();
	return copy;
}