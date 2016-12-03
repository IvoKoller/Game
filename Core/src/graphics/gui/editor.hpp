#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "../window.hpp"
#include "../shader.hpp"

#include "menuButton.hpp"
#include "tileButton.hpp"
#include "gridButton.hpp"
#include "textfield.hpp"
#include "countButton.hpp"
#include "../layers/defaultlayer.hpp"
#include "../layers/staticlayer.hpp"
#include "../../utils/filepath.hpp"

namespace evo {
namespace graphics {

	class Editor {
		static std::string m_Filepath;

		static int m_Width;
		static int m_Height;
		static int m_Parafactor;
		static int m_ActiveLayer;
		static bool m_Parallax;
		static bool m_UI;
		static bool m_hasChanged;
		static Sprite* m_Preview;

		static std::vector< std::vector< std::vector<unsigned int> > > m_Tiles;
		static std::vector< std::vector<GridButton*> > m_Buttons;
		static unsigned int m_SelectedID;
	public:
		Editor() { }
		~Editor() { }

		static void update();

		static void resize(int width, int height);
		static void setFile(std::string string) { m_Filepath = string; }
		static void addTile(unsigned int index) {
			if(!m_Parallax)
				m_Tiles[m_ActiveLayer][index/m_Width][index%m_Width] = m_SelectedID; }
		static void removeTile(unsigned int index) {
			if(!m_Parallax)
				m_Tiles[m_ActiveLayer][index/m_Width][index%m_Width] = 0; }
		static void select(unsigned int textureID) { m_SelectedID = textureID; }
		static unsigned int getSelected() { return m_SelectedID; }

		static void save();
		static void load();
		static void run();

		static bool hasChanged() { return m_hasChanged; }
		static void setChanged(bool b) { m_hasChanged = b; }
		static void setWidth(int width) { m_Width = width; m_hasChanged = true; }
		static int getWidth() { return m_Width; }
		static void setHeight(int height) { m_Height = height; m_hasChanged = true; }
		static int getHeight() { return m_Height; }
		static void setParaFactor(int factor) { m_Parafactor = factor; m_hasChanged = true; }
		static int getParaFactor() { return m_Parafactor; }
		static void setParallax(bool b) { m_Parallax = b; }
		static bool getParallax() { return m_Parallax; }
		static void setLayer(int index) { m_ActiveLayer = index; }
		static int getLayer() { return m_ActiveLayer; }
		static void build(Layer& layer, int z, int width, int height);
	};

} }

#endif /* end of include guard: EDITOR_HPP */
