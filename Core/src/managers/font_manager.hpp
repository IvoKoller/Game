#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include "manager.hpp"
#include "../graphics/font.hpp"

namespace evo {
namespace graphics {

	class FontManager : public Manager<Font>  {
	public:
		static void init();
	};

} }

#endif /* end of include guard: FONT_MANAGER_H */
