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
	struct Layer
	{
	public:
		Layer(graphics::SpriteBatch* spriteBatch, graphics::Shader* shader, const math::Matrix4x4& projectionMatrix);
		virtual ~Layer();

		void Update(Float32 deltaTime);
		void Draw();
		void Refresh();
		void Clear();

		Entity& AddEntity();

	private:
		std::vector<std::unique_ptr<Entity>> m_entities;
		graphics::SpriteBatch* m_spriteBatch;
		graphics::Shader* m_shader;
		math::Matrix4x4 m_projectionMatrix;
	};
}