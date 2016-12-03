#include "layer.hpp"

namespace evo {
namespace graphics {
	Layer::Layer(Renderer2D* renderer, Shader* shader, maths::mat4 projectionMatrix)
		: m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projectionMatrix) {
		m_Shader->enable();
		m_Shader->setUniformMat4("pr_matrix", m_ProjectionMatrix);
		m_Shader->disable();
	}

	Layer::~Layer(){ //TODO: causes problemes
		delete m_Shader;
		delete m_Renderer;

		clear();
	}

	void Layer::add(Renderable2D& renderable) {
		m_Renderables.push_back(&renderable);
	}

	void Layer::remove(Renderable2D& renderable) {
		for(int i = 0; i < m_Renderables.size(); i++) {
			if(m_Renderables[i] == &renderable){
				//std::cout << &renderable << std::endl;
				m_Renderables.erase(m_Renderables.begin() + i);
				//std::cout << m_Renderables.size() << std::endl;
				break;
			}
		}
	}

	void Layer::clear(){
		for (int i = 0; i < m_Renderables.size(); i++) delete m_Renderables[i];
		m_Renderables.clear();
	}

	void Layer::render() {
		m_Shader->enable();
		m_Renderer->begin();

		for (Renderable2D* renderable : m_Renderables){
			renderable->update();
			renderable->submit(m_Renderer);
		}

		m_Renderer->end();
		m_Renderer->flush();
	}

} }
