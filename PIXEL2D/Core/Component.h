#pragma once
#include "ValueTypes.h"
#include "..//Graphics/Renderer.h"
#include "Entity.h"

namespace PIXL
{
	struct Component
	{
		Entity* entity;

		virtual void Init(){}
		virtual void Update(Float32 deltaTime){}
		virtual void Draw(graphics::Renderer* renderer){}

		virtual ~Component(){}
	};
}