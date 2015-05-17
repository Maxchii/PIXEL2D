#include "Time.h"
#include "..//Utilities/Timer.h"

namespace PIXL
{
	Float32 Time::m_time;
	Float32 Time::m_averageDeltaTime;
	Float32 Time::m_deltaTime;
	Float32 Time::m_previousFrame;
	Float32 Time::m_currentFrame;
	UInt32 Time::m_framesPerSecond;
	UInt32 Time::m_frames;
	utilities::Timer* Time::m_timer;

	void Time::Init()
	{
		m_frames = 0;
		m_framesPerSecond = 0;
		m_deltaTime = 0;
		m_averageDeltaTime = 0;
		m_time = 0;

		m_timer = new utilities::Timer();
		m_timer->reset();
		m_previousFrame = m_currentFrame = m_timer->elapsed();
	}

	void Time::Step()
	{
		m_currentFrame = m_timer->elapsed();
		m_deltaTime = (m_currentFrame - m_previousFrame);
		m_previousFrame = m_currentFrame;
		m_frames++;


		if (m_timer->elapsed() - m_time > 1.0f)
		{
			m_framesPerSecond = m_frames;
			m_averageDeltaTime = (m_timer->elapsed() - m_time) / m_frames;
			m_time += 1.0f;
			m_frames = 0;
		}
	}

	Float32 Time::GetDeltaTime() 
	{
		return m_deltaTime;
	}

	UInt32 Time::GetFps() 
	{
		return m_framesPerSecond;
	}

	Float32 Time::GetAverageDelta() 
	{
		return m_averageDeltaTime;
	}

	Float32 Time::GetTime()
	{
		return m_timer->elapsed();
	}
}