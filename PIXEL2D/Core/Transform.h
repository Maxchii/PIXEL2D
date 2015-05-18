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

		const math::Vector3& GetPosition() const;
		const float GetRotation() const;
		const math::Vector2& GetScale()	const;
		const math::Matrix4x4& GetLocalTransform() const;
		const math::Matrix4x4& GetWorldTransform() const;

		void SetPosition(const math::Vector2& newPosition);
		void AddForce(const math::Vector2& newPosition);
		void SetRotation(float newRotation);
		void SetScale(const math::Vector2& newScale);

		void Init() override;
		void Update(Float32 deltaTime) override;
		bool IsDirty();
		void SetDirty();

	private:
		bool m_needsUpdate;
		math::Vector3 m_position;
		float m_rotation;
		math::Vector2 m_scale;

		math::Matrix4x4 m_localMatrix;
		math::Matrix4x4 m_worldMatrix;
	};
}