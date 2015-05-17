#include "Label.h"

namespace PIXL{ namespace graphics{

	Label::Label(const string& fontPath, const string& text, const math::Vector4& color /*= math::Vector4::One()*/, unsigned int size)
		: Drawable(math::Vector2::One(), color)
	{
		m_font = new Font(fontPath, size);
		m_text = text;
	}

	Label::Label(Font* font, const string& text, const math::Vector4& color /*= math::Vector4::One()*/)
	{
		m_font = font;
		m_text = text;
	}

	void Label::Draw(Renderer* renderer)
	{
		renderer->SubmitLabel(m_text, math::Vector3(100, 100, 0), *m_font, 0xffffff);
	}

	void Label::SetText(const string& text)
	{
		m_text = text;
	}

	const string& Label::GetText()
	{
		return m_text;
	}

	const void Label::SetFontSize(unsigned int size)
	{
		m_font->SetFontSize(size);
	}

}
}