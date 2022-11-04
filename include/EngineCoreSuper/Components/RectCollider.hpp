/*
** EPITECH PROJECT, 2022
** EngineCoreSuper
** File description:
** RectCollider
*/

#ifndef RECTCOLLIDER_HPP_
#define RECTCOLLIDER_HPP_

namespace eng
{
    class RectCollider {
        public:
            RectCollider(int width_, int height_, int offsetX_ = 0, int offsetY_ = 0):
            width(width_), height(height_), offsetX(offsetX_), offsetY(offsetY_)
            {}
            ~RectCollider() {}

            int width;
            int height;
            int offsetX;
            int offsetY;
        protected:
        private:
    };
} // namespace eng



#endif /* !RECTCOLLIDER_HPP_ */
