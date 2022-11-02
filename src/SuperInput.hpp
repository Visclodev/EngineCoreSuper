/*
** EPITECH PROJECT, 2022
** EngineCoreSuper
** File description:
** SuperInput
*/

#ifndef SUPERINPUT_HPP_
#define SUPERINPUT_HPP_

#include <iostream>
#include <map>

namespace eng
{
    enum InputType {
        physical_key,
        key,
        joy_button,
        joy_axis,
        mouse_button,
    };

    class SuperInput {
        public:
            SuperInput();
            ~SuperInput();

            void addAction(std::string name);
            void addEvent(std::string action, InputType type);
        protected:
        private:
            std::map<std::string, float> _inputMap;
    };
} // namespace eng



#endif /* !SUPERINPUT_HPP_ */
