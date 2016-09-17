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
#include "src/graphics/batchrenderer2d.hpp"

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

int main(int argc, char *argv[]) {
	using namespace evo;
	using namespace graphics;
	using namespace audio;
	using namespace maths;
	using namespace physics;
	//=======SETS FILEPATH========
	std::string path(argv[0]);
	filepath pathToExec(path);
	Debug::Debug("log/");
	//========DON'T DELETE=========

	Window window("evo!", 960, 540);
	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();

	Camera camera;

	StaticLayer staticlayer(&shader);
	DefaultLayer defaultlayer(&shader, camera);

	Texture::add(new Texture("Spritesheet", "assets/textures/pokemon.png", 3, 4));
	Texture::add(new Texture("Background", "assets/textures/background.png"));

	Sprite background(0, 0, 75, 75, Texture::get("Background"));
	Sprite::add(&background);
	background.addCollider(physics::Layer::Static, true);
	defaultlayer.add(background);

	Sprite character(20, 20, 5, 5, Texture::get("Spritesheet")); //NOTE: later probably also on heap
	Sprite::add(&character);
	character.addCollider(physics::Layer::Dynamic);
	defaultlayer.add(character);

	camera.bindToTarget(character.getPosition());

	Tile::add(new Tile("right", 1));
	Tile::add(new Tile("up", 4));
	Tile::add(new Tile("left", 7));
	Tile::add(new Tile("down", 10));

	Animation::add(new Animation("walkDown", 9, 11, 10));
	Animation::add(new Animation("walkLeft", 6, 8, 7));
	Animation::add(new Animation("walkUp", 3, 5, 4));
	Animation::add(new Animation("walkRight", 0, 2, 1));

	character.setTile("down");

	Group* g = new Group(maths::mat4::translate(maths::vec3(-15.8f, 7.0f, 0.0f)));

	Label* fps = new Label("", 0.4f, 0.4f, "SourceSansPro", 0xffffffff);
	g->add(new Sprite(0, 0, 5, 1.5f, 0x505050DD));
	g->add(fps);
	staticlayer.add(*g);

	GLint texIDs[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; //TODO: Clean this up

	shader.enable();
	shader.setUniform1iv("textures", texIDs, 10);

	Sound::add(new Sound("Pokemon", "assets/sounds/pallet-town.ogg"));
	//Sound::get("Pokemon")->loop();

	Timer time;
	float timer = 0;
	unsigned int frames = 0;

	while (!window.closed()) {
		window.clear();

		//=================ps4 controller=============== TODO: later in window.cpp
		int buttonsCount;
		const unsigned char *buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonsCount);
		//==============================================

		vec3 pos = character.getPosition();

		if((window.isKeyPressed(GLFW_KEY_UP) || GLFW_PRESS == buttons[14]) && !character.collider->CollidesTop()){
			character.play("walkUp", RepeatType::Pingpong);
			if(character.isPlaying()) pos.y ++; //check if animation is on frame change
		}else if((window.isKeyPressed(GLFW_KEY_RIGHT) || GLFW_PRESS == buttons[15]) && !character.collider->CollidesRight()){
			character.play("walkRight", RepeatType::Pingpong);
			if(character.isPlaying()) pos.x ++;
		}else if((window.isKeyPressed(GLFW_KEY_DOWN) || GLFW_PRESS == buttons[16]) && !character.collider->CollidesBottom()){
			character.play("walkDown", RepeatType::Pingpong);
			if(character.isPlaying()) pos.y --;
		}else if ((window.isKeyPressed(GLFW_KEY_LEFT) || GLFW_PRESS == buttons[17]) && !character.collider->CollidesLeft()){
			character.play("walkLeft", RepeatType::Pingpong);
			if(character.isPlaying()) pos.x --;
		}else{ character.stop(); }

		character.setPosition(pos);

		AnimationManager::update();
		defaultlayer.render();
		staticlayer.render();
		window.update();

		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			fps->text = std::to_string(frames) + " fps";
			//printf("%d fps\n", frames);
			frames = 0;
		}

	}

	//TODO: put this in ~window
	Texture::clear();
	SoundManager::clear();
	Font::clear();
	Collider::clear();

	return 0;
}

#endif /* end of include guard: MAIN_CPP */
