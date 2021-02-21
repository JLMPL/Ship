#pragma once
#include "Visual/Mesh.hpp"
#include "Scene/UI/Label.hpp"

class StoreItem
{
public:
    StoreItem();

    void update();
    void draw();

    void setData(const std::wstring& name, const std::wstring& desc, int price);
    void setPosition(const vec2& pos);
    void setSize(const vec2& size);

private:
    sf::Font m_font;
    Mesh m_mesh;
    Label m_name;
    Label m_description;
    Label m_priceText;

    int m_price = 100;
    vec2 m_pos;
    vec2 m_size = {100,100};
};