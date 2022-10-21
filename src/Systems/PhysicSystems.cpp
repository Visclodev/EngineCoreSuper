/*
** EPITECH PROJECT, 2022
** EngineCoreSuper
** File description:
** PhysicSystems
*/

#include "PhysicSystems.hpp"

eng::PhysicSystems::PhysicSystems(sf::Time &delta):
_delta(delta)
{
}

eng::PhysicSystems::~PhysicSystems()
{
}

void eng::PhysicSystems::applyVelocities(Registry &r)
{
    auto &positions = r.getComponents<Position>();
    auto &velocities = r.getComponents<Velocity>();

    for (int i = 0; i < positions.size() && i < velocities.size(); i++) {
        if (positions[i].has_value() && velocities[i].has_value()) {
            auto &position = positions[i].value();
            auto &velocity = velocities[i].value();

            position.x += velocity.x * _delta.asSeconds();
            position.y += velocity.y * _delta.asSeconds();
        }
    }
}
