#pragma once
#include "Scene.hpp"

class MainMenu : public Scene
{
public:
    MainMenu(Game* game);
    ~MainMenu() = default;

    void update(float dt) override final;

private:
};