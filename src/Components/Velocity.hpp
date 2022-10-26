/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Velocity
*/

#ifndef VELOCITY_HPP_
#define VELOCITY_HPP_

namespace eng
{
    /// @brief A class holding the velocity of an entity
    class Velocity {
        public:
            /// @brief Velocity object constructor
            /// @param _x horizontal velocity
            /// @param _y vertical velocity
            Velocity(float _x = 0, float _y = 0): x(_x), y(_y) {} 
            ~Velocity() {}

            float x;
            float y;
            float angular = 0;
        protected:
        private:
    };
} // namespace eng



#endif /* !VELOCITY_HPP_ */
