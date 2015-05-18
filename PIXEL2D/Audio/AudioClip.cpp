#include "AudioClip.h"
#include "..//Debugging/Debug.h"
#include "Audio.h"

namespace PIXL{ namespace audio{

	AudioClip::AudioClip(const string& filename, bool streamed)
		: m_channel(0), m_playing(false), m_paused(false), m_looping(false), m_volume(1.0f)
	{
		if (!streamed)
			ErrorCheck(Audio::AudioSystem().createSound(filename.c_str(), FMOD_DEFAULT, 0, &m_sound));
		else
			ErrorCheck(Audio::AudioSystem().createStream(filename.c_str(), FMOD_DEFAULT, 0, &m_sound));
	}

	void AudioClip::Play()
	{
		if (!m_playing){
			Audio::AudioSystem().playSound(FMOD_CHANNEL_REUSE, m_sound, false, &m_channel);
			m_playing = true;
			m_paused = false;
		}
	}

	void AudioClip::Loop(UInt32 amount)
	{
		m_sound->setMode(FMOD_LOOP_NORMAL);
		m_sound->setLoopCount(amount);
		m_looping = true;
	}

	void AudioClip::Pause()
	{
		if (!m_playing)
			return;

		m_channel->setPaused(true);
		m_playing = false;
		m_paused = true;
	}

	void AudioClip::Resume()
	{
		if (m_playing)
			return;

		m_channel->setPaused(false);
		m_playing = true;
		m_paused = false;
	}

	void AudioClip::Stop()
	{
		if (m_looping)
		{
			m_sound->setMode(FMOD_LOOP_OFF);
			m_looping = false;
		}
		m_playing = false;
		m_paused = true;
		m_channel->stop();
	}

	void AudioClip::SetVolume(float volume)
	{
		if (volume < 0.0f)
			volume = 0.0f;

		if (volume > 1.0f)
			volume = 1.0f;

		m_channel->setVolume(volume);
		m_volume = volume;
	}

	void AudioClip::ErrorCheck(FMOD_RESULT result)
	{
		if (result != FMOD_OK)
		{
			string errorString = "FMOD Error! ";
			errorString.append(std::to_string(result));
			errorString.append(" ").append(FMOD_ErrorString(result));
			debugging::Debug::LogError(nullptr, errorString.c_str());
		}
	}

	AudioClip::~AudioClip()
	{
		ErrorCheck(m_sound->release());
	}
}
}