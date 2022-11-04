/*
** EPITECH PROJECT, 2022
** EngineCoreSuper
** File description:
** PhysicSystems
*/

#include "PhysicSystems.hpp"

eng::PhysicSystems::PhysicSystems(float &delta):
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

            vl.x = flerp(vl.x, 0, rb.drag * _delta);
            vl.y = flerp(vl.y, 0, rb.drag * _delta);
            vl.angular = flerp(vl.angular, 0, rb.drag * _delta);
            if (rb.hasGravity)
                vl.y += rb.gravityForce * _delta;
        }
    }
}

// Need to optimise this method
// In terms, this will replace `applyVelocity()`
void eng::PhysicSystems::moveAndCollide(Registry &r)
{
    auto &velocities = r.getComponents<Velocity>();
    auto &rigidbodies = r.getComponents<RigidBody>();
    auto &spColliders = r.getComponents<CircleCollider>();
    auto &rcColliders = r.getComponents<RectCollider>();
    auto &positions = r.getComponents<Position>();
    std::array<float, 2> oldPos;
    int cId = 0;

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
                if (rb.colliderType == RigidBody::ColliderType::RECTANGLE)
                    cId = _isColliding(i, rcColliders[i].value(), r);
                else
                    cId = _isColliding(i, spColliders[i].value(), r);
                if (cId != -1) {
                    _bounce(po, vl, oldPos);
                    velocities[cId].value().x += -vl.x;
                    velocities[cId].value().y += -vl.y;
                }
            }
        }
    }
}

void eng::PhysicSystems::_addVel(eng::Position &p, eng::Velocity &v)
{
    p.x += v.x * _delta;
    p.y += v.y * _delta;
    p.rotation += v.angular * _delta;
}

void eng::PhysicSystems::_bounce(eng::Position &p, eng::Velocity &v,
std::array<float, 2> oldP)
{
    p.x = oldP[0];
    p.y = oldP[1];
    v.x = -v.x * 0.5;
    v.y = -v.y * 0.5;
}

int eng::PhysicSystems::_isColliding(int id, eng::RectCollider &rect,
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
            if (rb.colliderType == eng::RigidBody::ColliderType::CIRCLE) {
                auto &c = r.getComponents<CircleCollider>()[i].value();
                if (areCircleAndRectColliding(position, c, p, rect))
                    return i;
            } else if (rb.colliderType == eng::RigidBody::ColliderType::RECTANGLE) {
                auto &c = r.getComponents<RectCollider>()[i].value();
                if (areRectColliding(position, rect, p, c))
                    return i;
            }
        }
    }
    return -1;
}

int eng::PhysicSystems::_isColliding(int id, eng::CircleCollider &circle,
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
            if (rb.colliderType == eng::RigidBody::ColliderType::CIRCLE) {
                auto &c = r.getComponents<CircleCollider>()[i].value();
                if (areCircleColliding(position, circle, p, c))
                    return i;
            } else if (rb.colliderType == eng::RigidBody::ColliderType::RECTANGLE) {
                auto &c = r.getComponents<RectCollider>()[i].value();
                if (areCircleAndRectColliding(position, circle, p, c))
                    return i;
            }
        }
    }
    return -1;
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

bool eng::PhysicSystems::isPointOnCircle(eng::Position &point,
eng::Position &centre, eng::CircleCollider &circle)
{
    float distance = fsqr(centre.x - point.x) + fsqr(centre.y - point.y);
    return (distance < fsqr(circle.radius));
}

bool eng::PhysicSystems::isPointOnRect(eng::Position &point,
eng::Position &topLeft, eng::RectCollider &rect)
{
    return ((point.x > topLeft.x && point.x < topLeft.x + rect.width)
    && (point.y > topLeft.y && point.y < topLeft.y + rect.height));
}

bool eng::PhysicSystems::areCircleColliding(eng::Position &posA,
eng::CircleCollider &spA, eng::Position &posB, eng::CircleCollider &spB)
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

bool eng::PhysicSystems::areCircleAndRectColliding(eng::Position &posA,
eng::CircleCollider &spA, eng::Position &posB, eng::RectCollider &rcB)
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