#pragma once
#include <memory>

class Scene;

class Objective
{
public:
    using Ptr = std::unique_ptr<Objective>;

    enum Type
    {
        DestroyTheConvoy = 0,
        RobTheMerchantShip,

        Count
    };

    Objective(Scene* scene);
    virtual ~Objective() = default;

    virtual void check() = 0;

    bool isCompleted() const;

protected
:
    Scene* m_scene = nullptr;
    bool m_completed = false;
};