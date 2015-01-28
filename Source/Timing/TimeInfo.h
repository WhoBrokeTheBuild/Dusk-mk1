#ifndef DUSK_TIME_INFO_H
#define DUSK_TIME_INFO_H

namespace Dusk
{

namespace Timing
{

class TimeInfo
{
public:

	TimeInfo() { }

    double TotalSeconds;
    double TotalMilliseconds;
    double ElapsedSeconds;
    double ElapsedMilliseconds;

    double Delta;

}; // class TimeInfo

} // namespace Timing

} // namespace Dusk

#endif // DUSK_TIME_INFO_H
