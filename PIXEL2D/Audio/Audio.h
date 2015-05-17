#pragma once
#include <fmod.hpp>
#include <fmod_errors.h>
#include "..//Core/ValueTypes.h"

namespace PIXL{ class PIXL2D; }

namespace PIXL { namespace audio {

	class Audio final
	{
		friend class PIXL2D;
	public:
		static FMOD::System& AudioSystem();
	private:
		Audio(){}
		~Audio(){}

		bool Init();
		void Update();
		void ErrorCheck(FMOD_RESULT result);

		static FMOD::System* m_audioSystem;
	};

} }