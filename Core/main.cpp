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

#include "src/graphics/layers/tilelayer.hpp"

#include "src/graphics/layers/group.hpp"
#include "src/graphics/texture.hpp"
#include "src/graphics/label.hpp"

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
	//glClearColor(0.0f, 1.0f, 1.0f, 0.8f);

	//mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader& shader = *s;
	shader.enable();
	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));

	TileLayer layer(&shader);

	Texture* textures[] =
	{
		new Texture("textures/test.png"),
		new Texture("textures/tb.png"),
		new Texture("textures/tc.png")
	};


	for (float y = -9.0f; y < 9.0f; y++)
	{
		for (float x = -16.0f; x < 16.0f; x++)
		{
		//	layer.add(new Sprite(x, y, 0.9f, 0.9f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
			int r = rand() % 256;

			int col = 0xffff00 << 8 | r;
			if (rand() % 4 == 0)
				layer.add(new Sprite(x, y, 0.9f, 0.9f, col));
			else
				layer.add(new Sprite(x, y, 0.9f, 0.9f, textures[rand() % 3]));
		}
	}


	Group* g = new Group(maths::mat4::translation(maths::vec3(-15.8f, 7.0f, 0.0f)));
	Label* fps = new Label("TEXT", 0.4f, 0.4f, "SourceSansPro", 0xffffffff, 50);
	g->add(new Sprite(0, 0, 5, 1.5f, 0x505050DD));
	g->add(fps);

	layer.add(g);

	GLint texIDs[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	shader.enable();
	shader.setUniform1iv("textures", texIDs, 10);
	shader.setUniformMat4("pr_matrix", maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

	SoundManager::add(new Sound("Zelda", "sounds/zelda.ogg"));

	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	float t = 0.0f;

	float gain = 0.5f;
	SoundManager::get("Zelda")->setGain(gain);

	while (!window.closed())
	{
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light_pos", vec2((float)(x * 32.0f / window.getWidth() - 16.0f), (float)(9.0f - y * 18.0f / window.getHeight())));

		layer.render();

		const std::vector<Renderable2D*>& rs = layer.getRenderables();
		for (int i = 0; i < rs.size(); i++)
		{
			float c = sin(t) / 2 + 0.5f;
			rs[i]->setColor(maths::vec4(c, 0, 1, 1));
		}

		if (window.isKeyTyped(GLFW_KEY_P))
			SoundManager::get("Zelda")->play();

		if (window.isKeyTyped(GLFW_KEY_L))
			SoundManager::get("Zelda")->loop();

		if (window.isKeyTyped(GLFW_KEY_S))
			SoundManager::get("Zelda")->stop();

		if (window.isKeyTyped(GLFW_KEY_1))
			SoundManager::get("Zelda")->pause();

		if (window.isKeyTyped(GLFW_KEY_2))
			SoundManager::get("Zelda")->resume();

		if (window.isKeyTyped(GLFW_KEY_UP))
		{
			gain += 0.05f;
			SoundManager::get("Zelda")->setGain(gain);
		}

		if (window.isKeyTyped(GLFW_KEY_DOWN))
		{
			gain -= 0.05f;
			SoundManager::get("Zelda")->setGain(gain);
		}

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
