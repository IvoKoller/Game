#ifndef EDITORMAIN_HPP
#define EDITORMAIN_HPP

#include "src/graphics/window.hpp"
#include "src/graphics/shader.hpp"
#include "src/maths/maths.hpp"
#include "src/physics/collider.hpp"

#include "src/utils/timer.hpp"
#include "src/utils/filepath.hpp"
#include "src/utils/debug.hpp"

#include "src/graphics/buffers/buffer.hpp"
#include "src/graphics/buffers/indexbuffer.hpp"
#include "src/graphics/buffers/vertexarray.hpp"

#include "src/graphics/renderer2d.hpp"
#include "src/graphics/BatchRenderer2D.hpp"

#include "src/graphics/static_sprite.hpp"
#include "src/graphics/sprite.hpp"

#include "src/graphics/layers/staticlayer.hpp"
#include "src/graphics/layers/defaultlayer.hpp"

#include "src/graphics/layers/group.hpp"
#include "src/graphics/texture.hpp"
#include "src/graphics/label.hpp"
#include "src/graphics/tile.hpp"

#include "src/graphics/editor.hpp"

#include "src/graphics/camera.hpp"

#include "ext/gorilla-audio/ga.h"
#include "ext/gorilla-audio/gau.h"

#include "src/managers/sound_manager.hpp"
#include "src/managers/animation_manager.hpp"

void func(){ std::cout << "button clicked" << std::endl; }

unsigned int selectedID;
unsigned int IDarray[16*16] = { };

void funct(unsigned int textureID) { selectedID = textureID; }

void addInfo(unsigned int index) { IDarray[index] = selectedID; }
void removeInfo(unsigned int index) { IDarray[index] = NULL; }

int main(int argc, char *argv[]) {
	using namespace evo;
	using namespace graphics;
	using namespace audio;
	using namespace maths;
	using namespace physics;

	//=======SETS FILEPATH========
	std::string path(argv[0]);
	filepath pathToExec(path);
	Debug("deb/log/");
	//========DON'T DELETE=========

	//=================== INIT WINDOW ========================
	Window window("EVO Game Engine - Editor", 960, 540);
	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Editor editor(window, shader);
	shader.enable();
	shader.setUniform4f("filter", maths::vec4(1,1,1,1));
	//Camera camera;
	//========================================================

    StaticLayer uilayer(&shader);

    //ui sprites separate texture
    Texture::add(new Texture("Spritesheet", "assets/textures/sprite.png", 23, 1));
    Texture::add(new Texture("UI-Spritesheet", "assets/textures/sprite.png", 23, 1));

	Tile::clear();

    Tile::add(new Tile("FloorWhite", 0, 1, 1));
	Tile::add(new Tile("FloorRed", 1, 1, 1));
	Tile::add(new Tile("FloorGreen", 2, 1, 1));
	Tile::add(new Tile("FloorBlue", 3, 1, 1));
	Tile::add(new Tile("FloorYellow", 4, 1, 1));
	Tile::add(new Tile("FloorCyan", 5, 1, 1));
	Tile::add(new Tile("FloorMagenta", 6, 1, 1));

    Tile::add(new Tile("Grid", 7, 1, 1, Texture::getAtIndex(1)));
    Tile::add(new Tile("Hover", 8, 1, 1, Texture::getAtIndex(1)));
    Tile::add(new Tile("Selected", 9, 1, 1, Texture::getAtIndex(1)));
    Tile::add(new Tile("ButtonLeftNormal", 10, 1, 1, Texture::getAtIndex(1)));
    Tile::add(new Tile("ButtonLeftHover", 11, 1, 1, Texture::getAtIndex(1)));
    Tile::add(new Tile("ButtonLeftPressed", 12, 1, 1, Texture::getAtIndex(1)));
    Tile::add(new Tile("ButtonMiddleNormal", 13, 1, 1, Texture::getAtIndex(1)));
    Tile::add(new Tile("ButtonMiddleHover", 14, 1, 1, Texture::getAtIndex(1)));
    Tile::add(new Tile("ButtonMiddlePressed", 15, 1, 1, Texture::getAtIndex(1)));
    Tile::add(new Tile("ButtonRightNormal", 16, 1, 1, Texture::getAtIndex(1)));
    Tile::add(new Tile("ButtonRightHover", 17, 1, 1, Texture::getAtIndex(1)));
    Tile::add(new Tile("ButtonRightPressed", 18, 1, 1, Texture::getAtIndex(1)));
	Tile::add(new Tile("TextfieldLeft", 19, 1, 1, Texture::getAtIndex(1)));
	Tile::add(new Tile("TextfieldMiddle", 20, 1, 1, Texture::getAtIndex(1)));
	Tile::add(new Tile("TextfieldMiddleHover", 21, 1, 1, Texture::getAtIndex(1)));
	Tile::add(new Tile("TextfieldRight", 22, 1, 1, Texture::getAtIndex(1)));

    GLint texIDs[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; //TODO: Clean this up
    shader.enable();
    shader.setUniform1iv("textures", texIDs, 10);

    //=============== FONTS =================
    Font::add(new Font("Bpdots32", "assets/fonts/bpdots.otf", 32)); //TODO: font size dipendent on screen size
    Font::add(new Font("Bpdots20", "assets/fonts/bpdots.otf", 20)); //For Editor
    //======================================

	Sprite background(-16,-9,32,18,0xffffffff);
	background.setColor(maths::vec4(67, 72, 84, 1));
	Sprite backgroundGrid(-1,-8,16,16,0xff000000);

	uilayer.add(background);
	uilayer.add(backgroundGrid);

	MenuButton loadButton(-7, 6.5, 2, "Load");
	MenuButton saveButton(-4, 6.5, 2, "Save");
	Textfield textfield(-7, 4.5, 5, 11);
    MenuButton runButton(-7, 2.5, 2, "Run");
	//output field (build failed, build successfull etc.)

	//MenuButton ColliderOn()
	//MenuButton ColliderOff()
	MenuButton red(-7, 0, 2, "Red");
	MenuButton green(-4, 0, 2, "Green");
	MenuButton blue(-7, -2, 2, "Blue");

	loadButton.setFunction(func);
	saveButton.setFunction(func);
	runButton.setFunction(func);

	red.setToggleFunction(Editor::red);
	green.setToggleFunction(Editor::green);
	blue.setToggleFunction(Editor::blue);

	red.setToggleActive();
	green.setToggleActive();
	blue.setToggleActive();

	MenuButton::StaticManager::add(&loadButton);
	Textfield::StaticManager::add(&textfield);
    MenuButton::StaticManager::add(&saveButton);
    MenuButton::StaticManager::add(&runButton);
	MenuButton::StaticManager::add(&red);
	MenuButton::StaticManager::add(&green);
	MenuButton::StaticManager::add(&blue);

	uilayer.add(loadButton);
	uilayer.add(textfield);
    uilayer.add(saveButton);
    uilayer.add(runButton);
	uilayer.add(red);
	uilayer.add(green);
	uilayer.add(blue);

	Sprite* preview = new Sprite(-4,-8,2,2,Tile::get("Grid"));
	selectedID = Tile::get("Grid")->getID();
	uilayer.add(*preview);

	//Group palette(maths::mat4::translate(maths::vec3(-15, -8, 0)));
	int x, y, c = 0;
    for(int i = 0; i < Tile::size(); i++){
		//Check if texture is
        if (Tile::getAtIndex(i)->texture == Texture::getAtIndex(0)){
			x = c%4; y = c/4; c++; //LOL
			TileButton* tilebutton = new TileButton(-15+x,-8+y,1,1,Tile::getAtIndex(i)->getID(),Tile::getAtIndex(i), funct);
			TileButton::StaticManager::add(tilebutton);
			//palette.add(tilebutton);
			uilayer.add(*tilebutton);
        }
    }

	//Group worldGrid(maths::mat4::translate(maths::vec3(-8, -8, 0)));
	Group worldmap(maths::mat4::translate(maths::vec3(0, 0, 0)));

	for(int x = 0; x < 16; x++) {
		for(int y = 0; y < 16; y++) {
			TileButton* grid = new TileButton(-1+x,-8+y,1,1,x*16+y,"Grid", addInfo, true);
			TileButton::StaticManager::add(grid);
			grid->setSecondCallback(removeInfo);
			//IDarray[x*16+y] = Tile::get("Grid")->getID();
			uilayer.add(*grid);
		}
	}
	//uilayer.add(worldGrid);

    Timer time;
    while(!window.closed()) {
        if(time.elapsed() > 0.05f){ //Lock frame rate
            window.clear();
            MenuButton::checkstate(window);
            TileButton::checkstate(window);
			Textfield::update(window);
			Editor::update();
			preview->setTile(Tile::get(selectedID));

			for(int i = 0; i < TileButton::size(); i++){
				TileButton* button = TileButton::getAtIndex(i);
				if(button->isGridTile()){
					if(IDarray[button->getValue()] == 0) button->setTile(Tile::get("Grid"));
					else button->setTile(Tile::get(IDarray[button->getValue()]));
				}
			}

			uilayer.render();
            window.update();
            time.reset();
        }
    }

}


#endif /* end of include guard: EDITORMAIN_HPP */
