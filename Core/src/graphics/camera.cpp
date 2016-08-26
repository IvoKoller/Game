#include "camera.hpp"

namespace evo {
namespace graphics {

    Camera::Camera(const maths::mat4& projectionMatrix)
    : projectionMatrix(projectionMatrix) {
        viewMatrix = maths::mat4::identity();
		position = maths::vec3();
		//m_Rotation = maths::vec3();
    }

    Camera::~Camera(){ }
}}
