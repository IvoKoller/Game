#include "staticlayer.hpp"

namespace evo {
namespace graphics {

	StaticLayer::StaticLayer(Shader* shader)
		: Layer(new BatchRenderer2D(), shader, maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
	{
	}

	StaticLayer::~StaticLayer() { }

	void StaticLayer::render() {
		m_Shader->enable();
		m_Shader->setUniformMat4("vw_matrix", maths::mat4::identity());
		m_Renderer->begin();
		for (const Renderable2D* renderable : m_Renderables) renderable->submit(m_Renderer);
		m_Renderer->end();
		m_Renderer->flush();
	}

}}
