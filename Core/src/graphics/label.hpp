#pragma once

#include "renderable2d.hpp"
#include "../managers/font_manager.hpp"

namespace evo {
namespace graphics {

	class Label : public Renderable2D {
	public:
		Font* m_Font;
		std::string text;
		maths::vec3& position;
		float x, y;
	public:
		Label(std::string text, float x, float y, Font* font, unsigned int color);
		Label(std::string text, float x, float y, const std::string& font, unsigned int color);

		void submit(Renderer2D* renderer) const override;
	};

} }
