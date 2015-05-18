#pragma once
#include "..//Ext/freetype-gl/freetype-gl.h"
#include "..//Core/ValueTypes.h"
#include "..//Math/Math.h"

namespace PIXL{ namespace graphics{

	class Font final
	{
	public:
		Font(const string& filename, unsigned int fontSize);
	
		~Font(){}

		ftgl::texture_font_t* FtFont() const;
		const unsigned int GetID() const;
		const string& FileName() const;
		const int FontSize() const;
		const void SetFontSize(unsigned int fontSize);

	private:
		ftgl::texture_atlas_t* m_ftAtlas;
		ftgl::texture_font_t* m_ftFont;
		unsigned int m_fontSize;
		string m_fileName;
	};

} }