#ifndef MAT4_H
#define MAT4_H

#include "maths_func.hpp"

#include "vec3.hpp"
#include "vec4.hpp"

namespace evo {
namespace maths {

	struct mat4 {
		union {
			float elements[4 * 4];
			vec4 rows[4];
		};

		mat4();
		mat4(float diagonal);
		mat4(float* elements);
		mat4(const vec4& row0, const vec4& row1, const vec4& row2, const vec4& row3);

		static mat4 identity();

		mat4& multiply(const mat4& other);
		friend mat4 operator*(mat4 left, const mat4& right);
		mat4& operator*=(const mat4& other);

		vec3 multiply(const vec3& other) const;
		friend vec3 operator*(const mat4& left, const vec3& right);

		vec4 multiply(const vec4& other) const;
		friend vec4 operator*(const mat4& left, const vec4& right);

		mat4& invert();

		vec4 getcolumn(int index) const;
		void setcolumn(uint index, const vec4& column); //TODO: same as unsigned int??
		vec3 getposition() const { return vec3( getcolumn(3) ); }
		void setposition(const vec3& position) { setcolumn(3, vec4(position, 1.0f) ); }

		static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
		static mat4 perspective(float fov, float aspectratio, float near, float far);
		static mat4 lookAt(const vec3& camera, const vec3& object, const vec3& up);

		static mat4 translate(const vec3& translation);
		static mat4 rotate(float angle, const vec3& axis);
		static mat4 scale(const vec3& scale);
		static mat4 invert(const mat4& matrix);

		static mat4 transpose(const mat4& matrix);
	};

} }

#endif /* end of include guard: MAT4_H */
