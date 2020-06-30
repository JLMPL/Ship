#pragma once
#include "Core/Types.hpp"
#include <memory>

class LayerStack;

class Layer
{
public:
    using Ptr = std::unique_ptr<Layer>;

    enum class Type
    {
        MainMenu,
        Settings,
        Game,
        Credits,
        Pause,
        Background,
        Hud,

        None
    };

    template <typename T>
    T* as() { return static_cast<T*>(this); }

    Layer(LayerStack& layerStack) :
        m_layerStack(layerStack)
    {}

    virtual ~Layer() = default;

    virtual void update(float dt) = 0;
    virtual void draw() = 0;

protected:
    LayerStack& m_layerStack;
};