#pragma once
#include "Scene.hpp"
#include "Visual/Mesh.hpp"

class MainMenu : public Scene
{
public:
    MainMenu(Game* game);
    ~MainMenu() = default;

    void update(float dt) override final;
    void draw() override final;

private:
    Mesh m_mesh;
};