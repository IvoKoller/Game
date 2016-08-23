#pragma once

#include "src/graphics/window.hpp"
#include "src/graphics/shader.hpp"
#include "src/maths/maths.hpp"

#include "src/utils/timer.hpp"
#include "src/utils/filepath.hpp"

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

#include "src/graphics/font_manager.hpp"

#include "ext/gorilla-audio/ga.h"
#include "ext/gorilla-audio/gau.h"

#include "src/audio/sound_manager.hpp"

int main(int argc, char *argv[])
{
	using namespace evo;
	using namespace graphics;
	using namespace audio;
	using namespace maths;

	//=======SETS FILEPATH========
	std::string path(argv[0]);
	filepath pathToExec(path);
	//========DON'T DELETE=========

	Window window("evo!", 960, 540);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();

	Camera camera;

	StaticLayer staticlayer(&shader);
	DefaultLayer defaultlayer(&shader, camera);

	Texture* textures[] = {
		new Texture("assets/textures/pokemon.png"),
		new Texture("assets/textures/background.png")
	};

	Sprite* background = new Sprite(0, 0, 75, 75, textures[1]);
	defaultlayer.add(background);

	Sprite character(0, 0, 5, 5, textures[0], 3, 4);
	staticlayer.add(character);

	float cameraX = 0;
	float cameraY = 0;

	character.addTile("right", 1);
	character.addTile("up", 4);
	character.addTile("left", 7);
	character.addTile("down", 10);

	character.addAnimation("walkDown", 9, 11, 10);
	character.addAnimation("walkLeft", 6, 8, 7);
	character.addAnimation("walkUp", 3, 5, 4);
	character.addAnimation("walkRight", 0, 2, 1);

	character.setTile("down");

	Group* g = new Group(maths::mat4::translate(maths::vec3(-15.8f, 7.0f, 0.0f)));

	Label* fps = new Label("", 0.4f, 0.4f, "SourceSansPro", 0xffffffff, 50);
	g->add(new Sprite(0, 0, 5, 1.5f, 0x505050DD));
	g->add(fps);
	staticlayer.add(g);

	GLint texIDs[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	shader.enable();
	shader.setUniform1iv("textures", texIDs, 10);

	SoundManager::add(new Sound("Pokemon", "assets/sounds/pallet-town.ogg"));
	SoundManager::get("Pokemon")->loop();

	Timer time;
	float timer = 0;
	unsigned int frames = 0;

	while (!window.closed())
	{
		window.clear();

		if (window.isKeyPressed(GLFW_KEY_LEFT)){
			character.play("walkLeft", RepeatType::Pingpong);
			cameraX -= 0.05f;
		}else if (window.isKeyPressed(GLFW_KEY_UP)){
			character.play("walkUp", RepeatType::Pingpong);
			cameraY += 0.05f;
		}else if (window.isKeyPressed(GLFW_KEY_RIGHT)){
			character.play("walkRight", RepeatType::Pingpong);
			cameraX += 0.05f;
		}else if (window.isKeyPressed(GLFW_KEY_DOWN)){
			character.play("walkDown", RepeatType::Pingpong);
			cameraY -= 0.05f;
		}else{
			character.stop();
		}

		camera.setPosition(cameraX, cameraY);

		Sprite::update();
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

	for (int i = 0; i < 3; i++) //TODO: textures::clean
		delete textures[i];

	FontManager::clean();

	return 0;
}
