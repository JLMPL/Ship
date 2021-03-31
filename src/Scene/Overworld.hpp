#pragma once
#include "Scene.hpp"

class Overworld : public Scene
{
public:
    Overworld(Game* game);
    ~Overworld() = default;

    void goToMainMenu();
private:
};