#include "collider.hpp"
#include "../graphics/window.hpp"

namespace evo {
namespace physics {

	Collider::Collider(const maths::vec3& position, float width, float height,
		maths::vec3 clrlvl, Layer layer, bool invert)
		: m_Min(position), m_Width(width), m_Height(height), m_ColorLevel(clrlvl),
		 m_Layer(layer), m_Inverted(invert) { }

	bool Collider::CollidesWith(const char* name) const {
		return CollidesWith(hash(name));
	}

	bool Collider::CollidesWith(const unsigned int& id) const {
		return CollidesWith(*get(id));
	}

	bool Collider::CollidesWithMouse(const maths::vec2& position) const {
		double mx, my; float fmx, fmy;
        graphics::Window::getMousePosition(mx, my);
        fmx = -16 + static_cast<float>(mx)/(graphics::Window::getWidth()/32);
        fmy = 9 - static_cast<float>(my)/(graphics::Window::getHeight()/18);
        maths::vec2 cursor = maths::vec2(fmx, fmy);
        maths::vec2 relativeMousePosition = cursor - position;
		return Contains(cursor, position);
	}
	bool Collider::CollidesWithMouse() const {
		double mx, my; float fmx, fmy;
        graphics::Window::getMousePosition(mx, my);
        fmx = -16 + static_cast<float>(mx)/(graphics::Window::getWidth()/32);
        fmy = 9 - static_cast<float>(my)/(graphics::Window::getHeight()/18);
        maths::vec2 cursor = maths::vec2(fmx, fmy);
        maths::vec2 relativeMousePosition = cursor - maths::vec2(m_Min);
		return Contains(cursor);
	}

	bool Collider::CollidesWith(const Collider& other) const {
		maths::vec2 max(m_Min.x + m_Width, m_Min.y + m_Height);
		maths::vec2 otherMax(other.m_Min.x + other.m_Width, other.m_Min.y + other.m_Height);
		bool result = (max >= maths::vec2(other.m_Min) && maths::vec2(m_Min) <= otherMax)
		|| (maths::vec2(m_Min) >= otherMax && max <= maths::vec2(other.m_Min));
		if(m_Inverted && other.m_Inverted == true) return true;
		if(m_Inverted || other.m_Inverted == true) return !result;
		return result;
	}

	bool Collider::Collides(maths::vec3 clrlvl, Layer layer) const {
		for(Manager* element : m_Vector) {
			Collider* collider = static_cast<Collider*>(element);
			if(collider != this && (layer == Layer::All || collider->m_Layer == layer)
			&& (collider->m_ColorLevel.x + clrlvl.x == 2 ||
				collider->m_ColorLevel.y + clrlvl.y == 2 ||
				collider->m_ColorLevel.z + clrlvl.z == 2))
				if(this->CollidesWith(*collider)) return true;
		}
	}

	bool Collider::CollidesTopWith(const Collider& other) const {
		maths::vec2 max(m_Min.x + m_Width, m_Min.y + m_Height);
		maths::vec2 otherMax(other.m_Min.x + other.m_Width, other.m_Min.y + other.m_Height);
		bool result = max.y >= other.m_Min.y && max.y < otherMax.y && max.x > other.m_Min.x && m_Min.x < otherMax.x;
		if(m_Inverted && other.m_Inverted == true) return true;
		if(m_Inverted || other.m_Inverted == true) return !result;
		return result;
	}

	bool Collider::CollidesBottomWith(const Collider& other) const {
		maths::vec2 max(m_Min.x + m_Width, m_Min.y + m_Height);
		maths::vec2 otherMax(other.m_Min.x + other.m_Width, other.m_Min.y + other.m_Height);
		bool result = m_Min.y <= otherMax.y && m_Min.y > other.m_Min.y && max.x > other.m_Min.x && m_Min.x < otherMax.x;
		if(m_Inverted && other.m_Inverted == true) return true;
		if(m_Inverted || other.m_Inverted == true) return !result;
		return result;
	}

	bool Collider::CollidesLeftWith(const Collider& other) const {
		maths::vec2 max(m_Min.x + m_Width, m_Min.y + m_Height);
		maths::vec2 otherMax(other.m_Min.x + other.m_Width, other.m_Min.y + other.m_Height);
		bool result = otherMax.x >= m_Min.x && m_Min.x > other.m_Min.x && max.y > other.m_Min.y && m_Min.y < otherMax.y;
		if(m_Inverted && other.m_Inverted == true) return true;
		if(m_Inverted || other.m_Inverted == true) return !result;
		return result;
	}

	bool Collider::CollidesRightWith(const Collider& other) const {
		maths::vec2 max(m_Min.x + m_Width, m_Min.y + m_Height);
		maths::vec2 otherMax(other.m_Min.x + other.m_Width, other.m_Min.y + other.m_Height);
		bool result = max.x >= other.m_Min.x && max.x < otherMax.x && max.y > other.m_Min.y && m_Min.y < otherMax.y;
		if(m_Inverted && other.m_Inverted == true) return true;
		if(m_Inverted || other.m_Inverted == true) return !result;
		return result;
	}

	bool Collider::CollidesTop(maths::vec3 clrlvl, Layer layer) const {
		for(Manager* element : m_Vector) {
			Collider* collider = static_cast<Collider*>(element);
			if(collider != this && (layer == Layer::All || collider->m_Layer == layer)
			&& (collider->m_ColorLevel.x + clrlvl.x == 2 ||
				collider->m_ColorLevel.y + clrlvl.y == 2 ||
				collider->m_ColorLevel.z + clrlvl.z == 2))
				if(this->CollidesTopWith(*collider)) return true;
		}
	}

	bool Collider::CollidesBottom(maths::vec3 clrlvl, Layer layer) const {
		for(Manager* element : m_Vector) {
			Collider* collider = static_cast<Collider*>(element);
			if(collider != this && (layer == Layer::All || collider->m_Layer == layer)
			&& (collider->m_ColorLevel.x + clrlvl.x == 2 ||
				collider->m_ColorLevel.y + clrlvl.y == 2 ||
				collider->m_ColorLevel.z + clrlvl.z == 2))
				if(this->CollidesBottomWith(*collider)) return true;
		}
	}

	bool Collider::CollidesLeft(maths::vec3 clrlvl, Layer layer) const {
		for(Manager* element : m_Vector) {
			Collider* collider = static_cast<Collider*>(element);
			if(collider != this && (layer == Layer::All || collider->m_Layer == layer)
			&& (collider->m_ColorLevel.x + clrlvl.x == 2 ||
				collider->m_ColorLevel.y + clrlvl.y == 2 ||
				collider->m_ColorLevel.z + clrlvl.z == 2))
				if(this->CollidesLeftWith(*collider)) return true;
		}
	}

	bool Collider::CollidesRight(maths::vec3 clrlvl, Layer layer) const {
		for(Manager* element : m_Vector) {
			Collider* collider = static_cast<Collider*>(element);
			if(collider != this && (layer == Layer::All || collider->m_Layer == layer)
			&& (collider->m_ColorLevel.x + clrlvl.x == 2 ||
				collider->m_ColorLevel.y + clrlvl.y == 2 ||
				collider->m_ColorLevel.z + clrlvl.z == 2))
				if(this->CollidesRightWith(*collider)) return true;
		}
	}

	bool Collider::Contains(const maths::vec2& point) const {
		maths::vec2 max(m_Min.x + m_Width, m_Min.y + m_Height);
		return point >= m_Min && point <= max;
	}

	bool Collider::Contains(const maths::vec2& point, const maths::vec2& min) const {
		maths::vec2 max(min.x + m_Width, min.y + m_Height);
		return point >= min && point <= max;
	}

	bool Collider::operator==(const Collider& other) const {
		maths::vec2 max(m_Min.x + m_Width, m_Min.y + m_Height);
		maths::vec2 otherMax(other.m_Min.x + other.m_Width, other.m_Min.y + other.m_Height);
		return m_Min == other.m_Min && max == otherMax;
	}

	bool Collider::operator!=(const Collider& other) const {
		return !(*this == other);
	}

	bool Collider::operator<(const Collider& other) const {
		return maths::vec2(m_Min.x + m_Width, m_Min.y + m_Height) < maths::vec2(other.m_Min);
	}

	bool Collider::operator>(const Collider& other) const {
		return maths::vec2(m_Min) > maths::vec2(other.m_Min.x + other.m_Width, other.m_Min.y + other.m_Height);
	}

} }
