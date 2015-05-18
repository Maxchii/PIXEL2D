#pragma once
#include "..//Core/Component.h"
#include "Physics.h"

namespace PIXL{ namespace physics{

	enum ColliderType
	{
		STATIC = 0x1,
		DYNAMIC = 0x2
	};

	struct Collider : public Component
	{
	protected:
		Collider(const ColliderType& colliderType);
		virtual ~Collider();

		void Init() override;
		void Update(float deltaTime) override;


		ColliderType m_colliderType;
		b2World& m_world;
		b2Body* m_body;
	};

} }