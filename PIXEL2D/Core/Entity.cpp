#include "Entity.h"
#include "Layer.h"
#include "Transform.h"
#include "Component.h"
#include "..\Debugging\Debug.h"

namespace PIXL
{
	Entity::Entity(Layer& entManager)
		: m_alive(true), m_manager(entManager), m_parent(nullptr) {}

	void Entity::Init()
	{
		m_transform = &AddComponent<Transform>();
	}

	void Entity::SetParent(Entity& entity)
	{
		m_parent = &entity;
		entity.m_childs.push_back(this);
	}

	void Entity::Update(Float32 deltaTime)
	{
		//float temp = m_transform->GetRotation();
		//m_transform->SetRotation(temp += 20 * deltaTime);

		for (std::size_t i = 0; i < m_components.size() ; i++)
		{
			m_components[i]->Update(deltaTime);
		}
	}

	void Entity::Draw(graphics::Renderer* renderer)
	{
		renderer->Push(m_transform->GetWorldTransform());
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