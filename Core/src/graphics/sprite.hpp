#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <vector>
#include <string>
#include <cmath>
#include <ctime>

#include "renderable2d.hpp"
#include "../utils/debug.hpp"
#include "texture.hpp"
#include "tile.hpp"
#include "animation.hpp"
#include "../managers/staticManager.hpp"
#include "../physics/collider.hpp"

namespace evo {
namespace graphics {

	enum RepeatType {None, Loop, Pingpong};

	class Sprite : public Renderable2D, public StaticManager<Sprite> {
        friend class AnimationManager;
		Animation* m_ActiveAnimation = nullptr;
		std::chrono::high_resolution_clock::time_point m_StartOfAnimation;
		RepeatType m_RepeatType = RepeatType::None;
		bool m_Ping = true;
		bool m_IsPlaying = false;
		int m_CurrentFrame; //could/should theoretically be unsigned

	public:
		const physics::Collider* collider = nullptr;

		Sprite(float x, float y, float width, float height, unsigned int color, bool StaticCollider = false);
		Sprite(float x, float y, float width, float height, Texture* texture, bool StaticCollider = false);
		~Sprite();

		void addCollider(physics::Layer layer = physics::Layer::Static, bool invert = false);
		void addCollider(physics::Layer layer, float width, float height, bool invert = false);


		std::chrono::high_resolution_clock::time_point getTimePoint() const { return m_StartOfAnimation; }
		void resetTimePoint() { m_StartOfAnimation = std::chrono::high_resolution_clock::now(); }
		void setTile(const char* name);
		void play(const char* name, const RepeatType& repeattype);
		void stop(bool setToFallback = true);
		bool isPlaying() { return m_IsPlaying; }

	private:
		void setUV(int index, int height = 1, int width = 1);
	};

} }


#endif /* end of include guard: SPRITE_HPP */
