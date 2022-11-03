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
#include <array>
#include <SFML/Window.hpp>

namespace eng
{
    class SuperInput {
        public:
            enum class JoyAnalog {
                leftStickLeftAxis, leftStickRightAxis,
                leftStickUpAxis, leftStickDownAxis,
                rightStickLeftAxis, rightStickRightAxis,
                rightStickUpAxis, rightStickDownAxis,
                leftTrigger, rightTrigger
            };

            // a = cross, Nintendo B, Xbox A
            // b = circle, Nintendo A, Xbox B
            // x = square, Nintendo Y, Xbox X
            // y = triangle, Nintendo X, Xbox Y
            // share = Nintendo Screenshot, Xbox Share, ps5 microphone
            enum class JoyButton {
                a, b, y, x, up, down, right, left, start, select,
                l1, l2, l3, r1, r2, r3, home, share
            };

            enum Key {
                a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w,
                x, y, z, num0, num1, num2, num3, num4, num5, num6, num7, num8, num9,
                escape,
                leftctrl, leftshift, leftalt, leftsystem,
                rightctrl, rightshift, rightalt, rightsystem,
                menu, leftbracket, rightbracket, semicolon, comma, period, quote,
                slash, backslash, tilde, equal, hyphen, space, enter, backspace,
                //aligned to sf::Keyboard values
                tab, left = 71, right = 72, up = 73, down = 74
            };

            enum class MouseButton {
                left, right, middle, forward, backward
            };

            SuperInput(sf::Window &w);
            ~SuperInput();

            void addAction(std::string name, float deadzone = 0.1f);
            void addEvent(std::string action, eng::SuperInput::Key keyEvent);
            void addEvent(std::string action, eng::SuperInput::JoyAnalog joyEvent, int joyNum);
            void addEvent(std::string action, eng::SuperInput::JoyButton joyEvent, int joyNum);
            void addEvent(std::string action, eng::SuperInput::MouseButton buttonEvent);
            void clearEvent(std::string action);

            void updateEvents();

            float getActionStrength(std::string action);
            bool isActionPressed(std::string action);
            bool isActionJustPressed(std::string action);
            bool isActionJustReleased(std::string action);
        protected:
        private:
            std::map<std::string, std::array<float, 3>> _inputMap;
            std::map<eng::SuperInput::Key, std::vector<std::string>> _keyEvents;
            std::map<std::pair<int, eng::SuperInput::JoyAnalog>, std::vector<std::string>> _analogEvents;
            std::map<std::pair<int, eng::SuperInput::JoyButton>, std::vector<std::string>> _buttonEvents;
            std::map<eng::SuperInput::MouseButton, std::vector<std::string>> _mouseEvents;
            sf::Window &_w;
    };
} // namespace eng



#endif /* !SUPERINPUT_HPP_ */
