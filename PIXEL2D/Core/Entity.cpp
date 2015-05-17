#include "Entity.h"
#include "EntityManager.h"

namespace PIXL
{
	Entity::Entity(EntityManager& entManager)
		: m_alive(true), m_manager(entManager) {}

	void Entity::Update(Float32 deltaTime)
	{
		for (int i = 0; i < m_components.size() ; i++)
		{
			m_components[i]->Update(deltaTime);
		}
	}

	void Entity::Draw()
	{
		for (int i = 0; i < m_components.size(); i++)
		{
			m_components[i]->Draw();
		}
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