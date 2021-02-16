#include "MainMenu.hpp"
#include "StarBackground.hpp"
#include "Game.hpp"
#include "Menu.hpp"
#include "Overworld.hpp"
#include "Overworld/GameplayVars.hpp"

MainMenu::MainMenu(Game* game)
 : Scene(game)
{
    m_objects.emplace_back(new StarBackground(this));
    m_objects.emplace_back(new Menu(this));

    auto menu = (Menu*)m_objects.back().get();

    menu->addItem(L"Start Game", [&]()
    {
        m_game->changeScene(new Overworld(game));
    });
    menu->addItem(L"Tutorials: ON", [&]()
    {
        TutorialsEnabled = !TutorialsEnabled;
    });
    menu->addItem(L"Quit", [&]()
    {
        m_game->changeScene(nullptr);
    });

    ready();
}

void MainMenu::update(float dt)
{
    auto menu = (Menu*)m_objects.back().get();

    if (TutorialsEnabled)
        menu->setCaption(1, L"Tutorials: ON");
    else
        menu->setCaption(1, L"Tutorials: $7OFF");

    Scene::update(dt);
}