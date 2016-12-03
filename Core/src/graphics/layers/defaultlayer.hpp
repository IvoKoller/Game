#ifndef DEFAULTLAYER_HPP
#define DEFAULTLAYER_HPP

#include "layer.hpp"
#include "../BatchRenderer2D.hpp"
#include "../camera.hpp"

namespace evo {
namespace graphics {

	class DefaultLayer : public Layer {
		Camera& m_Camera;
		float m_Parallax;
	public:
		DefaultLayer(Shader* shader, Camera& camera, float parallax = 1.0f);
		~DefaultLayer();

		void render() override;
	};

}}

#endif /* end of include guard: DEFAULTLAYER_HPP */
