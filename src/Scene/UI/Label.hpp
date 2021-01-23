#pragma once
#include "Core/Math.hpp"
#include "Libs/RichText/RichText.hpp"

#define LB_WHITE  (L"$0")
#define LB_BLACK  (L"$1")
#define LB_RED    (L"$2")
#define LB_GREEN  (L"$3")
#define LB_BLUE   (L"$4")
#define LB_YELLOW (L"$5")
#define LB_PURPLE (L"$6")

class Label
{
public:
    void setFont(sf::Font& font);
    void setCharacterSize(int size);
    void setString(const std::wstring& text);
    void setPosition(const vec2& pos);
    void setOrigin(const vec2& origin);
    vec2 getSize() const;

    void draw();
    void clear();

private:
    sfe::RichText m_front;
    sfe::RichText m_shadow;
};