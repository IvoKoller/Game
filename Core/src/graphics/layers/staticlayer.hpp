#pragma once

#include "layer.hpp"
#include "../BatchRenderer2D.hpp"

namespace evo {
namespace graphics {

	class StaticLayer : public Layer {
	public:
		StaticLayer(Shader* shader);
		~StaticLayer();

		void render() override;
	};

}}
