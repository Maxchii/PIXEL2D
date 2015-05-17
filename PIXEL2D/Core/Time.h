#pragma once
#include "ValueTypes.h"

namespace PIXL{ class PIXL2D; }
namespace PIXL{ namespace utilities{ class Timer; } }

namespace PIXL
{
	class Time
	{
		friend class PIXL2D;
	public:
		static Float32 GetDeltaTime();
		static UInt32 GetFps();
		static Float32 GetAverageDelta();
		static Float32 GetTime();
	private:
		Time(){}
		~Time(){}

		void Init();
		void Step();

		static utilities::Timer* m_timer;
		static UInt32  m_frames;
		static UInt32  m_framesPerSecond;
		static Float32 m_currentFrame;
		static Float32 m_previousFrame;
		static Float32 m_deltaTime;
		static Float32 m_averageDeltaTime;
		static Float32 m_time;
	};
}