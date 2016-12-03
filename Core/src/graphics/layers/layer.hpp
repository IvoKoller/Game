#ifndef LAYER_HPP
#define LAYER_HPP

#include "../renderer2d.hpp"
#include "../renderable2d.hpp"

namespace evo {
	namespace graphics {

		class Layer {
		protected:
			Renderer2D* m_Renderer;
			std::vector<Renderable2D*> m_Renderables;
			Shader* m_Shader;
			maths::mat4 m_ProjectionMatrix;
		protected:
			Layer(Renderer2D* renderer, Shader* shader, maths::mat4 projectionMatrix);
		public:
			virtual ~Layer();
			virtual void add(Renderable2D& renderable); //NOTE: Pass reference, not pointer to avoid nullptr exception
			virtual void remove(Renderable2D& renderable);
			virtual void clear();
			virtual void render();

			const std::vector<Renderable2D*>& getRenderables() const { return m_Renderables; }
		};

	} }

#endif /* end of include guard: LAYER_HPP */
