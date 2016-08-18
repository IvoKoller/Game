#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include <string>
#include <cmath>

#include "../utils/timer.hpp"
#include "renderable2d.hpp"
#include "animation.hpp"

namespace evo {
namespace graphics {

	struct Tile {
		std::string name;
		int index;
		bool repeat;

		Tile(std::string name, int index, bool repeat = false) : name(name), index(index), repeat(repeat) { }
	};

	enum RepeatType {none, loop, pingpong};

	class Sprite : public Renderable2D {
		static std::vector<Sprite*> m_ActiveAnimations;
		static std::vector<Animation*> m_Animations;
		static std::vector<Tile*> m_Tiles;
		static int m_IDCount;

		Animation* m_ActiveAnimation;
		Timer m_Timer;
		RepeatType m_RepeatType;
		bool m_Ping = true;
		int m_ID;
		int m_Columns;
		int m_Rows;

	public:
		Sprite(float x, float y, float width, float height, unsigned int color);
		Sprite(float x, float y, float width, float height, Texture* texture);
		Sprite(float x, float y, float width, float height, Texture* texture, int rows, int columns);

		~Sprite();

		static void addAnimation(const std::string& name, int start, int end, int fallback = -1); //NOTE: could also support multisprite animation
		static void addTile(const std::string& name, int index, int height = 1, int width = 1);

		void play(const std::string& name);
		void loop(const std::string& name);
		void pingpong(const std::string& name);
		void stop(bool setToFallback = true);
		void setTile(const std::string name);

		static void update();
	private:
		static void deleteActive(Sprite* sprite);
		Animation* getAnimation(const std::string& name);
		Tile* getTile(const std::string& name);
		void setUV(int index, int height = 1, int width = 1);
	public:
		static int delay;
	};

} }


#endif /* end of include guard: SPRITE_H */
