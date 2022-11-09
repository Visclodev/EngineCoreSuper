/*
** EPITECH PROJECT, 2022
** EngineCoreSuper
** File description:
** main
*/

#include <EngineCoreSuper/EngineCoreSuper.hpp>

typedef struct scene_package_s {
        eng::SceneManager &scenes;
        eng::GraphicSystems &graphic;
        eng::PhysicSystems &physic;
        eng::AudioSystems &audio;
        eng::SuperInput &input;
        eng::TextureManager &texture;
    } scene_package_t;

class AScene : public IScene {
    public:
        AScene(scene_package_t pack): _scenes(pack.scenes),
        _graphic(pack.graphic), _audio(pack.audio), _physic(pack.physic),
        _input(pack.input), _texture(pack.texture)
        {}
        ~AScene() {}
    protected:
        eng::SceneManager &_scenes;
        eng::GraphicSystems &_graphic;
        eng::PhysicSystems &_physic;
        eng::AudioSystems &_audio;
        eng::SuperInput &_input;
        eng::TextureManager &_texture;
};

class GameScene : public AScene {
    public:
        GameScene(scene_package_t pack): AScene(pack)
        {}
        ~GameScene() {}

        void setupScene() {
            auto &reg = _scenes.getAttachedTopRegistry();
            reg.registerComponents(eng::SparseArray<eng::Position>());
            reg.registerComponents(eng::SparseArray<eng::Velocity>());
            reg.registerComponents(eng::SparseArray<eng::Drawable>());
            reg.registerComponents(eng::SparseArray<eng::Writable>());
        
            auto text = reg.spawnEntity();
            reg.addComponent(text, eng::Writable("GameText", "Welcome to "
            "the EngineCoreSuper demo game\nTo exit the game, press esc or "
            "B on your controller"));
            reg.addComponent(text, eng::Position(20, 20, 0));
        }

        void systemRun() {
            _input.updateEvents();
            if (_input.isActionJustReleased("ui_quit")) {
                // keep a variable if you want to pop two times
                auto &refscene = _scenes;
                refscene.pop();
                refscene.pop();
                // always return after a pop
                return;
            }
            if (_input.isActionJustReleased("ui_back")) {
                _scenes.pop();
                return;
            }
            _graphic.clear(sf::Color(0, 0, 50, 255));
            _graphic.drawSystem(_scenes.getAttachedTopRegistry());
            _graphic.writeSystem(_scenes.getAttachedTopRegistry());
            _graphic.display();
        }
    private:
};

class MenuScene : public AScene {
    public:
        MenuScene(scene_package_t pack): AScene(pack)
        {}
        ~MenuScene() {}

        void setupScene() {
            auto &reg = _scenes.getAttachedTopRegistry();
            reg.registerComponents(eng::SparseArray<eng::Position>());
            reg.registerComponents(eng::SparseArray<eng::Velocity>());
            reg.registerComponents(eng::SparseArray<eng::Drawable>());
            reg.registerComponents(eng::SparseArray<eng::Writable>());

            auto text = reg.spawnEntity();
            reg.addComponent(text, eng::Writable("MenuText", "Welcome to "
            "the EngineCoreSuper demo menu\nTo go to the game, press space or "
            "A on your controller\n press esc. or B on your controller to "
            "exit the app"));
            reg.addComponent(text, eng::Position(20, 20, 0));
        }
        void systemRun() {
            _input.updateEvents();
            if (_input.isActionJustReleased("ui_quit")) {
                _scenes.pop();
                // always return after a pop
                return;
            }
            if (_input.isActionJustReleased("ui_next"))
                _scenes.push(new GameScene(scene_package_t{_scenes, _graphic, _physic, _audio, _input, _texture}));
            _graphic.clear();
            _graphic.drawSystem(_scenes.getAttachedTopRegistry());
            _graphic.writeSystem(_scenes.getAttachedTopRegistry());
            _graphic.display();
        }
};

void setupInputs(eng::SuperInput &inputs)
{
    inputs.addAction("ui_next");
    inputs.addAction("ui_quit");
    inputs.addAction("ui_back");

    inputs.addEvent("ui_quit", eng::SuperInput::Key::escape);
    inputs.addEvent("ui_quit", eng::SuperInput::JoyButton::b, 0);

    inputs.addEvent("ui_back", eng::SuperInput::Key::enter);
    inputs.addEvent("ui_back", eng::SuperInput::JoyButton::x, 0);

    inputs.addEvent("ui_next", eng::SuperInput::Key::space);
    inputs.addEvent("ui_next", eng::SuperInput::JoyButton::a, 0);
}

int main(void)
{
    eng::RegistryManager registries;
    eng::SceneManager scenes(registries);
    eng::GraphicSystems gfx(1920, 1080, "EngineCoreSuper - Demo");
    eng::AudioSystems sfx;
    eng::PhysicSystems physics(gfx.getDeltaSeconds());
    eng::SuperInput inputs(gfx.getRenderWindow());
    eng::TextureManager textures;

    setupInputs(inputs);
    scenes.push(new MenuScene(scene_package_t{scenes, gfx, physics, sfx, inputs, textures}));
    while (gfx.isWindowOpen() && !scenes.empty())
        scenes.top().systemRun();
    return (0);
}