#include "Layer.h"

namespace PIXL { namespace graphics{

	Layer::Layer(SpriteBatch* spriteBatch, Shader* shader, const math::Matrix4x4& projectionMatrix)
		: m_spriteBatch(spriteBatch), m_shader(shader), m_projectionMatrix(projectionMatrix)
	{
		m_shader->Enable();
		GLint texIDs[] =
		{
			0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
			10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
			20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
			30, 31
		};
		m_shader->SetUniform1iv("textures", texIDs, 32);
		m_shader->SetUniformMat4("pr_matrix", m_projectionMatrix);
		m_shader->Disable();
	}

	void Layer::Add(Drawable* drawable)
	{
		m_drawables.push_back(drawable);
	}

	void Layer::Draw()
	{
		m_shader->Enable();
		m_spriteBatch->Begin();
		for (size_t i = 0; i < m_drawables.size(); i++)
		{
			m_drawables[i]->Draw(m_spriteBatch);
		}
		m_spriteBatch->End();
		m_spriteBatch->Flush();
	}

	const std::vector<Drawable*>& Layer::GetDrawables() const
	{
		return m_drawables;
	}

	Layer::~Layer()
	{
		delete m_spriteBatch;
		for (size_t i = 0; i < m_drawables.size(); i++)
		{
			delete  m_drawables[i];
		}
		m_drawables.clear();
	}

}
}