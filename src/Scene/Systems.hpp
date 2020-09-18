#pragma once
#include <memory>

class Scene;

void healthSystemRegisterEntity(Scene* scene, int id);
void healthSystemUpdate(Scene* scene);

void physicsSystemUpdate(Scene* scene);