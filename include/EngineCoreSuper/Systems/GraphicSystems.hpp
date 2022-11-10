/*
** EPITECH PROJECT, 2022
** EngineCoreSuper
** File description:
** GraphicSystems
*/

#ifndef GRAPHICSYSTEMS_HPP_
#define GRAPHICSYSTEMS_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../Registry.hpp"
#include "../Components/SuperComponents.hpp"

namespace eng
{
    class GraphicSystems {
        public:
            GraphicSystems(int width, int height, std::string name);
            ~GraphicSystems();

            /// @brief Draw every drawable on the framebuffer
            /// @param r The registry to draw on the framebuffer
            void drawSystem(Registry &r);

            /// @brief Draw every writable on the framebuffer
            /// @param r The registry to draw on the framebuffer
            void writeSystem(Registry &r);

            /// @brief update and draw particles on the framebuffer
            /// @param r The registry on which to apply this system
            void particleSystem(Registry &r);

            /// @brief update the spritesheets rects
            /// @param r The registry on which to apply this system
            void animateSystem(Registry &r);

            /// @brief check if the window should close
            /// @return true if it should close, false if not
            bool isWindowOpen();
            
            /// @brief Displays the window and updates the delta time
            void display();

            /// @brief clear the screen with a sf::Color
            /// @param c the color you want the screen to be filled with
            void clear(sf::Color c = sf::Color::Black);

            /// @brief get the delta time (time since last frame)
            /// @return delta in sf::Time reference
            sf::Time &getDelta();

            /// @brief Gets a reference to the delta time in seconds
            /// @return reference to a float (delta time in seconds)
            float &getDeltaSeconds();

            /// @brief get the clock (restarted every frame update)
            /// @return the sf::Clock reference
            sf::Clock &getClock();

            /// @brief get the renderWindow
            /// @return the sf::RenderWindow reference
            sf::RenderWindow &getRenderWindow();

            /// @brief Set the framerate limit
            /// @param limit the frequency of updates (per seconds)
            void setFrameRateLimit(unsigned int limit);

            /// @brief Get the framerate limit
            /// @return The framerate limit
            unsigned int getFrameRateLimit();

            /// @brief A system who handle specific window event
            void eventCatchWindow();

            bool &isWindowFocused();

            void closeWindow();
        protected:
        private:
            void _displayParticleVector(std::vector<eng::SuperParticle> vector);
            void _displayParticleVector(std::vector<eng::SuperParticle> vector,
                float x, float y);
            
            float _deltaSeconds;
            sf::Time _delta;
            sf::Clock _clock;
            sf::RenderWindow _window;
            sf::Event _event;
            bool _isWindowFocused = true;
            unsigned int _frameRateLimit;
    };
} // namespace eng



#endif /* !GRAPHICSYSTEMS_HPP_ */
