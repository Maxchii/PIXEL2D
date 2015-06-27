#pragma once
#include "ValueTypes.h"
#include "..//Math/Math.h"
#include "Component.h"
#include "..//Physics/Collider.h"

namespace PIXL
{
	struct Transform final : public Component
	{
	public:
		Transform();

		const math::Vector3f& GetPosition() const;
		const float GetRotation() const;
		const math::Vector2f& GetScale()	const;
		const math::Matrix4x4& GetLocalTransform() const;
		const math::Matrix4x4& GetWorldTransform() const;

		void SetPosition(const math::Vector2f& newPosition);
		void AddForce(const math::Vector2f& newPosition);
		void SetRotation(float newRotation);
		void SetScale(const math::Vector2f& newScale);

		void Init() override;
		void Update(Float32 deltaTime) override;
		bool IsDirty();
		void SetDirty();

		math::Vector3f GetUp();
		math::Vector3f GetRight();

	private:
		bool m_needsUpdate;
		math::Vector3f m_position;
		float m_rotation;
		math::Vector2f m_scale;

		math::Matrix4x4 m_localMatrix;
		math::Matrix4x4 m_worldMatrix;

		math::Vector3f m_up;
		math::Vector3f m_right;

		physics::Collider* m_collider;
	};
}