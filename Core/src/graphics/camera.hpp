#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../maths/maths.hpp"

namespace evo {
namespace graphics {

    struct Camera {
        const maths::vec3* target = nullptr;
        maths::mat4 projectionMatrix, viewMatrix;
		maths::vec3 position;
        maths::vec3 correction;
        //Rotation, FocalPoint;

        Camera(const maths::mat4& projectionMatrix = maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
        ~Camera();

        void bindToTarget(const maths::vec3& position, const maths::vec2 size = maths::vec2()) {
            target = &position;
            correction.x = size.x/2;
            correction.y = size.y/2;
        }
        void unbind() { target = nullptr; }
        void update() {
            if(target != nullptr) position = *target;
            position = -position; //inverts coordinates in any case
            position -= correction;
        }

    };

}}

#endif /* end of include guard: CAMERA_HPP */
