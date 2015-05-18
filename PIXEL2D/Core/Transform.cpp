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


	math::Vector3 Transform::GetUp()
	{
		m_up;
	}

	math::Vector3 Transform::GetRight()
	{
		m_right;
	}

	void Transform::Update(Float32 deltaTime)
	{
		if (m_needsUpdate)
		{
			m_localMatrix =
				math::Matrix4x4::Translation(m_position)
				* math::Matrix4x4::Rotation(m_rotation, math::Vector3::Forward())
				* math::Matrix4x4::Scaled({ m_scale.x, m_scale.y, 1.0f });

			m_worldMatrix = m_localMatrix;

			if (entity->GetParent() != nullptr)
			{
				m_localMatrix = entity->GetParent()->GetTransform().GetLocalTransform() * m_localMatrix;
				m_worldMatrix = entity->GetParent()->GetTransform().GetWorldTransform() * m_worldMatrix;
			}
			
			m_right.Set(m_worldMatrix.elements[0], m_worldMatrix.elements[4], m_worldMatrix.elements[8]);
			m_up.Set(m_worldMatrix.elements[1], m_worldMatrix.elements[5], m_worldMatrix.elements[9]);

			std::vector<Entity*>& childs = entity->childs();
			for (size_t i = 0; i < childs.size(); i++)
			{
				childs[i]->GetTransform().SetDirty();
			}

			m_needsUpdate = false;
		}
	}

	bool Transform::IsDirty()
	{
		return m_needsUpdate;
	}

	void Transform::SetDirty()
	{
		m_needsUpdate = true;
	}

}