#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <vector>
#include <string>
#include <cmath>
#include <ctime>

#include "renderable2d.hpp"
#include "../utils/debug.hpp"
#include "../managers/element.hpp"

namespace evo {
namespace graphics {

    class Animation;
    class Tile;

	enum RepeatType {None, Loop, Pingpong};

	class Sprite : public Renderable2D, public Element {
        friend class ActiveAnimationManager;
		Animation* m_ActiveAnimation = nullptr; //needs to be pointer as it can/will hold nullptr
		std::chrono::high_resolution_clock::time_point m_StartOfAnimation;
		RepeatType m_RepeatType = RepeatType::None;
		bool m_Ping = true;
		int m_CurrentFrame, m_Columns, m_Rows; //could/should theoretically be unsigned

	public:
		Sprite(float x, float y, float width, float height, unsigned int color);
		Sprite(float x, float y, float width, float height, Texture* texture);

		~Sprite();

		std::chrono::high_resolution_clock::time_point getTimePoint() const { return m_StartOfAnimation; }
		void resetTimePoint() { m_StartOfAnimation = std::chrono::high_resolution_clock::now(); }
		void setUV(int index, int height = 1, int width = 1);
		void setTile(const std::string name);

		void play(const std::string& name, const RepeatType& repeattype);
		void stop(bool setToFallback = true);
	};

} }


#endif /* end of include guard: SPRITE_HPP */
