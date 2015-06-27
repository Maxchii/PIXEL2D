#pragma once
#include "..//Core/Component.h"
#include "..//Math/Math.h"
#include "Physics.h"

namespace PIXL{ namespace physics{

	enum ColliderType
	{
		STATIC = 0x1,
		DYNAMIC = 0x2
	};

	namespace PIXL{ struct Transform; }
	struct Collider : public Component
	{
	public:
		Collider(const ColliderType& colliderType);
		virtual ~Collider();
		void Init() override;
		void Update(float deltaTime) override;

		void SetPositionToSimUnits(const math::Vector2f ps);
		math::Vector2f GetPositionFromSimUnits();

	protected:
		ColliderType m_colliderType;
		b2World& m_world;
		b2Body* m_body;
		Transform* m_transform;
		math::Vector2f m_simPosition;


		math::Vector2f ToSimValue(const math::Vector2f ps);

	};

} }