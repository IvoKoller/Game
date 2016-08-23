#include "font_manager.hpp"

namespace evo { namespace graphics {

	//TODO: has to be re-done
	Font* FontManager::get(const std::string& name, unsigned int size ){ //unsigned int size = 32
		for (Font* font : m_Fonts) {
			if (font->getSize() == size && font->getName() == name)
				return font;
		}
		// TODO: Maybe return a default font instead?
		Debug::Log("Font not found!", LogType::Error);
		return nullptr;
	}

} }
