#ifndef MAIN_CPP
#define MAIN_CPP

#include "src/graphics/window.hpp"
#include "src/graphics/shader.hpp"
#include "src/maths/maths.hpp"

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

#include "src/graphics/camera.hpp"

#include "ext/gorilla-audio/ga.h"
#include "ext/gorilla-audio/gau.h"

#include "src/managers/font_manager.hpp"
#include "src/managers/sound_manager.hpp"
#include "src/managers/tile_manager.hpp"
#include "src/managers/animation_manager.hpp"
#include "src/managers/texture_manager.hpp"

int main(int argc, char *argv[]) {
	using namespace evo;
	using namespace graphics;
	using namespace audio;
	using namespace maths;

	//=======SETS FILEPATH========
	std::string path(argv[0]);
	filepath pathToExec(path);
	Debug::Debug("log/");
	//========DON'T DELETE=========

	Window window("evo!", 960, 540);
	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();

	Debug::CheckError();

	Camera camera;

	StaticLayer staticlayer(&shader);
	DefaultLayer defaultlayer(&shader, camera);

	TextureManager::add("Spritesheet", new Texture("assets/textures/pokemon.png", 3, 4)); //NOTE: allocate on heap as it is a lot of data
	TextureManager::add("Background", new Texture("assets/textures/background.png"));

	Sprite character(0, 0, 5, 5, TextureManager::get("Spritesheet")); //NOTE: later probably also on heap
	staticlayer.add(character);

	Sprite background(0, 0, 75, 75, TextureManager::get("Background"));
	defaultlayer.add(background);

	TileManager::add("right", new Tile(1));
	TileManager::add("up", new Tile(4));
	TileManager::add("left", new Tile(7));
	TileManager::add("down", new Tile(10));

	AnimationManager::add("walkDown", new Animation(9, 11, 10));
	AnimationManager::add("walkLeft", new Animation(6, 8, 7));
	AnimationManager::add("walkUp", new Animation(3, 5, 4));
	AnimationManager::add("walkRight", new Animation(0, 2, 1));

	character.setTile("down");

	Group* g = new Group(maths::mat4::translate(maths::vec3(-15.8f, 7.0f, 0.0f)));

	Label* fps = new Label("", 0.4f, 0.4f, "SourceSansPro", 0xffffffff);
	g->add(new Sprite(0, 0, 5, 1.5f, 0x505050DD));
	g->add(fps);
	staticlayer.add(*g);

	GLint texIDs[] = //TODO: Clean this up
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	shader.enable();
	shader.setUniform1iv("textures", texIDs, 10);

	SoundManager::add("Pokemon", new Sound("assets/sounds/pallet-town.ogg"));
	SoundManager::get("Pokemon")->loop();

	Timer time;
	float timer = 0;
	unsigned int frames = 0;

	Debug::CheckError();
	while (!window.closed())
	{
		window.clear();

		if (window.isKeyPressed(GLFW_KEY_LEFT)){
			character.play("walkLeft", RepeatType::Pingpong);
			camera.position.x -= 0.05f;
		}else if (window.isKeyPressed(GLFW_KEY_UP)){
			character.play("walkUp", RepeatType::Pingpong);
			camera.position.y += 0.05f;
		}else if (window.isKeyPressed(GLFW_KEY_RIGHT)){
			character.play("walkRight", RepeatType::Pingpong);
			camera.position.x += 0.05f;
		}else if (window.isKeyPressed(GLFW_KEY_DOWN)){
			character.play("walkDown", RepeatType::Pingpong);
			camera.position.y -= 0.05f;
		}else{
			character.stop();
		}

		AnimationManager::update();
		Debug::CheckError();
		defaultlayer.render();
		staticlayer.render();
		window.update();

		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			fps->text = std::to_string(frames) + " fps";
			printf("%d fps\n", frames);
			frames = 0;
		}

	}

	//TODO: put this in ~window
	TextureManager::clean();
	SoundManager::clean();
	FontManager::clean();

	return 0;
}

#endif /* end of include guard: MAIN_CPP */
