/*
** EPITECH PROJECT, 2022
** EngineCoreSuper
** File description:
** PhysicSystems
*/

#ifndef PHYSICSYSTEMS_HPP_
#define PHYSICSYSTEMS_HPP_

#include <SFML/Config.hpp>
#include "../Registry.hpp"
#include "../Components/SuperComponents.hpp"

namespace eng
{
    class PhysicSystems {
        public:
            PhysicSystems(sf::Time &delta);
            ~PhysicSystems();

            void applyVelocities(Registry &r);
            void applyGravity(Registry &r);
            void moveAndCollide(Registry &r);

            /// @brief Checks if a Sphere collides with another
            /// @param posA the position of the first sphere
            /// @param spA the first sphere (a)
            /// @param posB the position of the second sphere
            /// @param spB the second sphere (b)
            /// @return True if a and b are colliding
            bool areSphereColliding(eng::Position &posA,
            eng::SphereCollider &spA, eng::Position &posB,
            eng::SphereCollider &spB);

            /// @brief Checks if a Rectangle collides with another
            /// @param posA the position of the first rectangle
            /// @param spA the first rectangle (a)
            /// @param posB the position of the second rectangle
            /// @param spB the second rectangle (b)
            /// @return True if a and b are colliding
            bool areRectColliding(eng::Position &posA, eng::RectCollider &rcA,
            eng::Position &posB, eng::RectCollider &rcB);

            /// @brief Checks if a Sphere collides with a rectangle
            /// @param posA the position of the sphere
            /// @param spA the sphere (a)
            /// @param posB the position of the rectangle
            /// @param spB the rectangle (b)
            /// @return True if a and b are colliding
            bool areSphereAndRectColliding(eng::Position &posA,
            eng::SphereCollider &spA, eng::Position &posB, eng::RectCollider &rcB);
        protected:
        private:
            void _addVel(eng::Position &p, eng::Velocity &v);
            void _bounce(eng::Position &p, eng::Velocity &v,
            std::array<float, 2> oldP);

            bool _isColliding(int id, eng::RectCollider &rect,
            eng::Registry &r);
            bool _isColliding(int id, eng::SphereCollider &sphere,
            eng::Registry &r);

            sf::Time &_delta;
    };
} // namespace eng


#endif /* !PHYSICSYSTEMS_HPP_ */
