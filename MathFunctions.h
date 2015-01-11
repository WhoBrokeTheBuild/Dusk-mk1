#ifndef DUSK_MATH_FUNCTIONS_H
#define DUSK_MATH_FUNCTIONS_H

#include <cstdarg>

/* Determines if a value is between two other numbers
 *
 * @param value: The value to check
 * @param min: The minimum value of the range to check
 * @param max: The maximum value of the range to check
 * @returns: True if the value is between the min and max values or equal to either, False otherwise
 */
template <class Number>
inline bool Between( Number value, Number min, Number max )
{
    return ( value >= min && value <= max );
}

/* Calculates a linear interpolation
 *
 * @param start: The number to start at, returned when fraction is 0
 * @param end: The number to end at, returned when fraction is 1
 * @param fraction: The value from 0 to 1 to interpolate between the two numbers where
 *     a value of 0 will return the start number, and a value of 1 will return the end
 * @returns: A number between the start and end values, determined by the fraction amount
 */
template <class Number>
inline Number Lerp( Number start, Number end, float fraction )
{
    return ( Number )( start + ( end - start ) * fraction );
}

template <class Number>
inline Number Clamp( Number value, Number min, Number max )
{
    return ( ( value > max ) ? max : ( ( value < min ) ? min : value ) );
}

template <class Number>
inline int Sign( Number value )
{
    return ( value > 0 ? 1 : ( value < 0 ? -1 : 0 ) );
}

#endif // DUSK_MATH_FUNCTIONS_H
