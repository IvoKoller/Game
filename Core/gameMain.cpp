#ifndef MAIN_CPP
#define MAIN_CPP

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

#include "src/graphics/camera.hpp"

#include "ext/gorilla-audio/ga.h"
#include "ext/gorilla-audio/gau.h"

#include "src/managers/sound_manager.hpp"
#include "src/managers/animation_manager.hpp"

//===========DEFINES===========
#define DEBUG
//=============================
void func(){ std::cout << "button clicked" << std::endl; }

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
	Window window("GAME", 960, 540);
	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniform4f("filter", maths::vec4(1,1,1,1));
	Camera camera;
	//========================================================

	StaticLayer backgroundLayer(&shader);
	StaticLayer uilayer(&shader);
	DefaultLayer worldlayer(&shader, camera);
	DefaultLayer playerlayer(&shader, camera);

	//==================== LOAD TEXTURES ===================
	Texture::add(new Texture("Spritesheet", "assets/textures/character.png", 3, 16));
	Texture::add(new Texture("Sprite", "assets/textures/world.png", 5, 4*7));
	//Texture::add(new Texture("Background", "assets/textures/colorTest.png"));

	//Sprite background(-16, -9, 32, 18, Texture::get("Background"));
	//Sprite::add(&background);
	//backgroundLayer.add(background);

	//============== INIT TILES =================
	Tile::add(new Tile("RedRight", 1));
	Tile::add(new Tile("RedLeft", 7));
	Tile::add(new Tile("BlueRight", 1));
	Tile::add(new Tile("BlueLeft", 7));
	Tile::add(new Tile("GreenRight", 1));
	Tile::add(new Tile("GreenLeft", 7));
	Tile::add(new Tile("NoneRight", 1));
	Tile::add(new Tile("NoneLeft", 7));

	Tile::add(new Tile("YFloor1", 4, 1, 1, Texture::getAtIndex(1), vec3(1,1,0)));
	Tile::add(new Tile("YFloor2", 5, 1, 1, Texture::getAtIndex(1), vec3(1,1,0)));
	Tile::add(new Tile("YFloor3", 6, 1, 1, Texture::getAtIndex(1), vec3(1,1,0)));
	Tile::add(new Tile("YFloor4", 7, 1, 1, Texture::getAtIndex(1), vec3(1,1,0)));
	Tile::add(new Tile("YGrass1", 10, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("YGrass2", 11, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("YBottom1", 0, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("YBottom2", 1, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("YBottom3", 2, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("YBox1", 9, 1, 1, Texture::getAtIndex(1), vec3(1,1,0)));
	Tile::add(new Tile("YBox2", 14, 1, 1, Texture::getAtIndex(1), vec3(1,1,0)));
	Tile::add(new Tile("YTrans1", 8, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("YBlank", 13, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));

	Tile::add(new Tile("WFloor1", 4+20, 1, 1, Texture::getAtIndex(1), vec3(1,1,1)));
	Tile::add(new Tile("WFloor2", 5+20, 1, 1, Texture::getAtIndex(1), vec3(1,1,1)));
	Tile::add(new Tile("WFloor3", 6+20, 1, 1, Texture::getAtIndex(1), vec3(1,1,1)));
	Tile::add(new Tile("WFloor4", 7+20, 1, 1, Texture::getAtIndex(1), vec3(1,1,1)));
	Tile::add(new Tile("WGrass1", 10+20, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("WGrass2", 11+20, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("WBottom1", 0+20, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("WBottom2", 1+20, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("WBottom3", 2+20, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("WBox1", 9+20, 1, 1, Texture::getAtIndex(1), vec3(1,1,1)));
	Tile::add(new Tile("WBox2", 14+20, 1, 1, Texture::getAtIndex(1), vec3(1,1,1)));
	Tile::add(new Tile("WTrans1", 8+20, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("WBlank", 13+20, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));

	Tile::add(new Tile("RFloor1", 4+40, 1, 1, Texture::getAtIndex(1), vec3(1,0,0)));
	Tile::add(new Tile("RFloor2", 5+40, 1, 1, Texture::getAtIndex(1), vec3(1,0,0)));
	Tile::add(new Tile("RFloor3", 6+40, 1, 1, Texture::getAtIndex(1), vec3(1,0,0)));
	Tile::add(new Tile("RFloor4", 7+40, 1, 1, Texture::getAtIndex(1), vec3(1,0,0)));
	Tile::add(new Tile("RGrass1", 10+40, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("RGrass2", 11+40, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("RBottom1", 0+40, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("RBottom2", 1+40, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("RBottom3", 2+40, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("RBox1", 9+40, 1, 1, Texture::getAtIndex(1), vec3(1,0,0)));
	Tile::add(new Tile("RBox2", 14+40, 1, 1, Texture::getAtIndex(1), vec3(1,0,0)));
	Tile::add(new Tile("RTrans1", 8+40, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("RBlank", 13+40, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));

	Tile::add(new Tile("MFloor1", 4+60, 1, 1, Texture::getAtIndex(1), vec3(1,0,1)));
	Tile::add(new Tile("MFloor2", 5+60, 1, 1, Texture::getAtIndex(1), vec3(1,0,1)));
	Tile::add(new Tile("MFloor3", 6+60, 1, 1, Texture::getAtIndex(1), vec3(1,0,1)));
	Tile::add(new Tile("MFloor4", 7+60, 1, 1, Texture::getAtIndex(1), vec3(1,0,1)));
	Tile::add(new Tile("MGrass1", 10+60, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("MGrass2", 11+60, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("MBottom1", 0+60, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("MBottom2", 1+60, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("MBottom3", 2+60, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("MBox1", 9+60, 1, 1, Texture::getAtIndex(1), vec3(1,0,1)));
	Tile::add(new Tile("MBox2", 14+60, 1, 1, Texture::getAtIndex(1), vec3(1,0,1)));
	Tile::add(new Tile("MTrans1", 8+60, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("MBlank", 13+60, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));

	Tile::add(new Tile("CFloor1", 4+80, 1, 1, Texture::getAtIndex(1), vec3(0,1,1)));
	Tile::add(new Tile("CFloor2", 5+80, 1, 1, Texture::getAtIndex(1), vec3(0,1,1)));
	Tile::add(new Tile("CFloor3", 6+80, 1, 1, Texture::getAtIndex(1), vec3(0,1,1)));
	Tile::add(new Tile("CFloor4", 7+80, 1, 1, Texture::getAtIndex(1), vec3(0,1,1)));
	Tile::add(new Tile("CGrass1", 10+80, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("CGrass2", 11+80, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("CBottom1", 0+80, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("CBottom2", 1+80, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("CBottom3", 2+80, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("CBox1", 9+80, 1, 1, Texture::getAtIndex(1), vec3(0,1,1)));
	Tile::add(new Tile("CBox2", 14+80, 1, 1, Texture::getAtIndex(1), vec3(0,1,1)));
	Tile::add(new Tile("CTrans1", 8+80, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("CBlank", 13+80, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));

	Tile::add(new Tile("GFloor1", 4+100, 1, 1, Texture::getAtIndex(1), vec3(0,1,0)));
	Tile::add(new Tile("GFloor2", 5+100, 1, 1, Texture::getAtIndex(1), vec3(0,1,0)));
	Tile::add(new Tile("GFloor3", 6+100, 1, 1, Texture::getAtIndex(1), vec3(0,1,0)));
	Tile::add(new Tile("GFloor4", 7+100, 1, 1, Texture::getAtIndex(1), vec3(0,1,0)));
	Tile::add(new Tile("GGrass1", 10+100, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("GGrass2", 11+100, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("GBottom1", 0+100, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("GBottom2", 1+100, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("GBottom3", 2+100, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("GBox1", 9+100, 1, 1, Texture::getAtIndex(1), vec3(0,1,0)));
	Tile::add(new Tile("GBox2", 14+100, 1, 1, Texture::getAtIndex(1), vec3(0,1,0)));
	Tile::add(new Tile("GTrans1", 8+100, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("GBlank", 13+100, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));

	Tile::add(new Tile("BFloor1", 4+120, 1, 1, Texture::getAtIndex(1), vec3(0,0,1)));
	Tile::add(new Tile("BFloor2", 5+120, 1, 1, Texture::getAtIndex(1), vec3(0,0,1)));
	Tile::add(new Tile("BFloor3", 6+120, 1, 1, Texture::getAtIndex(1), vec3(0,0,1)));
	Tile::add(new Tile("BFloor4", 7+120, 1, 1, Texture::getAtIndex(1), vec3(0,0,1)));
	Tile::add(new Tile("BGrass1", 10+120, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("BGrass2", 11+120, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("BBottom1", 0+120, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("BBottom2", 1+120, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("BBottom3", 2+120, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("BBox1", 9+120, 1, 1, Texture::getAtIndex(1), vec3(0,0,1)));
	Tile::add(new Tile("BBox2", 14+120, 1, 1, Texture::getAtIndex(1), vec3(0,0,1)));
	Tile::add(new Tile("BTrans1", 8+120, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));
	Tile::add(new Tile("BBlank", 13+120, 1, 1, Texture::getAtIndex(1), vec3(0,0,0)));


	Tile::add(new Tile("FloorWhite",  0, 1, 1,	Texture::getAtIndex(1), vec3(1,1,1)));
	Tile::add(new Tile("FloorRed", 	  1, 1, 1, 	Texture::getAtIndex(1), vec3(1,0,0)));
	Tile::add(new Tile("FloorGreen",  2, 1, 1, 	Texture::getAtIndex(1), vec3(0,1,0)));
	Tile::add(new Tile("FloorBlue",   3, 1, 1, 	Texture::getAtIndex(1), vec3(0,0,1)));
	Tile::add(new Tile("FloorYellow", 4, 1, 1, 	Texture::getAtIndex(1), vec3(1,1,0)));
	Tile::add(new Tile("FloorCyan",   5, 1, 1, 	Texture::getAtIndex(1), vec3(0,1,1)));
	Tile::add(new Tile("FloorMagenta",6, 1, 1,  Texture::getAtIndex(1), vec3(1,0,1)));

	//===========================================

	//============== INIT ANIMATIONS =================
	Animation::add(new Animation("RedIdleRight", 21, 23, 22));
	Animation::add(new Animation("RedIdleLeft", 18, 20, 19));
	Animation::add(new Animation("RedWalkRight", 15, 17, 16));
	Animation::add(new Animation("RedWalkLeft", 12, 14, 13));

	Animation::add(new Animation("BlueIdleRight", 33, 35, 34));
	Animation::add(new Animation("BlueIdleLeft", 30, 32, 31));
	Animation::add(new Animation("BlueWalkRight", 27, 29, 28));
	Animation::add(new Animation("BlueWalkLeft", 24, 26, 25));

	Animation::add(new Animation("GreenIdleRight", 45, 47, 46));
	Animation::add(new Animation("GreenIdleLeft", 42, 44, 43));
	Animation::add(new Animation("GreenWalkRight", 39, 41, 40));
	Animation::add(new Animation("GreenWalkLeft", 36, 38, 37));

	Animation::add(new Animation("NoneIdleRight", 9, 11, 10));
	Animation::add(new Animation("NoneIdleLeft", 6, 8, 7));
	Animation::add(new Animation("NoneWalkRight", 3, 5, 4));
	Animation::add(new Animation("NoneWalkLeft", 0, 2, 1));

	//================================================

	GLint texIDs[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; //TODO: Clean this up
	shader.enable();
	shader.setUniform1iv("textures", texIDs, 10);

	//=============== FONTS =================
	Font::add(new Font("Bpdots32", "assets/fonts/bpdots.otf", 32)); //TODO: font size dipendent on screen size
	Font::add(new Font("Bpdots32", "assets/fonts/bpdots.otf", 15)); //For Editor
	//======================================

	//================= LOAD FROM FILE =====================

	//TODO: Init with tile


	//music different instruments

	//sprites visible dependent on current color
	//also hide collider

	//level class

	//bunch of check variables
	//example: position of character

	//if no save file exists ->

	//create savefile
	//else read from savefile

	//things in savefile:
	//gamestate
	//preferred language ?
	//options
	//graphics
	//preferred screenresolution
	//audio
	//exit
	//=======================================================

	//===================== LOAD LEVEL =======================

	std::vector<unsigned int> m_Tiles;

	std::ifstream file;
	file.open(filepath::makeAbsolute("assets/scenes/test2.lvl"));
	if(file.is_open()){
		for(int i = 0; i < 16*16; i++){
			unsigned int n;
			file >> n;
			m_Tiles.push_back(n);
		}
		file.close();
	} else { std::cout << "file not found!" << std::endl; }

	//loading and building could be a combined process in the future

	//========================================================


	//=============BUILD WORLD===================
	maths::vec3 currentColorLevel = {1,1,0};
	maths::vec3 masterColorLevel = {1,1,0};

	bool sign = false;
	int x = 0, y = 0, index = 0, tilesize = 5;
	for(int i = 0; i < 16; i++){
		for(int n = 0; n < i*2+1; n++){
			if(n == 0) sign ? x++ : x--;
			else if(n < i+1) sign ? y-- : y++;
			else sign ? x-- : x++;
			if(m_Tiles[index] != 0) {
				Tile* tile = Tile::get(m_Tiles[index]);
				Sprite* s = new Sprite(7+x*tilesize, y*tilesize,tilesize,tilesize,tile);
				Sprite::add(s);
				std::cout << "colorlevel of tile is " << tile->ColorLevel << std::endl;
				s->addCollider(tile->ColorLevel, physics::Layer::Static);
				worldlayer.add(*s);
			}
			index++;
		}
		sign = !sign;
	}


	//====================CREATE CHARACTER==========================

	Sprite character(-8, 0, 4, 4, Texture::get("Spritesheet")); //NOTE: later probably also on heap
	Sprite::add(&character);
	character.addCollider(vec3(1,1,1), physics::Layer::Dynamic);
	playerlayer.add(character);
	//character.setTile("down");
	camera.bindToTarget(character.getPosition(),character.getSize());

	//==================== UI ===========================
	Group* g = new Group(maths::mat4::translate(maths::vec3(-15.8f, 7.0f, 0.0f)));
	Label* fps = new Label("", 0.4f, 0.4f, "Bpdots32", 0xffffffff);
	g->add(new Sprite(0, 0, 5, 1.5f, 0x505050DD));
	g->add(fps);
	uilayer.add(*g);

	Timer time;
	float timer = 0;
	unsigned int frames = 0;

	//=========================================

	//================= AUDIO =================
	Sound::add(new Sound("piano", "assets/sounds/piano.wav"));
	Sound::add(new Sound("cello", "assets/sounds/cello.wav"));
	Sound::add(new Sound("violin", "assets/sounds/violin.wav"));

	Sound::get("piano")->loop();
	Sound::get("cello")->loop();
	Sound::get("violin")->loop();

	//=========================================
	character.play("RedIdleRight", RepeatType::Pingpong);
	Timer jump;
	bool right = true;
	bool jumping = false;
	bool jumpingPossible = true;
	float jumpHeight = 0;
	while (!window.closed()) {
	//if(time.elapsed() > 0.01f){ //Lock frame rate
		window.clear();

		//=================== UI MENU ===================
		//settings

		//=========================================================

		//=================== MOVEMENT CONTROL ===================
		//TODO: DPAD_UP, DPAD_RIGHT, etc. - preset for different controllers
		//TODO: better joystick checking (no checking if disconnected etc.)

		vec3 pos = character.getPosition();
		if((window.isKeyPressed(GLFW_KEY_UP) || window.getJoystickAxis(7) == -1.0f)
		&& !character.collider->CollidesTop(currentColorLevel) && !jumping && jumpingPossible){
			jumping = true;
		}else if((window.isKeyPressed(GLFW_KEY_RIGHT) || window.getJoystickAxis(6) == 1.0f)
		&& !character.collider->CollidesRight(currentColorLevel)){
			if(currentColorLevel == maths::vec3(1,0,0))
				character.play("RedWalkRight", RepeatType::Pingpong);
			if(currentColorLevel == maths::vec3(0,1,0))
				character.play("GreenWalkRight", RepeatType::Pingpong);
			if(currentColorLevel == maths::vec3(0,0,1))
				character.play("BlueWalkRight", RepeatType::Pingpong);
			right = true;
			if(character.isPlaying()) pos.x ++;
		}else if ((window.isKeyPressed(GLFW_KEY_LEFT) || window.getJoystickAxis(6)== -1.0f)
		&& !character.collider->CollidesLeft(currentColorLevel)){
			if(currentColorLevel == maths::vec3(1,0,0))
				character.play("RedWalkLeft", RepeatType::Pingpong);
			if(currentColorLevel == maths::vec3(0,1,0))
				character.play("GreenWalkLeft", RepeatType::Pingpong);
			if(currentColorLevel == maths::vec3(0,0,1))
				character.play("BlueWalkLeft", RepeatType::Pingpong);
			right = false;
			if(character.isPlaying()) pos.x --;
		}else{
			if(right){
				if(currentColorLevel == maths::vec3(1,0,0))
					character.play("RedIdleRight", RepeatType::Pingpong);
				if(currentColorLevel == maths::vec3(0,1,0))
					character.play("GreenIdleRight", RepeatType::Pingpong);
				if(currentColorLevel == maths::vec3(0,0,1))
					character.play("BlueIdleRight", RepeatType::Pingpong);
			}else{
				if(currentColorLevel == maths::vec3(1,0,0))
					character.play("RedIdleLeft", RepeatType::Pingpong);
				if(currentColorLevel == maths::vec3(0,1,0))
					character.play("GreenIdleLeft", RepeatType::Pingpong);
				if(currentColorLevel == maths::vec3(0,0,1))
					character.play("BlueIdleLeft", RepeatType::Pingpong);
			}
		}
		if(jump.elapsed() > 0.01f ){
			if(jumping){
				if(jumpHeight < 10){
					pos.y += 0.7f;
					jumpHeight += 0.7f;
				}
				else{
					jumping = false;
					jumpingPossible = false;
					jumpHeight = 0;
				}
			}
			if(character.collider->CollidesBottom(currentColorLevel)) jumpingPossible = true;
			if(!jumping && !character.collider->CollidesBottom(currentColorLevel)) pos.y = pos.y - 0.25f; //gravity
			jump.reset();
		}


		character.setPosition(pos);
		//=========================================================

		//=================== COLOR CONTROL ===================
		if(window.isKeyPressed(GLFW_KEY_1) || window.isJoystickButtonPressed(3)){ //all colors
			shader.setUniform4f("filter", maths::vec4(1,1,1,1));
			currentColorLevel = masterColorLevel;
			Sound::get("piano")->setGain(1);
			Sound::get("violin")->setGain(1);
			Sound::get("cello")->setGain(1);

		}else if(window.isKeyPressed(GLFW_KEY_2) || window.isJoystickButtonPressed(1)){ //red
			shader.setUniform4f("filter", maths::vec4(1,0,0,1));
			currentColorLevel = maths::vec3(1,0,0);
			Sound::get("piano")->setGain(0);
			Sound::get("violin")->setGain(0);
			Sound::get("cello")->setGain(1);

		}else if(window.isKeyPressed(GLFW_KEY_3) || window.isJoystickButtonPressed(0)){ //green
			shader.setUniform4f("filter", maths::vec4(0,1,0,1));
			currentColorLevel = maths::vec3(0,1,0);
			Sound::get("piano")->setGain(1);
			Sound::get("violin")->setGain(0);
			Sound::get("cello")->setGain(0);

		}else if(window.isKeyPressed(GLFW_KEY_4) || window.isJoystickButtonPressed(2)) { //blue
			shader.setUniform4f("filter", maths::vec4(0,0,1,1));
			currentColorLevel = maths::vec3(0,0,1);
			Sound::get("piano")->setGain(0);
			Sound::get("violin")->setGain(1);
			Sound::get("cello")->setGain(0);
		}
		//=========================================================

		//====================== CHECKPOINT =======================

		//write to savefile

		//=========================================================

		//=================== RENDERING ===================
		AnimationManager::update();
		backgroundLayer.render();
		worldlayer.render();
		shader.setUniform1f("grayscale", false);
		playerlayer.render();
		shader.setUniform1f("grayscale", true);
		uilayer.render();
		window.update();

		frames++;
		if (time.elapsed() - timer > 1.0f) {
			timer += 1.0f;
			fps->text = std::to_string(frames) + " fps";
			//printf("%d fps\n", frames);
			frames = 0;
		}
	//}
}

	//===============MEMORY CLEAN UP===================
	//TODO: put this in ~window
	Texture::clear();
	SoundManager::clear();
	Font::clear();
	Collider::clear();
	//=================================================

	return 0;
}

#endif /* end of include guard: MAIN_CPP */
