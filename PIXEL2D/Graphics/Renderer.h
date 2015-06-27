#pragma once
#include "..//Math/Math.h"
#include <vector>
#include "Font.h"

namespace PIXL{ namespace graphics{ class Drawable; } }

namespace PIXL { namespace graphics{

	class Renderer
	{
	public:
		virtual void Begin(){};
		virtual void Submit(graphics::Drawable*  const drawable) = 0;
		virtual void SubmitLabel(const string& text, const math::Vector3f& position, const Font& font, unsigned int color){}
		virtual void End(){};
		virtual void Flush() = 0;

		void Push(const math::Matrix4x4& matrix);
		void Pop();

	protected:
		Renderer();
		math::Matrix4x4* m_transformationBack;
		std::vector<math::Matrix4x4> m_transformationStack;
	};

} }