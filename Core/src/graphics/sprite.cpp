#include "sprite.hpp"
#include "managers/animation_manager.hpp"
#include "managers/tile_manager.hpp"

namespace evo {
namespace graphics {

	Sprite::Sprite(float x, float y, float width, float height, unsigned int color)
		: Renderable2D(maths::vec3(x, y, 0), maths::vec2(width, height), color) {
		m_ID = AnimationManager::createID();
	}

	Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
		: Renderable2D(maths::vec3(x, y, 0), maths::vec2(width, height), 0xffffffff) {
		m_Texture = texture;
		m_ID = AnimationManager::createID();
	}

	Sprite::~Sprite() {
		//TODO: delete vectors
	}

	void Sprite::play(const std::string& name, const RepeatType& repeattype){
		Animation* animation = AnimationManager::get(name);
		if(animation == m_ActiveAnimation) return;
		if (animation != nullptr){
			m_RepeatType = repeattype;
			m_ActiveAnimation = animation;
			m_StartOfAnimation = std::chrono::high_resolution_clock::now();
			AnimationManager::addActive(*this);
			return;
		}
		Debug::Log("Animation not found!", LogType::Error);
	}

	void Sprite::stop(bool setToFallback){
		if(m_ActiveAnimation != nullptr && m_ActiveAnimation->fallback >= 0 && setToFallback == true)
			setUV(m_ActiveAnimation->fallback);

		m_RepeatType = RepeatType::none;
		m_ActiveAnimation = nullptr;
		m_Ping = true;
		AnimationManager::removeActive(m_ID);
	}

	void Sprite::setTile(const std::string name){
		stop(false);
		Tile* tile = TileManager::get(name);
		setUV(tile->index);
	}

	void Sprite::setUV(int index, int height, int width){
		float x = index % m_Rows;    float x1 = x + (float)width;
		float y = floor((float)index / m_Rows); float y1 = y + (float)height;

		y *= (1.0f / m_Columns);	y1 *= (1.0f / m_Columns);
		x *= (1.0f / m_Rows); 		x1 *= (1.0f / m_Rows);

		//TODO: access by index?
		m_UV.clear();
		m_UV.push_back(maths::vec2(x, y));
		m_UV.push_back(maths::vec2(x, y1));
		m_UV.push_back(maths::vec2(x1, y1));
		m_UV.push_back(maths::vec2(x1, y));
	}
} }
