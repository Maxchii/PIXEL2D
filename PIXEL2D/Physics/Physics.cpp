#include "Physics.h"

namespace PIXL { namespace physics{

	int32 Physics::m_positionIterations;
	int32 Physics::m_velocityIterations;
	b2World* Physics::m_world;
	b2Vec2 Physics::m_gravity;

	Physics::Physics()
	{
		
	}

	void Physics::Init(const math::Vector2& gravity)
	{
		m_gravity.Set(gravity.x, gravity.y);
		m_world = new b2World(m_gravity);
		m_velocityIterations = 8;
		m_positionIterations = 3;
	}

	void Physics::Update(Float32 deltaTime)
	{
		m_world->Step(deltaTime, m_velocityIterations, m_positionIterations);
	}

	void Physics::SetGravity(const math::Vector2& gravity)
	{
		m_world->SetGravity(b2Vec2(gravity.x, gravity.y));
	}

	void Physics::SetVelocityIterations(int32 amount)
	{
		m_velocityIterations = amount;
	}

	void Physics::SetPositionIterations(int32 amount)
	{
		m_positionIterations = amount;
	}

	b2World& Physics::World()
	{
		return *m_world;
	}

	Physics::~Physics()
	{
		delete m_world;
	}

}
}