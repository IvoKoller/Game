#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "window.hpp"
#include "shader.hpp"

#include "menuButton.hpp"
#include "tileButton.hpp"
#include "textfield.hpp"

namespace evo {
namespace graphics {

	class Editor {
		static Shader* m_Shader;
		static Window* m_Window;
        static bool m_ActiveColors[3];
		std::string m_Filepath;
	public:
		Editor(Window& window, Shader& shader) {
			m_Shader = &shader;
			m_Window = &window;
            for(int i = 0; i < 3; i++) m_ActiveColors[i] = 1;
		}
		~Editor() { }

		static void setFile() { }
		static void save() { }
		static void load() { }
		static void run() { }

		static void red(bool activated) { m_ActiveColors[0] = activated; }
        static void green(bool activated) { m_ActiveColors[1] = activated; }
		static void blue(bool activated) { m_ActiveColors[2] = activated; }
		static void update();
	};

} }

#endif /* end of include guard: EDITOR_HPP */
