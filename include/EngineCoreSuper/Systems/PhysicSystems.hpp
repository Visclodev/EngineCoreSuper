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

            /// @brief Checks if a Point is over a rectangle
            /// @param point The position of the point
            /// @param centre The top left corner of the rectangle
            /// @param circle The rectangle collider
            /// return True if the point is on the rectangle
            bool isPointOnRect(eng::Position &point, eng::Position &topLeft,
            eng::RectCollider &rect);

            /// @brief Checks if a Point is over a circle
            /// @param point The position of the point
            /// @param centre The centre of the circle
            /// @param circle The circle collider
            /// return True if the point is on the circle
            bool isPointOnCircle(eng::Position &point, eng::Position &centre,
            eng::CircleCollider &circle);

            /// @brief Checks if a Circle collides with another
            /// @param posA the position of the first circle
            /// @param spA the first circle (a)
            /// @param posB the position of the second circle
            /// @param spB the second circle (b)
            /// @return True if a and b are colliding
            bool areCircleColliding(eng::Position &posA,
            eng::CircleCollider &spA, eng::Position &posB,
            eng::CircleCollider &spB);

            /// @brief Checks if a Rectangle collides with another
            /// @param posA the position of the first rectangle
            /// @param spA the first rectangle (a)
            /// @param posB the position of the second rectangle
            /// @param spB the second rectangle (b)
            /// @return True if a and b are colliding
            bool areRectColliding(eng::Position &posA, eng::RectCollider &rcA,
            eng::Position &posB, eng::RectCollider &rcB);

            /// @brief Checks if a Circle collides with a rectangle
            /// @param posA the position of the circle
            /// @param spA the circle (a)
            /// @param posB the position of the rectangle
            /// @param spB the rectangle (b)
            /// @return True if a and b are colliding
            bool areCircleAndRectColliding(eng::Position &posA,
            eng::CircleCollider &spA, eng::Position &posB, eng::RectCollider &rcB);
        protected:
        private:
            void _addVel(eng::Position &p, eng::Velocity &v);
            void _bounce(eng::Position &p, eng::Velocity &v,
            std::array<float, 2> oldP);

            int _isColliding(int id, eng::RectCollider &rect,
            eng::Registry &r);
            int _isColliding(int id, eng::CircleCollider &circle,
            eng::Registry &r);

            sf::Time &_delta;
    };
} // namespace eng


#endif /* !PHYSICSYSTEMS_HPP_ */
