#include "font_manager.hpp"

namespace evo {
namespace graphics {

	void FontManager::init(){
		add(new Font("SourceSansPro", "assets/fonts/SourceSansPro-Light.ttf", 32));
	}

} }
