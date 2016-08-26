#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include "manager.hpp"

namespace evo {
	namespace graphics {

		class FontManager : public Manager<Font>{
			// dont call get() with size - change name accordingly instead: "SourceSansPro32"
		public:
			static void init(){
				add("SourceSansPro", new Font("assets/fonts/SourceSansPro-Light.ttf", 32));
			}
		private:
			FontManager();
		};

	} }

#endif /* end of include guard: FONT_MANAGER_H */
