#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "window.hpp"
#include "shader.hpp"

#include "menuButton.hpp"
#include "tileButton.hpp"
#include "textfield.hpp"
#include "countButton.hpp"
#include "layers/layer.hpp"
#include "../utils/filepath.hpp"

namespace evo {
namespace graphics {

	class Editor {
		static Shader* m_Shader;
		static Window* m_Window;
		static Layer* m_UILayer;
		static std::string m_Filepath;

		static unsigned int m_Tiles[16*16];
		static bool m_ActiveColors[3];
		static unsigned int m_SelectedID;
		static unsigned int m_PlayerPosition; //index of playertile
	public:
		Editor(Window& window, Shader& shader, Layer& layer) {
			m_Shader = &shader;
			m_Window = &window;
			m_UILayer = &layer;
            for(int i = 0; i < 3; i++) m_ActiveColors[i] = 1;
		}
		~Editor() { }

		static void setFile(std::string string) { m_Filepath = string; }
		static void addTile(unsigned int index) { m_Tiles[index] = m_SelectedID; }
		static void removeTile(unsigned int index) { m_Tiles[index] = 0; }
		static void select(unsigned int textureID) { m_SelectedID = textureID; }
		static unsigned int getSelected() { return m_SelectedID; }

		static void save();
		static void load();
		static void run();

		static void setColliderDefault(); //adds a collider around setTiles
		static void updateWorldMap(int tilecount);

		static void red(bool activated) { m_ActiveColors[0] = activated; }
        static void green(bool activated) { m_ActiveColors[1] = activated; }
		static void blue(bool activated) { m_ActiveColors[2] = activated; }

		static void update();
	};

} }

#endif /* end of include guard: EDITOR_HPP */
