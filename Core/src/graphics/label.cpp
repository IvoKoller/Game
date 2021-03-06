#include "label.hpp"

namespace evo {
namespace graphics {

	Label::Label(std::string text, float x, float y, Font* font, unsigned int color)
		: Renderable2D(), text(text), position(m_Position), m_Font(font) {
		m_Position = maths::vec3(x, y, 0.0f);
		m_Color = color;
	}


	Label::Label(std::string text, float x, float y, const char* font, unsigned int color)
		: Renderable2D(), text(text), position(m_Position), m_Font(Font::get(font)) {
		m_Position = maths::vec3(x, y, 0.0f);
		m_Color = color;
	}

	void Label::submit(Renderer2D* renderer) const {
		renderer->drawString(text, position, *m_Font, m_Color);
	}

} }
