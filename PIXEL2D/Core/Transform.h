#pragma once
#include "ValueTypes.h"
#include "..//Math/Math.h"
#include "Component.h"

namespace PIXL
{
	struct Transform final : public Component
	{
	public:
		Transform();

		const void updateTransformations();

		const math::Vector3& getPosition() const;
		const float getRotation() const;
		const math::Vector2& getScale()	const;
		const math::Matrix4x4& transformationMatrix() const;
		const math::Vector3& getUp() const;
		const math::Vector3& getRight()	const;

		void SetPosition(const math::Vector2& newPosition);
		void AddForce(const math::Vector2& newPosition);
		void Rotate(float newRotation);
		void Scale(const math::Vector2& newScale);

		void Init() override;
		void Update(Float32 deltaTime) override;
	private:
		bool m_needsUpdate;

		math::Vector3 m_up;
		math::Vector3 m_right;

		math::Vector3 m_position;
		float m_rotation;
		math::Vector2 m_scale;

		math::Matrix4x4 m_localMatrix;
	};
}