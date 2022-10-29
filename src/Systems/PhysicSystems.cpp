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

            _addVel(position, velocity);
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

            vl.x = flerp(vl.x, 0, rb.drag * _delta.asSeconds());
            vl.y = flerp(vl.y, 0, rb.drag * _delta.asSeconds());
            vl.angular = flerp(vl.angular, 0, rb.drag * _delta.asSeconds());
            if (rb.hasGravity)
                vl.y += rb.gravityForce * _delta.asSeconds();
        }
    }
}

// Need to optimise this method
// In terms, this will replace `applyVelocity()`
void eng::PhysicSystems::moveAndCollide(Registry &r)
{
    auto &velocities = r.getComponents<Velocity>();
    auto &rigidbodies = r.getComponents<RigidBody>();
    auto &spColliders = r.getComponents<SphereCollider>();
    auto &rcColliders = r.getComponents<RectCollider>();
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

            // if this is a rigidbody, then get the collider and check collision
            if (i < rigidbodies.size() && rigidbodies[i].has_value()) {
                auto &rb = rigidbodies[i].value();
                if (rb.colliderType == RigidBody::ColliderType::RECTANGLE) {
                    if (_isColliding(i, rcColliders[i].value(), r))
                        _bounce(po, vl, oldPos);
                } else {
                    if (_isColliding(i, spColliders[i].value(), r))
                        _bounce(po, vl, oldPos);
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

void eng::PhysicSystems::_bounce(eng::Position &p, eng::Velocity &v,
std::array<float, 2> oldP)
{
    p.x = oldP[0];
    p.y = oldP[1];
    v.x = -v.x * 0.5;
    v.y = -v.y * 0.5;
}

bool eng::PhysicSystems::_isColliding(int id, eng::RectCollider &rect,
eng::Registry &r)
{
    auto &positions = r.getComponents<Position>();
    auto &position = positions[id].value();
    auto &rigidbodies = r.getComponents<RigidBody>();

    // Go through every rigidbody
    for (int i = 0; i < positions.size() && i < rigidbodies.size(); i++) {
        if (i != id && positions[i].has_value() && rigidbodies[i].has_value()) {
            auto &p = positions[i].value();
            auto &rb = rigidbodies[i].value();
            if (rb.colliderType == eng::RigidBody::ColliderType::SPHERE) {
                auto &c = r.getComponents<SphereCollider>()[i].value();
                if (areSphereAndRectColliding(position, c, p, rect))
                    return true;
            } else if (rb.colliderType == eng::RigidBody::ColliderType::RECTANGLE) {
                auto &c = r.getComponents<RectCollider>()[i].value();
                if (areRectColliding(position, rect, p, c))
                    return true;
            }
        }
    }
    return false;
}

bool eng::PhysicSystems::_isColliding(int id, eng::SphereCollider &sphere,
eng::Registry &r)
{
    auto &positions = r.getComponents<Position>();
    auto &position = positions[id].value();
    auto &rigidbodies = r.getComponents<RigidBody>();

    // Go through every rigidbody
    for (int i = 0; i < positions.size() && i < rigidbodies.size(); i++) {
        if (i != id && positions[i].has_value() && rigidbodies[i].has_value()) {
            auto &p = positions[i].value();
            auto &rb = rigidbodies[i].value();
            if (rb.colliderType == eng::RigidBody::ColliderType::SPHERE) {
                auto &c = r.getComponents<SphereCollider>()[i].value();
                if (areSphereColliding(position, sphere, p, c))
                    return true;
            } else if (rb.colliderType == eng::RigidBody::ColliderType::RECTANGLE) {
                auto &c = r.getComponents<RectCollider>()[i].value();
                if (areSphereAndRectColliding(position, sphere, p, c))
                    return true;
            }
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
    float distance = fsqr(posB.x - posA.x) + fsqr(posB.y - posA.y);
    return (distance < fsqr(spA.radius + spB.radius));
}

bool eng::PhysicSystems::areRectColliding(eng::Position &posA,
eng::RectCollider &rcA, eng::Position &posB, eng::RectCollider &rcB)
{
    return !((posB.x >= posA.x + rcA.width)
    || (posB.x + rcB.width <= posA.x)
    || (posB.y >= posA.y + rcA.height)
    || (posB.y + rcB.height <= posA.y));
}

bool eng::PhysicSystems::areSphereAndRectColliding(eng::Position &posA,
eng::SphereCollider &spA, eng::Position &posB, eng::RectCollider &rcB)
{
    // First check AABB
    if ((posB.x >= posA.x + spA.radius)
    || (posB.x + rcB.width <= posA.x - spA.radius)
    || (posB.y >= posA.y + spA.radius)
    || (posB.y + rcB.height <= posA.y - spA.radius))
        return false;

    // Then check if at least one corner is inside the circle
    // top-left Corner
    if ((fsqr(posB.x - posA.x) + fsqr(posB.y - posA.y) < fsqr(spA.radius))
    || (fsqr((posB.x + rcB.width) - posA.x) + fsqr(posB.y - posA.y) < fsqr(spA.radius))
    || (fsqr(posB.x - posA.x) + fsqr((rcB.height + posB.y) - posA.y) < fsqr(spA.radius))
    || (fsqr((posB.x + rcB.width) - posA.x) + fsqr((rcB.height + posB.y) - posA.y) < fsqr(spA.radius)))
        return true;
    
    // Then check if the centre of the circle is on one of the projections of
    // the rect
    // X axis projection
    if (posA.x > posB.x && posA.x < posB.x + rcB.width)
        return true;
    // Y axis projection
    if (posA.y > posB.y && posA.y < posB.y + rcB.height)
        return true;
    return false;
}