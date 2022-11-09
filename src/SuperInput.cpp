/*
** EPITECH PROJECT, 2022
** EngineCoreSuper
** File description:
** SuperInput
*/

#include "SuperInput.hpp"

eng::SuperInput::SuperInput(sf::Window &w): _w(w)
{
}

eng::SuperInput::~SuperInput()
{
}

void eng::SuperInput::_setInput(std::string input, float value)
{
    _inputMap[input][2] = _inputMap[input][0];
    _inputMap[input][0] = value;
}

void eng::SuperInput::updateEvents()
{
    sf::Event event;

    // Set set previous values as new ones
    for (auto it = _inputMap.begin(); it != _inputMap.end(); it++)
        _setInput(it->first, it->second[0]);
    while (_w.pollEvent(event)) {
        // Press events
        if (event.type == sf::Event::KeyPressed) {
            auto it = _keyEvents[(Key)event.key.code].begin();
            for (; it != _keyEvents[(Key)event.key.code].end(); it++) {
                _setInput(*it, 1.0f);
            }
        }
        if (event.type == sf::Event::JoystickButtonPressed) {
            std::pair<int, JoyButton> pair(event.joystickButton.joystickId,
            (JoyButton)event.joystickButton.button);
            auto it = _buttonEvents[pair].begin();
            for (; it != _buttonEvents[pair].end(); it++) {
                _setInput(*it, 1.0f);
            }
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            auto it = _mouseEvents[(MouseButton)event.mouseButton.button].begin();
            for (; it != _mouseEvents[(MouseButton)event.mouseButton.button].end(); it++) {
                _setInput(*it, 1.0f);
            }
        }
        // Release events
        if (event.type == sf::Event::KeyReleased) {
            auto it = _keyEvents[(Key)event.key.code].begin();
            for (; it != _keyEvents[(Key)event.key.code].end(); it++) {
                _setInput(*it, 0.0f);
            }
        }
        if (event.type == sf::Event::JoystickButtonReleased) {
            std::pair<int, JoyButton> pair(event.joystickButton.joystickId,
            (JoyButton)event.joystickButton.button);
            auto it = _buttonEvents[pair].begin();
            for (; it != _buttonEvents[pair].end(); it++) {
                _setInput(*it, 0.0f);
            }
        }
        if (event.type == sf::Event::MouseButtonReleased) {
            auto it = _mouseEvents[(MouseButton)event.mouseButton.button].begin();
            for (; it != _mouseEvents[(MouseButton)event.mouseButton.button].end(); it++) {
                _setInput(*it, 0.0f);
            }
        }
        // Analog events
        if (event.type == sf::Event::JoystickMoved) {
            std::pair<int, JoyAnalog> pair(event.joystickMove.joystickId,
            (JoyAnalog)event.joystickMove.axis);
            auto it = _analogEvents[pair].begin();
            for (; it != _analogEvents[pair].end(); it++) {
                _setInput(*it, (event.joystickMove.position / 100.0f));
            }
        }
    }
}

void eng::SuperInput::addAction(std::string action, float deadzone)
{
    _inputMap[action] = {0.0f, deadzone, 0.0f};
}

// Add events

void eng::SuperInput::addEvent(std::string action, eng::SuperInput::Key keyEvent)
{
    _keyEvents[keyEvent].emplace_back(action);
}

void eng::SuperInput::addEvent(std::string action,
eng::SuperInput::JoyAnalog joyEvent, int joyIdx)
{
    _analogEvents[{joyIdx, joyEvent}].emplace_back(action);
}

void eng::SuperInput::addEvent(std::string action,
eng::SuperInput::JoyButton joyEvent, int joyIdx)
{
    _buttonEvents[{joyIdx, joyEvent}].emplace_back(action);
}

void eng::SuperInput::addEvent(std::string action, eng::SuperInput::MouseButton mouseEvent)
{
    _mouseEvents[mouseEvent].emplace_back(action);
}

void eng::SuperInput::clearEvent(std::string action)
{
    // Clear key events related to action
    for (auto it = _keyEvents.begin(); it != _keyEvents.end(); it++)
        for (auto i = it->second.begin(); i != it->second.end(); i++)
            if (*i == action)
                it->second.erase(i);
    // Clear mouse events related to action
    for (auto it = _mouseEvents.begin(); it != _mouseEvents.end(); it++)
        for (auto i = it->second.begin(); i != it->second.end(); i++)
            if (*i == action)
                it->second.erase(i);
    // Clear joyAnalog events related to action
    for (auto it = _analogEvents.begin(); it != _analogEvents.end(); it++)
        for (auto i = it->second.begin(); i != it->second.end(); i++)
            if (*i == action)
                it->second.erase(i);
    // Clear joyButton events related to action
    for (auto it = _buttonEvents.begin(); it != _buttonEvents.end(); it++)
        for (auto i = it->second.begin(); i != it->second.end(); i++)
            if (*i == action)
                it->second.erase(i);
}

// Action Getters

float eng::SuperInput::getActionStrength(std::string action)
{
    return _inputMap[action][0];
}

bool eng::SuperInput::isActionPressed(std::string action)
{
    return (_inputMap[action][0] == 1.0f);
}

bool eng::SuperInput::isActionJustPressed(std::string action)
{
    return (_inputMap[action][0] == 1.0f && _inputMap[action][2] < 1.0f);
}

bool eng::SuperInput::isActionJustReleased(std::string action)
{
    return (_inputMap[action][0] < 1.0f && _inputMap[action][2] == 1.0f);
}

std::array<int, 2> eng::SuperInput::getMousePosition(bool local)
{
    std::array<int, 2> res;

    if (local) {
        res[0] = sf::Mouse::getPosition(_w).x;
        res[1] = sf::Mouse::getPosition(_w).y;
    } else {
        res[0] = sf::Mouse::getPosition().x;
        res[1] = sf::Mouse::getPosition().y;
    }
    return (res);
}