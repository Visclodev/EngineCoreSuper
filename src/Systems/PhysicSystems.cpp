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
            position.rotation += velocity.angular * _delta.asSeconds();
        }
    }
}

// Fast linear interpolation
static float flerp(float a, float b, float t)
{
    return a + t * (b - a);
}

void eng::PhysicSystems::applyGravity(Registry &r)
{
    auto &velocities = r.getComponents<Velocity>();
    auto &rigidbodies = r.getComponents<RigidBody>();

    for (int i = 0; i < velocities.size() && i < rigidbodies.size(); i++) {
        if (velocities[i].has_value() && rigidbodies[i].has_value()) {
            auto &rb = rigidbodies[i].value();
            auto &vl = velocities[i].value();

            flerp(vl.x, 0, rb.drag * _delta.asSeconds());
            flerp(vl.y, 0, rb.drag * _delta.asSeconds());
            if (rb.hasGravity) {
                // Gravity
                vl.y += rb.gravityForce * _delta.asSeconds();
            }
        }
    }
}

// Need to optimise this method
void eng::PhysicSystems::moveAndCollide(Registry &r)
{
    auto &velocities = r.getComponents<Velocity>();
    auto &rigidbodies = r.getComponents<RigidBody>();
    auto &spColliders = r.getComponents<SphereCollider>();
    auto &positions = r.getComponents<Position>();
    std::array<float, 2> oldPos;

    // Go through the registry
    for (int i = 0; i < velocities.size() && i < positions.size(); i++) {

        // if there is a position and a velocity, then move the entity
        if (velocities[i].has_value() && positions[i].has_value()) {
            auto &po = positions[i].value();
            auto &vl = velocities[i].value();

            oldPos[0] = float(po.x);
            oldPos[1] = float(po.y);
            _addVel(po, vl);

            // if this is a rigidbody and it has a sphere collider
            if (i < rigidbodies.size() && rigidbodies[i].has_value()
            && i < spColliders.size() && spColliders[i].has_value()) {
                auto &rb = rigidbodies[i].value();
                auto &sp = spColliders[i].value();

                if (_isColliding(i, r)) {
                    // go back to old position and revert forces (yes wrong physics)
                    po.x = oldPos[0];
                    po.y = oldPos[1];
                    vl.x = -vl.x;
                    vl.y = -vl.y;
                }
            }
        }
    }
}

void eng::PhysicSystems::_addVel(eng::Position &p, eng::Velocity &v)
{
    p.x += v.x * _delta.asSeconds();
    p.y += v.y * _delta.asSeconds();
    p.rotation += v.angular * _delta.asSeconds();
}

bool eng::PhysicSystems::_isColliding(int id, eng::Registry &r)
{
    auto &positions = r.getComponents<Position>();
    auto &position = positions[id].value();
    auto &spColliders = r.getComponents<SphereCollider>();
    auto &sphere = spColliders[id].value();

    for (int i = 0; i < spColliders.size() && i < positions.size(); i++) {
        if (i != id && positions[i].has_value() && spColliders[i].has_value()) {
            auto &p = positions[i].value();
            auto &s = spColliders[i].value();
            if (areSphereColliding(position, sphere, p, s))
                return true;
        }
    }
    return false;
}

// Fast square root
static float fsqrt(const float x)  
{
    union {
        int i;
        float x;
    } u;
    u.x = x;
    u.i = (1<<29) + (u.i >> 1) - (1<<22); 
    return u.x;
}

// Fast square
static float fsqr(const float x)
{
    return (x * x);
}

bool eng::PhysicSystems::areSphereColliding(eng::Position &posA,
eng::SphereCollider &spA, eng::Position &posB, eng::SphereCollider &spB)
{
    float distance = fsqrt(fsqr(posB.x - posA.x) + fsqr(posB.y - posA.y));
    return (distance < spA.radius + spB.radius);
}