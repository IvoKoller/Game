#include "collider.hpp"

namespace evo {
namespace physics {

	Collider::Collider(const maths::vec3& position, float width, float height,
		Layer layer, bool invert)
		: m_Min(position), m_Width(width), m_Height(height), m_Layer(layer), m_Inverted(invert) { }

	bool Collider::CollidesWith(const char* name) const {
		return CollidesWith(hash(name));
	}

	bool Collider::CollidesWith(const unsigned int& id) const {
		return CollidesWith(*get(id));
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

	bool Collider::Collides(Layer layer) const {
		for(Manager* element : m_Vector) {
			Collider* collider = static_cast<Collider*>(element);
			if(collider->m_Layer == layer || layer == Layer::All)
				if(this->CollidesWith(*collider)) return true;
		}
	}

	bool Collider::CollidesTopWith(const Collider& other) const {
		maths::vec2 max(m_Min.x + m_Width, m_Min.y + m_Height);
		maths::vec2 otherMax(other.m_Min.x + other.m_Width, other.m_Min.y + other.m_Height);
		bool result = max.y >= other.m_Min.y && max.y < otherMax.y && max.x >= other.m_Min.x && m_Min.x <= otherMax.x;
		if(m_Inverted && other.m_Inverted == true) return true;
		if(m_Inverted || other.m_Inverted == true) return !result;
		return result;
	}

	bool Collider::CollidesBottomWith(const Collider& other) const {
		maths::vec2 max(m_Min.x + m_Width, m_Min.y + m_Height);
		maths::vec2 otherMax(other.m_Min.x + other.m_Width, other.m_Min.y + other.m_Height);
		bool result = m_Min.y <= otherMax.y && m_Min.y > other.m_Min.y && max.x >= other.m_Min.x && m_Min.x <= otherMax.x;
		if(m_Inverted && other.m_Inverted == true) return true;
		if(m_Inverted || other.m_Inverted == true) return !result;
		return result;
	}

	bool Collider::CollidesLeftWith(const Collider& other) const {
		maths::vec2 max(m_Min.x + m_Width, m_Min.y + m_Height);
		maths::vec2 otherMax(other.m_Min.x + other.m_Width, other.m_Min.y + other.m_Height);
		bool result = otherMax.x >= m_Min.x && m_Min.x > other.m_Min.x && max.y >= other.m_Min.y && m_Min.y <= otherMax.y;
		if(m_Inverted && other.m_Inverted == true) return true;
		if(m_Inverted || other.m_Inverted == true) return !result;
		return result;
	}

	bool Collider::CollidesRightWith(const Collider& other) const {
		maths::vec2 max(m_Min.x + m_Width, m_Min.y + m_Height);
		maths::vec2 otherMax(other.m_Min.x + other.m_Width, other.m_Min.y + other.m_Height);
		bool result = max.x >= other.m_Min.x && max.x < otherMax.x && max.y >= other.m_Min.y && m_Min.y <= otherMax.y;
		if(m_Inverted && other.m_Inverted == true) return true;
		if(m_Inverted || other.m_Inverted == true) return !result;
		return result;
	}

	bool Collider::CollidesTop(Layer layer) const {
		for(Manager* element : m_Vector) {
			Collider* collider = static_cast<Collider*>(element);
			if(collider != this && (layer == Layer::All || collider->m_Layer == layer))
			if(this->CollidesTopWith(*collider)) return true;
		}
	}

	bool Collider::CollidesBottom(Layer layer) const {
		for(Manager* element : m_Vector) {
			Collider* collider = static_cast<Collider*>(element);
			if(collider != this && (layer == Layer::All || collider->m_Layer == layer))
				if(this->CollidesBottomWith(*collider)) return true;
		}
	}

	bool Collider::CollidesLeft(Layer layer) const {
		for(Manager* element : m_Vector) {
			Collider* collider = static_cast<Collider*>(element);
			if(collider != this && (layer == Layer::All || collider->m_Layer == layer))
				if(this->CollidesLeftWith(*collider)) return true;
		}
	}

	bool Collider::CollidesRight(Layer layer) const {
		for(Manager* element : m_Vector) {
			Collider* collider = static_cast<Collider*>(element);
			if(collider != this && (layer == Layer::All || collider->m_Layer == layer))
				if(this->CollidesRightWith(*collider)) return true;
		}
	}

	bool Collider::Contains(const maths::vec2& point) const {
		maths::vec2 max(m_Min.x + m_Width, m_Min.y + m_Height);
		return point >= m_Min && point <= max;
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
