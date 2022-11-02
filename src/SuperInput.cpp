/*
** EPITECH PROJECT, 2022
** EngineCoreSuper
** File description:
** SuperInput
*/

#include "SuperInput.hpp"

eng::SuperInput::SuperInput()
{
}

eng::SuperInput::~SuperInput()
{
}

void eng::SuperInput::updateEvents(sf::Window &w)
{
    // Update every key events
    for (auto it = _keyEvents.begin(); it != _keyEvents.begin(); it++) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(it->first))) {
            for (auto i = it->second.begin(); i != it->second.end(); i++) {
                _inputMap[*i][2] = _inputMap[*i][0];
                _inputMap[*i][0] = 1.0f;
            }
        }
    }

    // Update every joystick button event

    // Update every joystick analog event

    // Update every mouse button event
}

void eng::SuperInput::addAction(std::string action, float deadzone)
{
    _inputMap[action] = {0.0f, deadzone, 0.0f};
}

// Add events

void eng::SuperInput::addEvent(std::string action, eng::SuperInput::Key keyEvent)
{
    _keyEvents[(sf::Keyboard::Key)keyEvent].push_back(action);
}

void eng::SuperInput::addEvent(std::string action, eng::SuperInput::JoyAnalog joyEvent)
{
    _analogEvents[joyEvent].push_back(action);
}

void eng::SuperInput::addEvent(std::string action, eng::SuperInput::JoyButton joyEvent)
{
    _buttonEvents[joyEvent].push_back(action);
}

void eng::SuperInput::addEvent(std::string action, eng::SuperInput::MouseButton mouseEvent)
{
    _mouseEvents[mouseEvent].push_back(action);
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
    return _inputMap[action][0] - _inputMap[action][1];
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