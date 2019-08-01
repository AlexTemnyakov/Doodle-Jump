/*******************************************************************
  Driver for MicroZed based MZ_APO board

	  author:	Alexander Temnyakov
      e-mail:   temnyale@fel.cvut.cz, alex.temnyakoff@yandex.ru
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#include <chrono>
#include <iostream> 
#include <cstdint>
#include "Timer.h"
using namespace std;

/* get time in milliseconds */
uint64_t Timer::milliseconds()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>
		(m_clock.now().time_since_epoch()).count();
}

/* get time in microseconds */
uint64_t Timer::microseconds()
{
	return std::chrono::duration_cast<std::chrono::microseconds>
		(m_clock.now().time_since_epoch()).count();
}

/* get time in nanoseconds */
uint64_t Timer::nanoseconds()
{
	return std::chrono::duration_cast<std::chrono::nanoseconds>
		(m_clock.now().time_since_epoch()).count();
}