#include "Vector3.h"

Arc::Vector3 Arc::Vector3::ZERO = Vector3(0.0f);

Arc::Vector3 Arc::Vector3::ONE = Vector3(1.0f);

Arc::Vector3 Arc::Vector3::NEGATIVE_ONE = Vector3(-1.0f);

void Arc::Vector3::normalize( void )
{
	float length = getLength();
	if (length != 0)
	{
		m_X /= length;
		m_Y /= length;
		m_Z /= length;
	}
}

Arc::Vector3 Arc::Vector3::getNormalized( void )
{
	Vector3 copy = *this;
	copy.normalize();
	return copy;
}