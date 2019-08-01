/*******************************************************************
  Driver for MicroZed based MZ_APO board

	  author:	Alexander Temnyakov
      e-mail:   temnyale@fel.cvut.cz, alex.temnyakoff@yandex.ru
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#pragma once

#include <chrono>

using namespace std;

/* Class for accessing to time */
class Timer {
	static std::chrono::high_resolution_clock m_clock;

public:
	/* get time in milliseconds */
	static uint64_t milliseconds();
	/* get time in microseconds */
	static uint64_t microseconds();
	/* get time in nanoseconds */
	static uint64_t nanoseconds();
};