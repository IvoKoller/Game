#include "camera.hpp"

namespace evo {
namespace graphics {

    Camera::Camera(const maths::mat4& projectionMatrix)
    : m_ProjectionMatrix(projectionMatrix) {
        m_ViewMatrix = maths::mat4::identity();
		m_Position = maths::vec3();
		//m_Rotation = maths::vec3();
    }

    Camera::~Camera(){ }
}}
