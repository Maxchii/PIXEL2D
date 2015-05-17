#pragma once
#include "SpriteBatch.h"
#include "..//Math/Matrix4x4.h"
#include "Shader.h"
#include "Drawable.h"
#include "..//Core/ValueTypes.h"

namespace PIXL { namespace graphics{

	class Layer final
	{
	public:
		Layer(SpriteBatch* spriteBatch, Shader* shader, const math::Matrix4x4& projectionMatrix);
		virtual ~Layer();

		virtual void Add(Drawable* drawable);
		void Draw();

		const std::vector<Drawable*>& GetDrawables() const;


	private:
		SpriteBatch* m_spriteBatch;
		std::vector<Drawable*> m_drawables;
		Shader* m_shader;
		math::Matrix4x4 m_projectionMatrix;
	};


} }