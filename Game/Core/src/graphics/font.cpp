#include "font.hpp"

namespace evo {
namespace graphics {

	Font::Font(const char* name, std::string relativeFilepath, int size)
		: StaticManager(name), m_Size(size) {

		m_FTAtlas = ftgl::texture_atlas_new(512, 512, 1);
		std::string filename = filepath::makeAbsolute(relativeFilepath);
		m_Filename = filename;
		m_FTFont = ftgl::texture_font_new_from_file(m_FTAtlas, m_Size, filename.c_str());
	}

	void Font::init(){
		Font::add(new Font("SourceSansPro", "assets/fonts/SourceSansPro-Light.ttf", 32));
	}


} }
