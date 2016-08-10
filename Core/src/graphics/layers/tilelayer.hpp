#pragma once

#include "layer.hpp"
#include "../BatchRenderer2D.hpp"

namespace evo { namespace graphics {

	class TileLayer : public Layer
	{
	public:
		TileLayer(Shader* shader);
		~TileLayer();
	};

} }