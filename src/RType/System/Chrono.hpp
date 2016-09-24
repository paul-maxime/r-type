#ifndef RTYPE_SYSTEM_CHRONO_HPP_
#define RTYPE_SYSTEM_CHRONO_HPP_

#include <ctime>
#include <chrono>
#include <iostream>
#include <iomanip>

// Implementing the solution of Matt Clarkson for the non implemented
// std::put_time from c++11 in gcc < 4.9.2
template<typename Clock, typename Duration>
std::ostream &operator<<(std::ostream &stream,
						 const std::chrono::time_point<Clock, Duration> &time_point)
{
	const std::time_t time = Clock::to_time_t(time_point);

	// GCC 4.9.2 has implemented std::put_time from C++11
# if RTYPE_IS_WIN32
	struct tm tm;

	// msvc only
	localtime_s(&tm, &time);
	return stream << std::put_time(&tm, "c");

# elif RTYPE_IS_UNIX && (__GNUC__ > 4 || (__GNUC__ == 4 && ((__GNUC_MINOR__ == 9 && __GNUC_REVISION__ >= 2) || __GNUC_MINOR__ > 9)))
	struct tm tm;

	std::localtime_r(&time, &tm);
	return stream << std::put_time(tm, "c");

# else
	char buffer[26];

	ctime_r(&time, buffer);
	// Removes the newline
	buffer[24] = '\0';
	return stream << buffer;

#endif // RTYPE_IS_WIN32
}

#endif // !RTYPE_SYSTEM_CHRONO_HPP_
