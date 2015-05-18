#pragma once
#include "..//Core/ValueTypes.h"
#include <Box2D/Box2D.h>
#include "..//Math/Math.h"

namespace PIXL { class PIXL2D; }

namespace PIXL{ namespace physics{

	class Physics final
	{
		friend class PIXL2D;
	public:
		static void SetGravity(const math::Vector2& gravity);
		static void SetVelocityIterations(int32 amount);
		static void SetPositionIterations(int32 amount);
		static b2World& World();

	private:
		Physics();
		~Physics();
		void Init(const math::Vector2& gravity);
		void Update(Float32 deltaTime);

	private:
		static b2Vec2 m_gravity;
		static b2World* m_world;
		static int32 m_velocityIterations;
		static int32 m_positionIterations;
		
	};

} }