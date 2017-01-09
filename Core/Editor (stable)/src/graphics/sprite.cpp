#include "sprite.hpp"

#include "../managers/animation_manager.hpp"

namespace evo {
namespace graphics {

	Sprite::Sprite(float x, float y, float width, float height, unsigned int color, bool StaticCollider)
		: Renderable2D(maths::vec3(x, y, 0), maths::vec2(width, height), color),
		StaticManager() { if(StaticCollider) addCollider(); }

	Sprite::Sprite(float x, float y, float width, float height, Texture* texture, bool StaticCollider)
		: Renderable2D(maths::vec3(x, y, 0), maths::vec2(width, height), 0xffffffff),
		StaticManager() { m_Texture = texture; if(StaticCollider) addCollider(); }

	Sprite::Sprite(float x, float y, float width, float height, const char* tile, bool StaticCollider)
		: Renderable2D(maths::vec3(x, y, 0), maths::vec2(width, height), 0xffffffff),
		StaticManager() { setTile(tile); if(StaticCollider) addCollider(); }

	Sprite::Sprite(float x, float y, float width, float height, Tile* tile, bool StaticCollider)
		: Renderable2D(maths::vec3(x, y, 0), maths::vec2(width, height), 0xffffffff),
		StaticManager() { setTile(tile); if(StaticCollider) addCollider(); }

	Sprite::~Sprite() { }

	void Sprite::addCollider(maths::vec3 clrlvl, physics::Layer layer, bool invert){
		Manager* col = new physics::Collider(m_Position, m_Size.x, m_Size.y, clrlvl, layer, invert);
		physics::Collider::add(col);
		collider = static_cast<physics::Collider*>(col);
	}

	void Sprite::addCollider(maths::vec3 clrlvl, physics::Layer layer, float width, float height, bool invert){
		Manager* col = new physics::Collider(m_Position, width, height, clrlvl, layer, invert);
		physics::Collider::add(col);
		collider = static_cast<physics::Collider*>(col);
	}

	void Sprite::setUV(int index, int height, int width){
		int rows = m_Texture->getRows();
		int columns = m_Texture->getColumns();

		float x = index % rows; float x1 = x + (float) width;
		float y = floor((float) index / rows); float y1 = y + (float) height;

		y *= (1.0f / columns);	y1 *= (1.0f / columns);
		x *= (1.0f / rows); 		x1 *= (1.0f / rows);

		m_UV[0] = maths::vec2(x, y);
		m_UV[1] = maths::vec2(x, y1);
		m_UV[2] = maths::vec2(x1, y1);
		m_UV[3] = maths::vec2(x1, y);
	}

	void Sprite::setTile(const char* name){
		stop(false);
		Tile* tile = Tile::get(name);
		m_Texture = tile->texture; //sets texture to tile texture
		setUV(tile->index);
	}

	void Sprite::setTile(Tile* tile){
		stop(false);
		m_Texture = tile->texture; //sets texture to tile texture
		setUV(tile->index);
	}

	void Sprite::play(const char* name, const RepeatType& repeattype){
		Animation* animation = Animation::get(name);
		m_Texture = animation->texture; //sets Texture to animation texture
		if(animation == m_ActiveAnimation) return; //already playing
		if (animation != nullptr){ //play for the first time
			m_RepeatType = repeattype;
			m_ActiveAnimation = animation;
			m_StartOfAnimation = std::chrono::high_resolution_clock::now();
			m_CurrentFrame = animation->startFrame; //prepares first frame
			AnimationManager::add(id);
			return;
		}
		Debug::Log("Animation not found!", LogType::Error);
	}

	void Sprite::stop(bool setToFallback){
		if(m_ActiveAnimation != nullptr && m_ActiveAnimation->fallbackFrame >= 0 && setToFallback == true)
			setUV(m_ActiveAnimation->fallbackFrame);

		m_RepeatType = RepeatType::None;
		m_ActiveAnimation = nullptr;
		m_Ping = true;
		AnimationManager::remove(id);
	}

} }
