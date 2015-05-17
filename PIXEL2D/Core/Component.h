#pragma once
#include "ValueTypes.h"

namespace PIXL
{
	class Entity;
	class Component
	{
	public:
		Entity* entity;

		virtual void Init(){}
		virtual void Update(Float32 deltaTime){}
		virtual void Draw(){}

		virtual ~Component(){}
	};
}