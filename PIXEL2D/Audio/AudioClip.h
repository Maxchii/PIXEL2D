#pragma once
#include "..//Core/ValueTypes.h"
#include <fmod.hpp>
#include <fmod_errors.h>


namespace PIXL { namespace audio{

	class AudioClip final
	{
	public:
		AudioClip(const string& filename, bool streamed);
		~AudioClip();

		void Play();
		void Loop(UInt32 amount = 0);
		void Pause();
		void Resume();
		void Stop();

		void SetVolume(Float32 volume);

		const Float32 GetVolume() const;
		const bool Playing() const;
	private:
		void ErrorCheck(FMOD_RESULT result);

		string m_filename;
		bool m_playing;
		Float32 m_volume;
		bool m_paused;
		bool m_looping;

		FMOD::Sound* m_sound;
		FMOD::Channel* m_channel;

	};

} }