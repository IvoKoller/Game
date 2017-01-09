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
	Window window("EVO Game Engine - Editor", 1920, 1080);
	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	StaticLayer uilayer(&shader); // could all happen inside Editor
	Editor editor(window, shader, uilayer);
	shader.enable();
	shader.setUniform4f("filter", maths::vec4(1,1,1,1));
	//Camera camera;
	//========================================================

	// could all happen inside Editor

    //ui sprites separate texture
    Texture::add(new Texture("Spritesheet", "assets/textures/world.png", 5, 4*7));
    Texture::add(new Texture("UI-Spritesheet", "assets/textures/sprite.png", 32, 1));

	Tile::clear();

    Tile::add(new Tile("YFloor1", 4, 1, 1));
	Tile::add(new Tile("YFloor2", 5, 1, 1));
	Tile::add(new Tile("YFloor3", 6, 1, 1));
	Tile::add(new Tile("YFloor4", 7, 1, 1));
	Tile::add(new Tile("YGrass1", 10, 1, 1));
	Tile::add(new Tile("YGrass2", 11, 1, 1));
	Tile::add(new Tile("YBottom1", 0, 1, 1));
	Tile::add(new Tile("YBottom2", 1, 1, 1));
	Tile::add(new Tile("YBottom3", 2, 1, 1));
	Tile::add(new Tile("YBox1", 9, 1, 1));
	Tile::add(new Tile("YBox2", 14, 1, 1));
	Tile::add(new Tile("YTrans1", 8, 1, 1));
	Tile::add(new Tile("YBlank", 13, 1, 1));

	Tile::add(new Tile("WFloor1", 4+20, 1, 1));
	Tile::add(new Tile("WFloor2", 5+20, 1, 1));
	Tile::add(new Tile("WFloor3", 6+20, 1, 1));
	Tile::add(new Tile("WFloor4", 7+20, 1, 1));
	Tile::add(new Tile("WGrass1", 10+20, 1, 1));
	Tile::add(new Tile("WGrass2", 11+20, 1, 1));
	Tile::add(new Tile("WBottom1", 0+20, 1, 1));
	Tile::add(new Tile("WBottom2", 1+20, 1, 1));
	Tile::add(new Tile("WBottom3", 2+20, 1, 1));
	Tile::add(new Tile("WBox1", 9+20, 1, 1));
	Tile::add(new Tile("WBox2", 14+20, 1, 1));
	Tile::add(new Tile("WTrans1", 8+20, 1, 1));
	Tile::add(new Tile("WBlank", 13+20, 1, 1));

	Tile::add(new Tile("RFloor1", 4+40, 1, 1));
	Tile::add(new Tile("RFloor2", 5+40, 1, 1));
	Tile::add(new Tile("RFloor3", 6+40, 1, 1));
	Tile::add(new Tile("RFloor4", 7+40, 1, 1));
	Tile::add(new Tile("RGrass1", 10+40, 1, 1));
	Tile::add(new Tile("RGrass2", 11+40, 1, 1));
	Tile::add(new Tile("RBottom1", 0+40, 1, 1));
	Tile::add(new Tile("RBottom2", 1+40, 1, 1));
	Tile::add(new Tile("RBottom3", 2+40, 1, 1));
	Tile::add(new Tile("RBox1", 9+40, 1, 1));
	Tile::add(new Tile("RBox2", 14+40, 1, 1));
	Tile::add(new Tile("RTrans1", 8+40, 1, 1));
	Tile::add(new Tile("RBlank", 13+40, 1, 1));

	Tile::add(new Tile("MFloor1", 4+60, 1, 1));
	Tile::add(new Tile("MFloor2", 5+60, 1, 1));
	Tile::add(new Tile("MFloor3", 6+60, 1, 1));
	Tile::add(new Tile("MFloor4", 7+60, 1, 1));
	Tile::add(new Tile("MGrass1", 10+60, 1, 1));
	Tile::add(new Tile("MGrass2", 11+60, 1, 1));
	Tile::add(new Tile("MBottom1", 0+60, 1, 1));
	Tile::add(new Tile("MBottom2", 1+60, 1, 1));
	Tile::add(new Tile("MBottom3", 2+60, 1, 1));
	Tile::add(new Tile("MBox1", 9+60, 1, 1));
	Tile::add(new Tile("MBox2", 14+60, 1, 1));
	Tile::add(new Tile("MTrans1", 8+60, 1, 1));
	Tile::add(new Tile("MBlank", 13+60, 1, 1));

	Tile::add(new Tile("CFloor1", 4+80, 1, 1));
	Tile::add(new Tile("CFloor2", 5+80, 1, 1));
	Tile::add(new Tile("CFloor3", 6+80, 1, 1));
	Tile::add(new Tile("CFloor4", 7+80, 1, 1));
	Tile::add(new Tile("CGrass1", 10+80, 1, 1));
	Tile::add(new Tile("CGrass2", 11+80, 1, 1));
	Tile::add(new Tile("CBottom1", 0+80, 1, 1));
	Tile::add(new Tile("CBottom2", 1+80, 1, 1));
	Tile::add(new Tile("CBottom3", 2+80, 1, 1));
	Tile::add(new Tile("CBox1", 9+80, 1, 1));
	Tile::add(new Tile("CBox2", 14+80, 1, 1));
	Tile::add(new Tile("CTrans1", 8+80, 1, 1));
	Tile::add(new Tile("CBlank", 13+80, 1, 1));

	Tile::add(new Tile("GFloor1", 4+100, 1, 1));
	Tile::add(new Tile("GFloor2", 5+100, 1, 1));
	Tile::add(new Tile("GFloor3", 6+100, 1, 1));
	Tile::add(new Tile("GFloor4", 7+100, 1, 1));
	Tile::add(new Tile("GGrass1", 10+100, 1, 1));
	Tile::add(new Tile("GGrass2", 11+100, 1, 1));
	Tile::add(new Tile("GBottom1", 0+100, 1, 1));
	Tile::add(new Tile("GBottom2", 1+100, 1, 1));
	Tile::add(new Tile("GBottom3", 2+100, 1, 1));
	Tile::add(new Tile("GBox1", 9+100, 1, 1));
	Tile::add(new Tile("GBox2", 14+100, 1, 1));
	Tile::add(new Tile("GTrans1", 8+100, 1, 1));
	Tile::add(new Tile("GBlank", 13+100, 1, 1));

	Tile::add(new Tile("BFloor1", 4+120, 1, 1));
	Tile::add(new Tile("BFloor2", 5+120, 1, 1));
	Tile::add(new Tile("BFloor3", 6+120, 1, 1));
	Tile::add(new Tile("BFloor4", 7+120, 1, 1));
	Tile::add(new Tile("BGrass1", 10+120, 1, 1));
	Tile::add(new Tile("BGrass2", 11+120, 1, 1));
	Tile::add(new Tile("BBottom1", 0+120, 1, 1));
	Tile::add(new Tile("BBottom2", 1+120, 1, 1));
	Tile::add(new Tile("BBottom3", 2+120, 1, 1));
	Tile::add(new Tile("BBox1", 9+120, 1, 1));
	Tile::add(new Tile("BBox2", 14+120, 1, 1));
	Tile::add(new Tile("BTrans1", 8+120, 1, 1));
	Tile::add(new Tile("BBlank", 13+120, 1, 1));


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

    GLint texIDs[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; //TODO: Clean this up
    shader.enable();
    shader.setUniform1iv("textures", texIDs, 10);

    //=============== FONTS =================
    Font::add(new Font("Bpdots32", "assets/fonts/bpdots.otf", 32)); //For Editor
    //======================================

	Sprite background(-16,-9,32,18,0xffffffff);
	background.setColor(maths::vec4(67, 72, 84, 255));
	Sprite backgroundGrid(-1,-8.75,16,16,0xff000000);
	Sprite menubar(-16,7.5,32,1.5,0xffffffff);
	menubar.setColor(maths::vec4(71, 76, 92, 255));

	uilayer.add(background);
	uilayer.add(backgroundGrid);
	uilayer.add(menubar);

	MenuButton loadButton(-15.5, 7.75, 1.5, "Load");
	Textfield textfield(-13, 7.75, 5, 11);
	MenuButton saveButton(-7, 7.75, 1.5, "Save");
	MenuButton runButton(-4.5, 7.75, 1.5, "Run");
	CountButton mapsize(-2,7.75,Editor::updateWorldMap);

	//output field (build failed, build successfull etc.)

	Label colorChannels("Color channels", -7.2, 1.7f,"Bpdots32", 0xff000000);
	MenuButton red(-7, 0, 1.5, "Red");
	MenuButton green(-4, 0, 1.8, "Green");
	MenuButton blue(-7, -2, 1.5, "Blue");

	Label colliders("Colliders", -7.2, -3,"Bpdots32", 0xff000000);
	MenuButton colliderButton(-7,-5,3,"Default");
	//tile-like collider button
	//character button

	loadButton.setFunction(Editor::load);
	saveButton.setFunction(Editor::save);
	runButton.setFunction(Editor::run);
	colliderButton.setFunction(Editor::setColliderDefault);

	red.setToggleFunction(Editor::red);
	green.setToggleFunction(Editor::green);
	blue.setToggleFunction(Editor::blue);

	red.setToggleActive();
	green.setToggleActive();
	blue.setToggleActive();

	Textfield::StaticManager::add(&textfield);

	Label::add(&colorChannels);
	Label::add(&colliders);

	uilayer.add(textfield);
	uilayer.add(loadButton);
    uilayer.add(saveButton);
    uilayer.add(runButton);
	uilayer.add(red);
	uilayer.add(green);
	uilayer.add(blue);
	uilayer.add(colliderButton);
	uilayer.add(mapsize);

	uilayer.add(colorChannels);
	uilayer.add(colliders);

	Sprite* preview = new Sprite(-4,-8,2,2,Tile::get("Grid"));
	Editor::select(Tile::get("Grid")->getID());
	uilayer.add(*preview);

	float tilesize = 1;
	int x, y, c = 0;
    for(int i = 0; i < Tile::size(); i++){
		//Check if texture is correct
        if (Tile::getAtIndex(i)->texture == Texture::getAtIndex(0)){
			x = c%7; y = c/7; c++; //LOL
			TileButton* tilebutton = new TileButton(-15+x*tilesize,-8+y*tilesize,
			tilesize,tilesize,Tile::getAtIndex(i)->getID(),Tile::getAtIndex(i), Editor::select);
			//palette.add(tilebutton);
			uilayer.add(*tilebutton);
        }
    }

	bool sign = false;
	int sideMax = 16;
	x = y = 0;
	int index = 0;

	for(int i = 0; i < sideMax; i++){
		for(int n = 0; n < i*2+1; n++){
			if(n == 0) sign ? x++ : x--;
			else if(n < i+1) sign ? y-- : y++;
			else sign ? x-- : x++;
			TileButton* grid = new TileButton(7+x*tilesize, -0.75+y*tilesize,tilesize,
				tilesize, index, Tile::get("Grid"), Editor::addTile, true);
			grid->setSecondCallback(Editor::removeTile);
			uilayer.add(*grid);
			TileButton::StaticManager::add(grid);
			std::cout << grid << std::endl;
			index++;
		}
		sign = !sign;
	}

    Timer time;
    while(!window.closed()) {
        if(time.elapsed() > 0.05f){ //Lock frame rate
            window.clear();
			Editor::update();
			preview->setTile(Tile::get(Editor::getSelected()));
			uilayer.render();
            window.update();
            time.reset();
        }
    }

}

#endif /* end of include guard: EDITORMAIN_HPP */
