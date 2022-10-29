/*
** EPITECH PROJECT, 2022
** EngineCoreSuper
** File description:
** SphereCollider
*/

#ifndef SPHERECOLLIDER_HPP_
#define SPHERECOLLIDER_HPP_

namespace eng
{
    class SphereCollider {
        public:
            SphereCollider(int radius_):
            radius(radius_)
            {}
            ~SphereCollider() {}

            int radius;
        protected:
        private:
    };
} // namespace eng

#endif /* !SPHERECOLLIDER_HPP_ */
