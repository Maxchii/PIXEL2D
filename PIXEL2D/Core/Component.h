#pragma once
#include "ValueTypes.h"
#include "..//Graphics/Renderer.h"

namespace PIXL
{
	class Entity;
	//namespace PIXL{ namespace graphics{ class Renderer; } }
	struct Component
	{
		Entity* entity;

		virtual void Init(){}
		virtual void Update(Float32 deltaTime){}
		virtual void Draw(graphics::Renderer* renderer){}

		virtual ~Component(){}
	};
}