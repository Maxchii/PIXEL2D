#pragma once
#include "ValueTypes.h"
#include <vector>
#include <memory>

#include "..//Graphics/SpriteBatch.h"
#include "..//Math/Matrix4x4.h"
#include "..//Graphics/Shader.h"
#include "..//Graphics/Drawable.h"

namespace PIXL
{
	class Entity;
	struct EntityManager
	{
	public:
		EntityManager(graphics::SpriteBatch* spriteBatch, graphics::Shader* shader, const math::Matrix4x4& projectionMatrix);
		virtual ~EntityManager();

		void Update(Float32 deltaTime);
		void Draw();
		void Refresh();

		Entity& addEntity();

	private:
		std::vector<std::unique_ptr<Entity>> entities;

		graphics::SpriteBatch* m_spriteBatch;
		graphics::Shader* m_shader;
		math::Matrix4x4 m_projectionMatrix;
	};
}