#include "Overworld.hpp"
#include "Random.hpp"

#include "Overworld/Drone.hpp"
#include "Overworld/Player.hpp"
#include "Overworld/Hud.hpp"
#include "Overworld/Objective.hpp"
#include "Overworld/PauseMenu.hpp"
#include "Overworld/Planet.hpp"
#include "Overworld/Store.hpp"
#include "Overworld/GameOver.hpp"
#include "Overworld/Cutscene.hpp"
#include "StarBackground.hpp"
#include "Tutorial.hpp"

#include "MainMenu.hpp"
#include "Game.hpp"

Overworld::Overworld(Game* game)
 : Scene(game)
{
    m_objects.emplace_back(new StarBackground(this));

    for (int i = 0; i < 1000; i++)
    {
        m_objects.emplace_back(new Planet(this));
    }

    m_objects.emplace_back(new Player(this));

    m_objects.emplace_back(new Objective(this));
    m_objects.emplace_back(new Hud(this));

    m_objects.emplace_back(new PauseMenu(this));
    m_objects.emplace_back(new Store(this));

    m_objects.emplace_back(new Tutorial(this));
    m_objects.emplace_back(new GameOver(this));

    m_objects.emplace_back(new Cutscene(this));

    ready();

    // findObject<GameOver>("game_over")->show();
}

void Overworld::goToMainMenu()
{
    m_game->changeScene(new MainMenu(m_game));
}