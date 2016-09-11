#ifndef CAMER_HPP
#define CAMER_HPP

#include "../maths/maths.hpp"

namespace evo {
namespace graphics {

    struct Camera {
        maths::mat4 projectionMatrix, viewMatrix;
		maths::vec3 position; //, Rotation, FocalPoint;

        Camera(const maths::mat4& projectionMatrix = maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
        ~Camera();
    };

}}

#endif /* end of include guard: CAMER_HPP */
