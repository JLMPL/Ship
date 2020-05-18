#pragma once
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
        Gameplay,
        Credits,
        Pause,
        Background,

        None
    };

    Layer(LayerStack& layerStack) :
        m_layerStack(layerStack)
    {}

    virtual ~Layer() = default;

    virtual void update(float dt) = 0;
    virtual void draw() = 0;

protected:
    LayerStack& m_layerStack;
};