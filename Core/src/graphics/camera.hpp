#ifndef CAMERA_H
#define CAMERA_H

#include "../maths/maths.hpp"

namespace evo {
namespace graphics {

    class Camera {
        maths::mat4 m_ProjectionMatrix, m_ViewMatrix;
		maths::vec3 m_Position; //, m_Rotation, m_FocalPoint;
    public:
        Camera(const maths::mat4& projectionMatrix = maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
        ~Camera();

        void setPosition(const maths::vec3& position) {
            m_Position = position;
            m_ViewMatrix = maths::mat4::translation(m_Position);
        }

        maths::vec3 getPosition() const { return m_Position; }
        maths::mat4 getProjectionMatrix() const { return m_ProjectionMatrix; }
    };

}}

#endif /* end of include guard: CAMERA_H */
