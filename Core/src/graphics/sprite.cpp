#include "sprite.hpp"

#include "../managers/animation_manager.hpp"
#include "../managers/tile_manager.hpp"
#include "animation.hpp"
#include "tile.hpp"

namespace evo {
namespace graphics {

	Sprite::Sprite(float x, float y, float width, float height, unsigned int color)
		: Renderable2D(maths::vec3(x, y, 0), maths::vec2(width, height), color),
		  Element(ActiveAnimationManager::getID()) { }

	Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
		: Renderable2D(maths::vec3(x, y, 0), maths::vec2(width, height), 0xffffffff),
		  Element(ActiveAnimationManager::getID()) {
		m_Texture = texture;
	}

	Sprite::~Sprite() {

	}

	void Sprite::setUV(int index, int height, int width){
		float x = index % m_Rows;    float x1 = x + (float)width;
		float y = floor((float)index / m_Rows); float y1 = y + (float)height;

		y *= (1.0f / m_Columns);	y1 *= (1.0f / m_Columns);
		x *= (1.0f / m_Rows); 		x1 *= (1.0f / m_Rows);

		m_UV[0] = maths::vec2(x, y);
		m_UV[1] = maths::vec2(x, y1);
		m_UV[2] = maths::vec2(x1, y1);
		m_UV[3] = maths::vec2(x1, y);
	}

	void Sprite::setTile(const std::string name){
		stop(false);
		Tile* tile = TileManager::get(name);
		setUV(tile->index);
	}

	void Sprite::play(const std::string& name, const RepeatType& repeattype){
		Animation* animation = AnimationManager::get(name);
		if(animation == m_ActiveAnimation) return;
		if (animation != nullptr){
			m_RepeatType = repeattype;
			m_ActiveAnimation = animation;
			m_StartOfAnimation = std::chrono::high_resolution_clock::now();
			ActiveAnimationManager::add(this);
			return;
		}
		Debug::Log("Animation not found!", LogType::Error);
	}

	void Sprite::stop(bool setToFallback){
		if(m_ActiveAnimation != nullptr && m_ActiveAnimation->fallback >= 0 && setToFallback == true)
			setUV(m_ActiveAnimation->fallback);

		m_RepeatType = RepeatType::None;
		m_ActiveAnimation = nullptr;
		m_Ping = true;
		ActiveAnimationManager::remove(id);
	}

} }
