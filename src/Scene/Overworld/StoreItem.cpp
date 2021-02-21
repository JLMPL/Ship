#include "StoreItem.hpp"

StoreItem::StoreItem()
{
    m_mesh.loadFromFile("data/meshes/shotgun_item.obj");
    m_font.loadFromFile("data/fonts/DejaVuSans.ttf");

    m_name.setFont(m_font);
    m_name.setCharacterSize(25);
    m_name.setString(L"$2Blaster Shotgun");

    m_description.setFont(m_font);
    m_description.setCharacterSize(20);
    m_description.setString(L"$0Shoots a wide cone of bolts covering a large area.\nVery effective at short distance.");

    m_priceText.setFont(m_font);
    m_priceText.setCharacterSize(25);
    m_priceText.setString(L"$6$ 1500");
}

void StoreItem::setData(const std::wstring& name, const std::wstring& desc, int price)
{
    m_name.setString(L"$2" + name);
    m_name.setOrigin({0, m_name.getSize().y/2});
    m_description.setString(desc);
    m_description.setOrigin({0, m_description.getSize().y/2});
    m_priceText.setString(L"$6$ " + std::to_wstring(price));
    m_priceText.setOrigin({0, m_priceText.getSize().y/2});

    setPosition(m_pos);
}

void StoreItem::update()
{

}

void StoreItem::draw()
{
    m_mesh.draw(false);
    m_name.draw();
    m_description.draw();
    m_priceText.draw();
}

void StoreItem::setPosition(const vec2& pos)
{
    m_pos = pos;

    m_mesh.setScale(m_size.y);
    m_mesh.setPosition(m_pos);

    m_name.setPosition({m_pos.x + m_size.y, m_pos.y + (m_size.y/4)});
    m_description.setPosition({m_pos.x + m_size.y, m_pos.y + (m_size.y/1.5)});
    m_priceText.setPosition({m_pos.x + m_size.x - m_priceText.getSize().x - (m_size.y*0.5), m_pos.y + (m_size.y/2)});
}

void StoreItem::setSize(const vec2& size)
{
    m_size = size;
    setPosition(m_pos);
}