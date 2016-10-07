#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "../maths/vec2.hpp"
#include "../maths/vec3.hpp"
#include "../managers/staticManager.hpp"

namespace evo {
namespace physics {

    //Each collider is bound to a position. That way, I don't have to update
    //the colliders position manually

    //width and height might vary during execution

    enum Layer { All, Static, Dynamic, Trigger };

    class Collider : public StaticManager<Collider> {
        const maths::vec3& m_Min; //min = position
        float m_Width;
        float m_Height;
        Layer m_Layer;
        bool m_Inverted;

    public:
        Collider(const maths::vec3& position, float width, float height,
            Layer layer = Layer::Static, bool invert = false);

        bool CollidesWith(const char* name) const;
        bool CollidesWith(const unsigned int& id) const;
        bool CollidesWith(const Collider& other) const;

        bool Collides(Layer layer = Layer::All) const ; //layer = all checks all layers

        bool CollidesTopWith(const Collider& other) const;
        bool CollidesBottomWith(const Collider& other) const;
        bool CollidesLeftWith(const Collider& other) const;
        bool CollidesRightWith(const Collider& other) const;

        bool CollidesTop(Layer layer = Layer::All) const;
        bool CollidesBottom(Layer layer = Layer::All) const;
        bool CollidesLeft(Layer layer = Layer::All) const;
        bool CollidesRight(Layer layer = Layer::All) const;

        bool Contains(const maths::vec2& point) const;

        bool operator==(const Collider& other) const;
        bool operator!=(const Collider& other) const;

        bool operator<(const Collider& other) const;
        bool operator>(const Collider& other) const;

        friend std::ostream& operator<<(std::ostream& stream, const Collider& collider);
    private:
        bool Intersects(const Collider& other) const;
    };

} }

#endif /* end of include guard: COLLIDER_HPP */
