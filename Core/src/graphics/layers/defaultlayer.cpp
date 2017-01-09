#include "defaultlayer.hpp"

namespace evo {
namespace graphics {

	DefaultLayer::DefaultLayer(Shader* shader, Camera& camera, float parallax)
		: Layer(new BatchRenderer2D(), shader, camera.projectionMatrix),
		  m_Camera(camera), m_Parallax(parallax) { }

	DefaultLayer::~DefaultLayer() { }

	void DefaultLayer::render() {
		m_Shader->enable();
		m_Shader->setUniformMat4("vw_matrix", maths::mat4::translate(
			m_Camera.getPosition() * m_Parallax));
		m_Renderer->begin();

		for (Renderable2D* renderable : m_Renderables){
			renderable->update();
			renderable->submit(m_Renderer);
		}

		m_Renderer->end();
		m_Renderer->flush();
	}


}}
