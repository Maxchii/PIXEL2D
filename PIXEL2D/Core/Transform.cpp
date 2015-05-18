#include "Transform.h"

namespace PIXL
{
	Transform::Transform() : m_needsUpdate(true)
	{
		
	}

	void Transform::Init()
	{
		m_rotation = 0;
		m_position.Set(0, 0, 0);
		m_scale.Set(1.0f, 1.0f);
		m_localMatrix = math::Matrix4x4::Identity();
	}

	const math::Vector3& Transform::GetPosition() const
	{
		return m_position;
	}

	const float Transform::GetRotation() const
	{
		return m_rotation;
	}

	const math::Vector2& Transform::GetScale() const
	{
		return m_scale;
	}

	const math::Matrix4x4& Transform::GetLocalTransform() const
	{
		return m_localMatrix;
	}

	const math::Matrix4x4& Transform::GetWorldTransform() const
	{
		return m_worldMatrix;
	}

	void Transform::SetPosition(const math::Vector2& newPosition)
	{
		m_position.Set(newPosition.x, newPosition.y, 0.0f);
		
		m_needsUpdate = true;
	}

	void Transform::AddForce(const math::Vector2& newPosition)
	{

	}

	void Transform::SetRotation(float newRotation)
	{
		m_rotation = newRotation;
		
		m_needsUpdate = true;
	}

	void Transform::SetScale(const math::Vector2& newScale)
	{
		m_scale = newScale;
		m_needsUpdate = true;
		
	}

	void Transform::Update(Float32 deltaTime)
	{
		if (m_needsUpdate)
		{
			
			m_localMatrix = math::Matrix4x4::Translate(math::Matrix4x4::Identity(), m_position);
			m_localMatrix = math::Matrix4x4::Rotate(m_localMatrix, m_rotation, math::Vector3::Forward());
			m_localMatrix = math::Matrix4x4::Scale(m_localMatrix, math::Vector3(m_scale.x, m_scale.y, 1.0f));

			if (entity->GetParent() != nullptr)
			{
				m_worldMatrix = entity->GetParent()->GetTransform().GetWorldTransform() * m_localMatrix;
			}
			else
			{
				m_worldMatrix = m_localMatrix;
			}

			std::vector<Entity*>& childs = entity->childs();
			for (size_t i = 0; i < childs.size(); i++)
			{
				childs[i]->GetTransform().IsDirty();
			}

			m_needsUpdate = false;
		}
	}

	bool Transform::IsDirty()
	{
		return m_needsUpdate;
	}

	

}