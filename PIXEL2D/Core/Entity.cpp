#include "Entity.h"
#include "EntityManager.h"
#include "Transform.h"

namespace PIXL
{
	Entity::Entity(EntityManager& entManager)
		: m_alive(true), m_manager(entManager) {}

	void Entity::Update(Float32 deltaTime)
	{
		for (std::size_t i = 0; i < m_components.size() ; i++)
		{
			m_components[i]->Update(deltaTime);
		}
	}

	void Entity::Draw(graphics::Renderer* renderer)
	{
		renderer->Push(GetComponent<Transform>().transformationMatrix());
		for (std::size_t i = 0; i < m_components.size(); i++)
		{
			m_components[i]->Draw(renderer);
		}
		renderer->Pop();
	}

	bool Entity::IsAlive() const
	{
		return m_alive;
	}

	void Entity::Destroy()
	{
		m_alive = false;
	}

}