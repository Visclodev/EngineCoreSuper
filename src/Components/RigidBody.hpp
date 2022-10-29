/*
** EPITECH PROJECT, 2022
** EngineCoreSuper
** File description:
** RigidBody
*/

#ifndef RIGIDBODY_HPP_
#define RIGIDBODY_HPP_

namespace eng
{
    class RigidBody {
        public:
            enum ColliderType {
                SPHERE,
                RECTANGLE
            };

            /// @brief RigidBody constructor
            /// @param type the type of collider (circle or rectangle atm)
            /// @param hasGravity_ set to true to have a constant downward force
            /// @param drag_ air friction, from 0 to 1, 0 = no friction
            RigidBody(ColliderType type, bool hasGravity_ = true,
            float drag_ = 0):
            colliderType(type), hasGravity(hasGravity_), drag(drag_)
            {}
            ~RigidBody() {}

            ColliderType colliderType;
            bool hasGravity;
            float gravityForce = 98.0f;
            /// @brief Air friction
            float drag = 0.0f;
        protected:
        private:
    };
} // namespace eng

#endif /* !RIGIDBODY_HPP_ */
