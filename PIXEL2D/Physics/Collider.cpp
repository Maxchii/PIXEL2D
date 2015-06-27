#include "Collider.h"
#include "..//Core/Transform.h"
#include "..//Core/ValueTypes.h"
#include "..//Graphics/Window.h"

namespace PIXL { namespace physics{

	Collider::Collider(const ColliderType& colliderType)
		: m_world(Physics::World())
	{
		m_colliderType = colliderType;
	}

	void Collider::Init()
	{
		m_transform = &entity->GetTransform();
		SetPositionToSimUnits(math::Vector2f(m_transform->GetPosition().x, m_transform->GetPosition().y));

		b2BodyDef m_bodyDef;
		if (m_colliderType == STATIC)
			m_bodyDef.type = b2_staticBody;
		else if (m_colliderType == DYNAMIC)
			m_bodyDef.type = b2_dynamicBody;

		m_bodyDef.position.Set(1, 4);
		m_body = m_world.CreateBody(&m_bodyDef);

		b2PolygonShape groundBox;
		math::Vector2f simSize = ToSimValue(math::Vector2f(32,32));
		groundBox.SetAsBox(1, 1);

		b2FixtureDef fixDef;
		fixDef.shape = &groundBox;
		fixDef.density = 1.0f;
		fixDef.friction = 0.3f;

		m_body->CreateFixture(&fixDef);
	}

	void Collider::Update(float deltaTime)
	{
		std::cout << m_simPosition << std::endl;
	}

	Collider::~Collider()
	{

	}

	void Collider::SetPositionToSimUnits(const math::Vector2f ps)
	{
		Float32 w = float32(graphics::Window::Width());
		Float32 h = float32(graphics::Window::Height());
		Float32 u = ps.x / w;
		Float32 v = (h - ps.y) / h;

		float32 ratio = w / h;
		math::Vector2f extents(ratio * 25.0f, 25.0f);

		math::Vector2f lower = ps - extents;
		math::Vector2f upper = ps + extents;

		m_simPosition.Set((1.0f - u) * lower.x + u * upper.x, (1.0f - v) * lower.y + v * upper.y);
	}

	math::Vector2f Collider::GetPositionFromSimUnits()
	{
		Float32 w = Float32(graphics::Window::Width());
		Float32 h = float32(graphics::Window::Height());
		Float32 ratio = w / h;
		math::Vector2f extents(ratio * 25.0f, 25.0f);

		math::Vector2f lower = math::Vector2f(entity->GetTransform().GetPosition().x, entity->GetTransform().GetPosition().y) - extents;
		math::Vector2f upper = math::Vector2f(entity->GetTransform().GetPosition().x, entity->GetTransform().GetPosition().y) + extents;

		float32 u = (m_simPosition.x - lower.x) / (upper.x - lower.x);
		float32 v = (m_simPosition.y - lower.y) / (upper.y - lower.y);

		math::Vector2f ps;
		ps.x = u * w;
		ps.y = (1.0f - v) * h;
		return ps;
	}

	math::Vector2f Collider::ToSimValue(const math::Vector2f ps)
	{
		Float32 w = float32(graphics::Window::Width());
		Float32 h = float32(graphics::Window::Height());
		Float32 u = ps.x / w;
		Float32 v = (h - ps.y) / h;

		float32 ratio = w / h;
		math::Vector2f extents(ratio * 25.0f, 25.0f);

		math::Vector2f lower = ps - extents;
		math::Vector2f upper = ps + extents;

		return math::Vector2f((1.0f - u) * lower.x + u * upper.x, (1.0f - v) * lower.y + v * upper.y);
	}

} }