#include "Audio.h"
#include "..//Debugging/Debug.h"

namespace PIXL{ namespace audio{

	FMOD::System* Audio::m_audioSystem;

	bool Audio::Init()
	{
		FMOD_RESULT result;
		unsigned int version;
		int numDrivers;
		FMOD_SPEAKERMODE speakermode;
		FMOD_CAPS caps;
		char name[256];

		//Create a system object and initializes
		result = FMOD::System_Create(&m_audioSystem);
		ErrorCheck(result);
		result = m_audioSystem->getVersion(&version);
		ErrorCheck(result);
		if (version < FMOD_VERSION)
		{
			string errorString = "Error! you are using an old version of FMOD! you are using version ";
			errorString.append(std::to_string(version)).append(" you need ").append(std::to_string(FMOD_VERSION));
			debugging::Debug::LogError(nullptr, errorString.c_str());
		}
		result = m_audioSystem->getNumDrivers(&numDrivers);
		ErrorCheck(result);
		if (numDrivers == 0)
		{
			result = m_audioSystem->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
			ErrorCheck(result);
		}
		else
		{
			result = m_audioSystem->getDriverCaps(0, &caps, 0, &speakermode);
			ErrorCheck(result);

			//Set the user selected speaker mode.
			result = m_audioSystem->setSpeakerMode(speakermode);
			ErrorCheck(result);
			if (caps & FMOD_CAPS_HARDWARE_EMULATED)
			{
				/*!
				* The user has the "accelteration" slider set to off! This is really bad for latency!
				*/
				debugging::Debug::LogWarning(nullptr, "Acceleration slider is set to off! this may cause bad audio latency!");
				result = m_audioSystem->setDSPBufferSize(1024, 10);
				ErrorCheck(result);
			}
			result = m_audioSystem->getDriverInfo(0, name, 256, 0);
			ErrorCheck(result);
			if (strstr(name, "SigmaTel"))
			{
				//SigmaTel sound device crackle for some reason if the format is PCM 16bit. PCM floating point output solves this issue.
				result = m_audioSystem->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 0, FMOD_DSP_RESAMPLER_LINEAR);
				ErrorCheck(result);
			}		
		}

		result = m_audioSystem->init(100, FMOD_INIT_NORMAL, 0);
		if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)
		{
			//the speaker mode selected isn't supported by this soundcard. switch back to stereo.
			result = m_audioSystem->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
			ErrorCheck(result);

			//re-init
			result = m_audioSystem->init(100, FMOD_INIT_NORMAL, 0);
		}
		ErrorCheck(result);

		return true;

	}

	void Audio::ErrorCheck(FMOD_RESULT result)
	{
		if (result != FMOD_OK)
		{
			string errorString = "FMOD Error! ";
			errorString.append(std::to_string(result));
			errorString.append(" ").append(FMOD_ErrorString(result));
			debugging::Debug::LogError(nullptr, errorString.c_str());
		}
	}

	void Audio::Update()
	{
		m_audioSystem->update();
	}

	FMOD::System& Audio::AudioSystem()
	{
		return *m_audioSystem;
	}

	

	

} }