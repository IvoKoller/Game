#include "sprite.hpp"
#include "managers/animation_manager.hpp"

namespace evo {
namespace graphics {

	Sprite::Sprite(float x, float y, float width, float height, unsigned int color)
		: Renderable2D(maths::vec3(x, y, 0), maths::vec2(width, height), color) {
		//m_ID = m_IDCount++;
	}

	Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
		: Renderable2D(maths::vec3(x, y, 0), maths::vec2(width, height), 0xffffffff) {
		m_Texture = texture;
		//call to addsprite animation manager
	}

	Sprite::~Sprite() {
		//TODO: delete vectors
	}

	void Sprite::play(const std::string& name){
		Animation* animation = AnimationManager::get(name);
		if(animation == m_ActiveAnimation) return;
		if (animation != nullptr){
			m_RepeatType = RepeatType::none;
			m_ActiveAnimation = animation;
			m_ActiveAnimations.push_back(this);
			m_Timer.reset();
			return;
		}
		std::cout << "Animation not found!" << std::endl;
	}

	void Sprite::loop(const std::string& name){
		Animation* animation = getAnimation(name);
		if(animation == m_ActiveAnimation) return;
		if (animation != nullptr){
			m_RepeatType = RepeatType::loop;
			m_ActiveAnimation = animation;
			m_ActiveAnimations.push_back(this);
			m_Timer.reset();
			return;
		}
		std::cout << "Animation not found!" << std::endl;
	}

	void Sprite::pingpong(const std::string &name){
		Animation* animation = getAnimation(name);
		if(animation == m_ActiveAnimation) return;
		if (animation != nullptr){
			m_RepeatType = RepeatType::pingpong;
			m_ActiveAnimation = animation;
			m_ActiveAnimations.push_back(this);
			m_Timer.reset();
			return;
		}
		std::cout << "Animation not found!" << std::endl;
	}

	void Sprite::stop(bool setToFallback){
		if(m_ActiveAnimation != nullptr && m_ActiveAnimation->fallback >= 0 && setToFallback == true)
			setUV(m_ActiveAnimation->fallback);

		m_RepeatType = RepeatType::none;
		m_ActiveAnimation = nullptr;
		m_Ping = true;
		deleteActive(this);
	}

	void Sprite::setTile(const std::string name){
		stop(false);
		Tile* tile = getTile(name);
		setUV(tile->index);
	}

	void Sprite::update(){
		for (Sprite* sprite : m_ActiveAnimations) {
			Animation* animation = sprite->m_ActiveAnimation;
			if(sprite->m_Timer.elapsed() > 0.15f){ //0.091 = 30fps
				sprite->m_Timer.reset();
				sprite->setUV(animation->current);
				if(sprite->m_RepeatType == RepeatType::pingpong){
					if (animation->current == animation->end)
						sprite->m_Ping = false;

					if (animation->current == animation->start)
						sprite->m_Ping = true;

					sprite->m_Ping ? animation->current++ : animation->current--;
					break;
				}
				if (animation->current < animation->end){
					animation->current++;
					break;
				} else if (sprite->m_RepeatType == RepeatType::loop){
					animation->current = animation->start;
					break;
				} else sprite->stop();
			}
		}
	}

	void Sprite::deleteActive(Sprite* sprite){
		for(int i = 0; i < m_ActiveAnimations.size(); i++){
			if (m_ActiveAnimations[i]->m_ID == sprite->m_ID){
				m_ActiveAnimations.erase(m_ActiveAnimations.begin() + i);
			}
		}
	}

	Animation* Sprite::getAnimation(const std::string& name){
		for (Animation* animation : m_Animations) {
			if (animation->name == name)
				return animation;
		}
		return nullptr;
	}

	Tile* Sprite::getTile(const std::string& name){
		for (Tile* tile : m_Tiles) {
			if (tile->name == name)
				return tile;
		}
		return nullptr;
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
