#include "font_manager.hpp"

namespace evo {
namespace graphics {

	void FontManager::init(){
		add("SourceSansPro", new Font("assets/fonts/SourceSansPro-Light.ttf", 32));
	}

} }
