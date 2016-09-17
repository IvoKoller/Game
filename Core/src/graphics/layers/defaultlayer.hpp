#ifndef DEFAULTLAYER_HPP
#define DEFAULTLAYER_HPP

#include "layer.hpp"
#include "../BatchRenderer2D.hpp"
#include "../camera.hpp"

namespace evo {
namespace graphics {

	class DefaultLayer : public Layer {
		Camera& m_Camera;
	public:
		DefaultLayer(Shader* shader, Camera& camera);
		~DefaultLayer();

		void render() override;
	};

}}

#endif /* end of include guard: DEFAULTLAYER_HPP */
