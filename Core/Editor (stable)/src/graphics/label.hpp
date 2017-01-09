#ifndef LABEL_HPP
#define LABEL_HPP

#include "renderable2d.hpp"
#include "../managers/staticManager.hpp"

namespace evo {
namespace graphics {

	class Label : public Renderable2D, public StaticManager<Label> {
	public:
		Font* m_Font;
		std::string text;
		maths::vec3& position;
		float x, y;
	public:
		Label(std::string text, float x, float y, Font* font, unsigned int color);
		Label(std::string text, float x, float y, const char* font, unsigned int color);

		void submit(Renderer2D* renderer) const override;
	};

} }

#endif /* end of include guard: LABEL_HPP */
