#include "Renderer.h"

namespace PIXL{ namespace graphics{

	Renderer::Renderer()
	{
		m_transformationStack.push_back(math::Matrix4x4::Identity());
		m_transformationBack = &m_transformationStack.back();
	}

	void Renderer::Push(const math::Matrix4x4& matrix)
	{
		m_transformationStack.push_back(/*m_transformationStack.back() * */matrix);
		m_transformationBack = &m_transformationStack.back();
	}

	void Renderer::Pop()
	{
		if (m_transformationStack.size() > 1)
		{
			m_transformationStack.pop_back();
			m_transformationBack = &m_transformationStack.back();
		}
	}

}
}