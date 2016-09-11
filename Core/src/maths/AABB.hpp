#ifndef AABB_HPP
#define AABB_HPP

#include "vec2.hpp"
#include "vec3.hpp"
#include <cmath>

namespace evo {
namespace maths {

    struct AABB {
        vec3 min;
        vec3 max;

        AABB();
        AABB(const vec2& min, const vec2& max);
        AABB(const vec3& min, const vec3& max);
        AABB(float x, float y, float width, float height);
        AABB(float x, float y, float z, float width, float height, float depth);

        bool Intersects(const AABB& other) const;
        bool Contains(const vec2& point) const;
        bool Contains(const vec3& point) const;

        vec3 Center() const;

        bool operator==(const AABB& other) const;
        bool operator!=(const AABB& other) const;

        bool operator<(const AABB& other) const;
        bool operator>(const AABB& other) const;

        friend std::ostream& operator<<(std::ostream& stream, const AABB& aabb);

        inline vec3 GetSize() const { return vec3(std::abs(max.x - min.x), std::abs(max.y - min.y), std::abs(max.z - min.z)); }
    };

} }

#endif /* end of include guard: AABB_HPP */
