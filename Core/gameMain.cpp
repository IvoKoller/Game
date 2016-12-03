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

	//==================== LOAD TEXTURES ===================
	Texture::add(new Texture("Spritesheet", "assets/textures/pokemon.png", 3, 4));
	Texture::add(new Texture("Sprite", "assets/textures/sprite.png", 32, 1));
	//Texture::add(new Texture("Background", "assets/textures/colorTest.png"));

	//Sprite background(-16, -9, 32, 18, Texture::get("Background"));
	//Sprite::add(&background);
	//backgroundLayer.add(background);

	//============== INIT TILES =================
	Tile::add(new Tile("right", 1));
	Tile::add(new Tile("up", 4));
	Tile::add(new Tile("left", 7));
	Tile::add(new Tile("down", 10));

	Tile::add(new Tile("FloorWhite",  0, 1, 1,	Texture::getAtIndex(1), vec3(1,1,1)));
	Tile::add(new Tile("FloorRed", 	  1, 1, 1, 	Texture::getAtIndex(1), vec3(1,0,0)));
	Tile::add(new Tile("FloorGreen",  2, 1, 1, 	Texture::getAtIndex(1), vec3(0,1,0)));
	Tile::add(new Tile("FloorBlue",   3, 1, 1, 	Texture::getAtIndex(1), vec3(0,0,1)));
	Tile::add(new Tile("FloorYellow", 4, 1, 1, 	Texture::getAtIndex(1), vec3(1,1,0)));
	Tile::add(new Tile("FloorCyan",   5, 1, 1, 	Texture::getAtIndex(1), vec3(0,1,1)));
	Tile::add(new Tile("FloorMagenta",6, 1, 1,  Texture::getAtIndex(1), vec3(1,0,1)));

	//===========================================

	//============== INIT ANIMATIONS =================
	Animation::add(new Animation("walkDown", 9, 11, 10));
	Animation::add(new Animation("walkLeft", 6, 8, 7));
	Animation::add(new Animation("walkUp", 3, 5, 4));
	Animation::add(new Animation("walkRight", 0, 2, 1));
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
	file.open(filepath::makeAbsolute("assets/scenes/red.lvl"));
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

	Sprite character(-8, 0, 2, 2, Texture::get("Spritesheet")); //NOTE: later probably also on heap
	Sprite::add(&character);
	character.addCollider(vec3(1,1,1), physics::Layer::Dynamic);
	worldlayer.add(character);
	character.setTile("down");
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
	Sound::add(new Sound("Pokemon", "assets/sounds/pallet-town.ogg"));
	//Sound::get("Pokemon")->loop();
	//=========================================

	while (!window.closed()) {
		window.clear();

		//=================== UI MENU ===================
		//save
		//settings

		//=========================================================

		//=================== MOVEMENT CONTROL ===================
		//TODO: DPAD_UP, DPAD_RIGHT, etc. - preset for different controllers
		//TODO: better joystick checking (no checking if disconnected etc.)

		vec3 pos = character.getPosition();

		if((window.isKeyPressed(GLFW_KEY_UP) || window.getJoystickAxis(7) == -1.0f)
		&& !character.collider->CollidesTop(currentColorLevel)){
			character.play("walkUp", RepeatType::Pingpong);
			if(character.isPlaying()) pos.y ++; //check if animation is on frame change
		}else if((window.isKeyPressed(GLFW_KEY_RIGHT) || window.getJoystickAxis(6) == 1.0f)
		&& !character.collider->CollidesRight(currentColorLevel)){
			character.play("walkRight", RepeatType::Pingpong);
			if(character.isPlaying()) pos.x ++;
		}else if((window.isKeyPressed(GLFW_KEY_DOWN) || window.getJoystickAxis(7) == 1.0f)
		&& !character.collider->CollidesBottom(currentColorLevel)){
			character.play("walkDown", RepeatType::Pingpong);
			if(character.isPlaying()) pos.y --;
		}else if ((window.isKeyPressed(GLFW_KEY_LEFT) || window.getJoystickAxis(6)== -1.0f)
		&& !character.collider->CollidesLeft(currentColorLevel)){
			character.play("walkLeft", RepeatType::Pingpong);
			if(character.isPlaying()) pos.x --;
		}else{ character.stop(); }

		//if(!character.collider->CollidesBottom(currentColorLevel)) pos.y = pos.y - 0.0001; //gravity

		character.setPosition(pos);
		//=========================================================

		//=================== COLOR CONTROL ===================
		if(window.isKeyPressed(GLFW_KEY_1) || window.isJoystickButtonPressed(3)){ //all colors
			shader.setUniform4f("filter", maths::vec4(1,1,1,1));
			currentColorLevel = masterColorLevel;

		}else if(window.isKeyPressed(GLFW_KEY_2) || window.isJoystickButtonPressed(1)){ //red
			shader.setUniform4f("filter", maths::vec4(1,0,0,1));
			currentColorLevel = maths::vec3(1,0,0);

		}else if(window.isKeyPressed(GLFW_KEY_3) || window.isJoystickButtonPressed(0)){ //green
			shader.setUniform4f("filter", maths::vec4(0,1,0,1));
			currentColorLevel = maths::vec3(0,1,0);

		}else if(window.isKeyPressed(GLFW_KEY_4) || window.isJoystickButtonPressed(2)) { //blue
			shader.setUniform4f("filter", maths::vec4(0,0,1,1));
			currentColorLevel = maths::vec3(0,0,1);

		}
		//=========================================================

		//====================== CHECKPOINT =======================

		//write to savefile

		//=========================================================

		//=================== RENDERING ===================
		AnimationManager::update();
		backgroundLayer.render();
		worldlayer.render();
		uilayer.render();
		window.update();

		frames++;
		if (time.elapsed() - timer > 1.0f) {
			timer += 1.0f;
			fps->text = std::to_string(frames) + " fps";
			//printf("%d fps\n", frames);
			frames = 0;
		}

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
