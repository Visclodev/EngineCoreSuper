/*
** EPITECH PROJECT, 2022
** EngineCoreSuper
** File description:
** main
*/

#include <EngineCoreSuper/EngineCoreSuper.hpp>

class Player{
    public:
        Player(std::string name_, int health_):
        name(name_), health(health_)
        {}
        ~Player()
        {}
        std::string name;
        int health;
    private:
};

void print_infos(eng::Registry &reg, eng::Entity &baba)
{
    std::cout << reg.getComponents<Player>()[baba.getId()].value().name << " has ";
    std::cout << reg.getComponents<Player>()[baba.getId()].value().health;
    std::cout << " health points!" << std::endl;

    std::cout << "He is at: {" << reg.getComponents<eng::Position>()[baba.getId()].value().x;
    std::cout << ", " << reg.getComponents<eng::Position>()[baba.getId()].value().y;
    std::cout << "}" << std::endl;
}

void addText(eng::Registry &r)
{
    eng::Entity text = r.spawnEntity();

    r.emplaceComponent(text, eng::Position(300, 1080 / 2, 0));
    r.emplaceComponent(text, eng::Writable("escape_text", "Press esc. key to exit"));
}

void addParticleEmmiter(eng::Registry &r, int screenWidth, int screenHeight)
{
    eng::Entity particles = r.spawnEntity();
    int x = screenWidth / 2;
    int y = screenHeight / 2;

    r.emplaceComponent(particles, eng::Position(x, y, 0));
    std::cout << "emplaced position in registry" << std::endl;
    r.emplaceComponent(particles, eng::ParticleEmitter());
    std::cout << "emplaced particle emitter in registry" << std::endl;
    auto &emitter = r.getComponents<eng::ParticleEmitter>()[particles.getId()].value();
    
    emitter.setParticleTexture(eng::PARTICLE_TYPE::Pixel);
    emitter.setBaseSpeed(1);
    emitter.setBaseRotation(160, 200);
    emitter.setEmittingRate(0.01);
    emitter.setAcceleration(150);
    emitter.setMaxNumber(100);
    emitter.setParticleColor(sf::Color::Yellow);
    emitter.isLocal = false;
}

int main(void)
{
    eng::RegistryManager r;
    r.addRegistry("Registry one");
    auto reg = r.getTop();
    eng::Entity baba = reg.spawnEntity();
    eng::GraphicSystems gfx(1920, 1080, "Coucou");
    gfx.setFrameRateLimit(60);

    reg.registerComponents(eng::SparseArray<Player>());
    reg.registerComponents(eng::SparseArray<eng::Position>());
    reg.registerComponents(eng::SparseArray<eng::Drawable>());
    reg.registerComponents(eng::SparseArray<eng::Writable>());
    reg.registerComponents(eng::SparseArray<eng::ParticleEmitter>());
    reg.emplaceComponent(baba, Player("baba", 56));
    reg.emplaceComponent(baba, eng::Position(13, 13, 0));
    reg.emplaceComponent(baba, eng::Drawable("../assets/logo.png"));
    addText(reg);
    addParticleEmmiter(reg, 1920, 1080);

    print_infos(reg, baba);

    while (gfx.isWindowOpen()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            gfx.getRenderWindow().close();
        gfx.clear();
        gfx.drawSystem(reg);
        gfx.writeSystem(reg);
        gfx.particleSystem(reg);
        gfx.display();
    }
    return (0);
}
