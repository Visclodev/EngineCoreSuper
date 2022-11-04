/*
** EPITECH PROJECT, 2022
** EngineCoreSuper
** File description:
** CircleCollider
*/

#ifndef CIRCLECOLLIDER_HPP_
#define CIRCLECOLLIDER_HPP_

namespace eng
{
    class CircleCollider {
        public:
            CircleCollider(int radius_):
            radius(radius_)
            {}
            ~CircleCollider() {}

            int radius;
        protected:
        private:
    };
} // namespace eng

#endif /* !CIRCLECOLLIDER_HPP_ */
