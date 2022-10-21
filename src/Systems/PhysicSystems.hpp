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
#include "../Components/Components.hpp"

namespace eng
{
    class PhysicSystems {
        public:
            PhysicSystems(sf::Time &delta);
            ~PhysicSystems();

            void applyVelocities(Registry &r);
        protected:
        private:
            sf::Time _delta;
    };
} // namespace eng


#endif /* !PHYSICSYSTEMS_HPP_ */
