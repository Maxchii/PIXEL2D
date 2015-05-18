#include "Collider.h"

namespace PIXL { namespace physics{

	Collider::Collider(const ColliderType& colliderType)
		: m_world(Physics::World())
	{
		m_colliderType = colliderType;
	}

	void Collider::Init()
	{

	}

	void Collider::Update(float deltaTime)
	{

	}

	Collider::~Collider()
	{

	}

}
}