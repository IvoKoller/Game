#pragma once

#include "renderable2d.hpp"
#include "font_manager.hpp"

namespace sparky { namespace graphics {

	class Label : public Renderable2D
	{
	public:
		Font* m_Font;
		std::string text;
		maths::vec3& position;
		float x, y;
	public:
		Label(std::string text, float x, float y, Font* font, unsigned int color);
		Label(std::string text, float x, float y, const std::string& font, unsigned int color, unsigned int size = -1);

		void submit(Renderer2D* renderer) const override;
		void validateFont(const std::string& name, int size);
	};

} }
