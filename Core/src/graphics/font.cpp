#include "font.hpp"

namespace sparky { namespace graphics {

	Font::Font(std::string name, std::string relativeFilepath, int size)
		: m_Name(name), m_Size(size)
	{
		m_FTAtlas = ftgl::texture_atlas_new(512, 512, 3);

		std::string filename = filepath::makeAbsolute(relativeFilepath);
		m_Filename = filename;

		m_FTFont = ftgl::texture_font_new_from_file(m_FTAtlas, m_Size, filename.c_str());
	}



} }
