#include "Font.h"
#include "..//Debugging/Debug.h"

namespace PIXL{ namespace graphics{

	Font::Font(const string& filename, unsigned int fontSize)
		: m_fileName(filename), m_fontSize(fontSize)
	{
		m_ftAtlas = ftgl::texture_atlas_new(512, 512, 2);
		m_ftFont = ftgl::texture_font_new_from_file(m_ftAtlas, (float)fontSize, filename.c_str());

		if (m_ftFont == nullptr)
		{
			string errorString = "Failed to load font: ";
			errorString.append(filename);
			debugging::Debug::LogError(nullptr, errorString.c_str());
		}

	}

	

	ftgl::texture_font_t* Font::FtFont() const
	{
		return m_ftFont;
	}

	const unsigned int Font::GetID() const
	{
		return m_ftAtlas->id;
	}

	const string& Font::FileName() const
	{
		return m_fileName;
	}

	const int Font::FontSize() const
	{
		return m_fontSize;
	}

	const void Font::SetFontSize(unsigned int fontSize)
	{
		m_ftFont = ftgl::texture_font_new_from_file(m_ftAtlas, (float)fontSize, m_fileName.c_str());
		m_fontSize = fontSize;
	}

}
}