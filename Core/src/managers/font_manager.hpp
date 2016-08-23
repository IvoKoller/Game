#pragma once

#include <vector>
#include "../font.hpp"
#include "../../utils/debug.hpp"

namespace evo {
namespace graphics {

	class FontManager : public Manager<Font>{
	public:
		static Font* get(const std::string& name, unsigned int size);
	private:
		FontManager();
	};

} }
