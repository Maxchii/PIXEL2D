#pragma once
#include "Drawable.h"
#include "..//Math/Math.h"
#include "Font.h"

namespace PIXL{	namespace graphics{

	class Label final : public Drawable
	{
	public:
		Label(const string& fontPath, const string& text, const math::Vector4& color = math::Vector4::One(), unsigned int size = 32);
		Label(Font* font, const string& text, const math::Vector4& color = math::Vector4::One());

		void Draw(Renderer* renderer) override;
		void SetText(const string& text);
		const string& GetText();
		const void SetFontSize(unsigned int size);
	private:
		Font* m_font;
		string m_text;
	};

} }