#ifndef DUSK_TIME_INFO_H
#define DUSK_TIME_INFO_H

namespace Dusk
{

namespace Timing
{

/// A collection of timeing related information.
/**
 * Contains the Total Seconds and Milliseconds that have elapsed since the
 * program started running, as well as the seconds and milliseconds that have
 * elapsed since the last update and the Delta Time.
 */
class TimeInfo
{
public:

	TimeInfo() { }

	/// The total seconds that have elapsed since the program started
    double TotalSeconds;
	/// The total milliseconds that have elapsed since the program started
    double TotalMilliseconds;
	/// The seconds that have elapsed since the last update
    double ElapsedSeconds;
	/// The milliseconds that have elapsed since the last update
    double ElapsedMilliseconds;
	/// The measurement of time relative to the desired framerate.
	/**
	 * The value will be at 1.0 when the program is running normally, > 1.0
	 * when the program is running slowly, and < 1.0 when the program is
	 * running fast
	 */
    double Delta;

}; // class TimeInfo

} // namespace Timing

} // namespace Dusk

#endif // DUSK_TIME_INFO_H
