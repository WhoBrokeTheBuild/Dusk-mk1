#include "Vector2.h"

Arc::Vector2 Arc::Vector2::ZERO = Vector2(0.0f);

Arc::Vector2 Arc::Vector2::ONE = Vector2(1.0f);

Arc::Vector2 Arc::Vector2::NEGATIVE_ONE = Vector2(-1.0f);

void Arc::Vector2::normalize( void )
{
	float length = getLength();
	if (length != 0)
	{
		m_X /= length;
		m_Y /= length;
	}
}

Arc::Vector2 Arc::Vector2::getNormalized( void )
{
	Vector2 copy = *this;
	copy.normalize();
	return copy;
}