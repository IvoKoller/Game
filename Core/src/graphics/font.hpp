#pragma once

#include <string>
#include "../../ext/freetype-gl/freetype-gl.h"
#include "../utils/filepath.hpp"

namespace evo {
namespace graphics {

	class Font {
	private:
		ftgl::texture_atlas_t* m_FTAtlas;
		ftgl::texture_font_t* m_FTFont;
		unsigned int m_Size;
		std::string m_Filename;
	public:
		Font(std::string filename, int size);

		ftgl::texture_font_t* getFTFont() const { return m_FTFont; }

		const unsigned int getID() const { return m_FTAtlas->id; }
		const std::string& getFileName() const { return m_Filename; }
		const int getSize() const { return m_Size; }
	};

} }
