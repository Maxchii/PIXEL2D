#pragma once
#include <chrono>

namespace PIXL { namespace utilities {

	class Timer
	{
	public:
		Timer(){ reset(); }

		inline void reset(){ m_Start = hrClock::now(); }

		inline float elapsed()
		{
			return std::chrono::duration_cast<milliseconds_type>(hrClock::now() - m_Start).count() / 1000.0f;
		}

	private:
		typedef std::chrono::high_resolution_clock hrClock;
		typedef std::chrono::duration<float, std::milli> milliseconds_type;
		std::chrono::time_point<hrClock> m_Start;
	};

} }