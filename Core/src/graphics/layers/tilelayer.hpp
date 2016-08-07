#pragma once

#include "layer.hpp"
#include "../BatchRenderer2D.hpp"

namespace sparky { namespace graphics {

	class TileLayer : public Layer
	{
	public:
		TileLayer(Shader* shader);
		~TileLayer();
	};

} }