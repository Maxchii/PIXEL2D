#pragma once
#include "ValueTypes.h"

namespace PIXL{
	struct Component
	{

		virtual void Init();
		virtual void Update(Float32 deltaTime);
		virtual void Draw();

		virtual ~Component();
	};
}