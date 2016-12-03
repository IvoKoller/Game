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
	Shader* shader = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader->enable();
	shader->setUniform4f("filter", maths::vec4(1,1,1,1));
	//========================================================

	StaticLayer backgroundLayer(shader);

	//==================== LOAD TEXTURES ===================
	Texture::add(new Texture("Spritesheet", "assets/textures/pokemon.png", 3, 4));
	Texture::add(new Texture("Sprite", "assets/textures/sprite.png", 32, 1));
	Texture::add(new Texture("Background", "assets/textures/colorTest.png"));

	Sprite background(-16, -9, 32, 18, 0xffffffff);

	//Sprite::add(&background);
	backgroundLayer.add(background);

	GLint texIDs[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; //TODO: Clean this up
	shader->enable();
	shader->setUniform1iv("textures", texIDs, 10);

	while (!window.closed()) {
		window.clear();

		backgroundLayer.render();
		window.update();

	}

	return 0;
}

#endif /* end of include guard: MAIN_CPP */
