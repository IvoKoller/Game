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

#include "src/graphics/gui/editor.hpp"

#include "src/graphics/camera.hpp"

#include "ext/gorilla-audio/ga.h"
#include "ext/gorilla-audio/gau.h"

#include "src/managers/sound_manager.hpp"
#include "src/managers/animation_manager.hpp"

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
	Window window("EVO Game Engine - Editor", 1024,576);//1920, 1080);
	Shader* shader = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Camera camera;

	DefaultLayer layer0(shader, camera, 2.0/10);
	DefaultLayer layer1(shader, camera, 6.0/10);
	DefaultLayer layer2(shader, camera);
	DefaultLayer layer3(shader, camera, 14.0/10);
	DefaultLayer layer4(shader, camera, 18.0/10);
	StaticLayer uilayer(shader);

	// Editor editor(window, shader, uilayer);
	GLint texIDs[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; //TODO: Clean this up
	shader->enable();
	shader->setUniform1iv("textures", texIDs, 10);
	shader->setUniform4f("filter", maths::vec4(1,1,1,1));
	shader->disable();

    Texture::add(new Texture("Spritesheet", "assets/textures/sprite.png", 32, 1));
    Texture::add(new Texture("UI-Spritesheet", "assets/textures/sprite.png", 32, 1));

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

	Tile::add(new Tile("CountButtonNormal", 23, 1, 1, Texture::getAtIndex(1)));
	Tile::add(new Tile("CountButtonPlusHover", 24, 1, 1, Texture::getAtIndex(1)));
	Tile::add(new Tile("CountButtonPlusPressed", 25, 1, 1, Texture::getAtIndex(1)));
	Tile::add(new Tile("CountButtonMinusHover", 26, 1, 1, Texture::getAtIndex(1)));
	Tile::add(new Tile("CountButtonMinusPressed", 27, 1, 1, Texture::getAtIndex(1)));

	Tile::add(new Tile("Collider", 28, 1, 1, Texture::getAtIndex(1)));
	Tile::add(new Tile("Player", 29, 1, 1, Texture::getAtIndex(1)));
	Tile::add(new Tile("PlayerButton", 30, 1, 1, Texture::getAtIndex(1)));
	Tile::add(new Tile("PlayerButtonHover", 31, 1, 1, Texture::getAtIndex(1)));


    //=============== FONTS =================
    Font::add(new Font("Bpdots32", "assets/fonts/bpdots.otf", 48)); //For Editor
    //======================================

	Sprite* background = new Sprite(-16,-9,15,18,0xffffffff);
	background->setColor(maths::vec4(67, 72, 84, 255));
	uilayer.add(*background);

	uilayer.add(*new MenuButton(-15.5, 7.75, 1.5, "Load", Editor::load));
	uilayer.add(*new Textfield(-13, 7.75, 5, 11));
	uilayer.add(*new MenuButton(-7, 7.75, 1.5, "Save", Editor::save));
	uilayer.add(*new MenuButton(-4.5, 7.75, 1.5, "Run", Editor::run));

	uilayer.add(*new Label("WIDTH:", -15.5, 6.5, Font::get("Bpdots32"),0xff000000));
	uilayer.add(*new CountButton(-13, 6.25, Editor::setWidth, 16, 1, 32)); //width
	Editor::setWidth(16); //init value

	uilayer.add(*new Label("HEIGHT:", -9.75, 6.5, Font::get("Bpdots32"),0xff000000));
	uilayer.add(*new CountButton(-7, 6.25, Editor::setHeight, 9, 1, 32)); //height
	Editor::setHeight(9); //init value

	uilayer.add(*new Label("PARALLAX FACTOR:", -15.5, 5, Font::get("Bpdots32"),0xff000000));
	uilayer.add(*new CountButton(-10, 4.75, Editor::setParaFactor, 3, 1, 32)); //width
	Editor::setParaFactor(4);

	uilayer.add(*new Label("LAYER:", -6.75, 5, Font::get("Bpdots32"),0xff000000));
	uilayer.add(*new CountButton(-4.5, 4.75, Editor::setLayer, 2, 0, 4)); //layer
	uilayer.add(*new MenuButton(-4.5, 3.5, 2.75, "Parallax", Editor::setParallax));

	Sprite* preview = new Sprite(-4,-8,2,2,Tile::get("Grid"));
	Editor::select(Tile::get("Grid")->getID());
	uilayer.add(*preview);

	int x, y, c = 0;
    for(int i = 0; i < Tile::size(); i++){
		//Check if texture is correct
        if (Tile::getAtIndex(i)->texture == Texture::getAtIndex(0)){
			x = c%9; y = c/9; c++; //LOL
			uilayer.add(*new TileButton(-15+x,-8+y,
			1,1,Tile::getAtIndex(i)->getID(),Tile::getAtIndex(i), Editor::select));
        }
    }

    Timer time;
	bool ui = true;
    while(!window.closed()) {
        if(time.elapsed() > 0.01f){ //Lock frame rate
            window.clear();
			if(Editor::hasChanged()){
				int width = Editor::getWidth();
				int height = Editor::getHeight();
				int paraFactor = Editor::getParaFactor();
				if(width-2*paraFactor > 0) {
					Editor::resize(width, height);
					Editor::build(layer0, 0, width-2*paraFactor, height);
					Editor::build(layer1, 1, width-paraFactor, height);
					Editor::build(layer2, 2, width, height);
					Editor::build(layer3, 3, width+paraFactor, height);
					Editor::build(layer4, 4, width+2*paraFactor, height);
					Editor::setChanged(false);
				}
			}
			Editor::update();

			//controls
			//change color channel (1,2,3)

			//m_Shader->setUniform4f("filter",
	        //maths::vec4(m_ActiveColors[0],m_ActiveColors[1],m_ActiveColors[2],1));

			//change transparency (4)
			//change position (arrow keys)
			preview->setTile(Tile::get(Editor::getSelected()));

			if(window.isKeyPressed(GLFW_KEY_RIGHT)){
				camera.position.x += 0.1;
			}else if(window.isKeyPressed(GLFW_KEY_LEFT)){
				camera.position.x -= 0.1;
			}else if(window.isKeyPressed(GLFW_KEY_UP)){
				camera.position.y += 0.1;
			} else if(window.isKeyPressed(GLFW_KEY_DOWN)){
				camera.position.y -= 0.1;
			} else if(window.isKeyTyped(GLFW_KEY_1)){
				shader->setUniform4f("filter", maths::vec4(1,1,1,1));
			} else if(window.isKeyTyped(GLFW_KEY_2)){
				shader->setUniform4f("filter", maths::vec4(1,0,0,1));
			} else if(window.isKeyTyped(GLFW_KEY_3)){
				shader->setUniform4f("filter", maths::vec4(0,1,0,1));
			} else if(window.isKeyTyped(GLFW_KEY_4)){
				shader->setUniform4f("filter", maths::vec4(0,0,1,1));
			} else if(window.isKeyTyped(GLFW_KEY_ESCAPE)) ui = ui ? false : true;

			if(Editor::getParallax()){
				layer0.render();
				layer1.render();
				layer2.render();
				layer3.render();
				layer4.render();
			}else{
				switch(Editor::getLayer()) {
					case 0 : layer0.render();
							 break;
					case 1 : layer1.render();
							 break;
					case 2 : layer2.render();
							 break;
					case 3 : layer3.render();
							 break;
					case 4 : layer4.render();
							 break;
				}
			}

			if(ui) uilayer.render();
            window.update();
            time.reset();
        }
    }

	Tile::clear();
	Font::clear();
	Texture::clear();

}

#endif /* end of include guard: EDITORMAIN_HPP */
