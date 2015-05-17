#include "Transform.h"

namespace PIXL
{
	Transform::Transform() : m_needsUpdate(true)
	{
		
	}

	void Transform::Init()
	{
		m_up.Set(0, 1.0f, 0);
		m_right.Set(1.0f, 0, 0);
		m_rotation = 0;
		m_position.Set(0, 0, 0);
		m_scale.Set(1.0f, 1.0f);
		m_localMatrix = math::Matrix4x4::Identity();
	}

	const void Transform::updateTransformations()
	{
		m_needsUpdate = true;
	}

	const math::Vector3& Transform::getPosition() const
	{
		return m_position;
	}

	const float Transform::getRotation() const
	{
		return m_rotation;
	}

	const math::Vector2& Transform::getScale() const
	{
		return m_scale;
	}

	const math::Matrix4x4& Transform::transformationMatrix() const
	{
		return m_localMatrix;
	}

	const math::Vector3& Transform::getUp() const
	{
		return m_up;
	}

	const math::Vector3& Transform::getRight() const
	{
		return m_right;
	}

	void Transform::SetPosition(const math::Vector2& newPosition)
	{
		m_position.Set(newPosition.x, newPosition.y, 0.0f);
		m_needsUpdate = true;
	}

	void Transform::AddForce(const math::Vector2& newPosition)
	{

	}

	void Transform::Rotate(float newRotation)
	{
		m_rotation = newRotation;
		m_needsUpdate = true;
	}

	void Transform::Scale(const math::Vector2& newScale)
	{
		m_scale = newScale;
		m_needsUpdate = true;
	}

	void Transform::Update(Float32 deltaTime)
	{
		if (m_needsUpdate)
		{
			m_localMatrix = math::Matrix4x4::Translate(m_localMatrix, m_position);
			m_localMatrix = math::Matrix4x4::Rotate(m_localMatrix, m_rotation, math::Vector3::Forward());
			m_localMatrix = math::Matrix4x4::Scale(m_localMatrix, math::Vector3(m_scale.x, m_scale.y, 1.0f));

			m_needsUpdate = false;
		}
	}

}