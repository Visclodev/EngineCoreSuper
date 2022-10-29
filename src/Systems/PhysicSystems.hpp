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
        protected:
        private:
            void _addVel(eng::Position &p, eng::Velocity &v);

            bool _isColliding(int id, eng::Registry &r);

            sf::Time &_delta;
    };
} // namespace eng


#endif /* !PHYSICSYSTEMS_HPP_ */
