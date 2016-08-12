#include "sprite.hpp"

namespace evo { namespace graphics {

	Sprite::Sprite(float x, float y, float width, float height, unsigned int color)
		: Renderable2D(maths::vec3(x, y, 0), maths::vec2(width, height), color)
	{

	}

	Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
		: Renderable2D(maths::vec3(x, y, 0), maths::vec2(width, height), 0xffffffff)
	{
		m_Texture = texture;
	}

	Sprite::Sprite(float x, float y, float width, float height, Texture* texture, float columns, float rows, float index)
		: Renderable2D(maths::vec3(x, y, 0), maths::vec2(width, height), 0xffffffff)
	{
		m_Texture = texture;
		m_Columns = columns;
		m_Rows = rows;
		m_Index = index;
		setUV();
	}

	void Sprite::UVindex(float index){
		m_Index = index;
		setUV();
	}

	void Sprite::setUV(){
		m_UV.clear();
		float x = m_Index % m_Columns;    float x1 = x + 1.0f;
		float y = (m_Index - (m_Index % m_Rows)) / m_Rows; float y1 = y + 1.0f;

		y *= (1.0f / m_Rows);	y1 *= (1.0f / m_Rows);
		x *= (1.0f / m_Columns); x1 *= (1.0f / m_Columns);

		m_UV.push_back(maths::vec2(x, y));
		m_UV.push_back(maths::vec2(x, y1));
		m_UV.push_back(maths::vec2(x1, y1));
		m_UV.push_back(maths::vec2(x1, y));
	}
} }
