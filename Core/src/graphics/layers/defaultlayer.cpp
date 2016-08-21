#include "defaultlayer.hpp"

namespace evo {
namespace graphics {

	DefaultLayer::DefaultLayer(Shader* shader, const Camera& camera)
		: Layer(new BatchRenderer2D(), shader, camera.getProjectionMatrix()),
		  m_Camera(camera) { }

	DefaultLayer::~DefaultLayer() { }

	void DefaultLayer::render() {
		m_Shader->enable();
		m_Shader->setUniformMat4("vw_matrix", maths::mat4::translate(m_Camera.getPosition()));
		m_Renderer->begin();

		for (const Renderable2D* renderable : m_Renderables)
			renderable->submit(m_Renderer);

		m_Renderer->end();
		m_Renderer->flush();
	}

}}
