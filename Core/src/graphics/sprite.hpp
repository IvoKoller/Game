#pragma once

#include "renderable2d.hpp"

namespace evo { namespace graphics {

	class Sprite : public Renderable2D
	{
	private:
		int m_Columns;
		int m_Rows;
		int m_Index;
	public:
		Sprite(float x, float y, float width, float height, unsigned int color);
		Sprite(float x, float y, float width, float height, Texture* texture);
		Sprite(float x, float y, float width, float height, Texture* texture, float columns, float rows, float index);

		void UVindex(float index);
	private:
		void setUV();
	};

} }
