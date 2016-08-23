#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include "../utils/debug.hpp"

#include "renderable2d.hpp"

#include "animation.hpp"
#include "tile.hpp"

namespace evo {
namespace graphics {

	enum RepeatType {None, Loop, Pingpong};

	class Sprite : public Renderable2D {
		friend class AnimationManager;

		Animation* m_ActiveAnimation; //needs to be pointer as it can/will hold nullptr
		std::chrono::high_resolution_clock::time_point m_StartOfAnimation;
		RepeatType m_RepeatType;
		bool m_Ping = true;
		int m_CurrentFrame, m_Columns, m_Rows; //could/should theoretically be unsigned
		unsigned int m_ID;

	public:
		Sprite(float x, float y, float width, float height, unsigned int color);
		Sprite(float x, float y, float width, float height, Texture* texture);

		~Sprite();

		std::chrono::high_resolution_clock::time_point getTimePoint() const {
			return m_StartOfAnimation; }
		void resetTimePoint() {
			m_StartOfAnimation = std::chrono::high_resolution_clock::now(); }
		void setUV(int index, int height = 1, int width = 1);
		void setTile(const std::string name);

		void play(const std::string& name, const RepeatType& repeattype);
		void stop(bool setToFallback = true);
	};

} }


#endif /* end of include guard: SPRITE_H */
