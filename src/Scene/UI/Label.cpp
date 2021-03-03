#include "Label.hpp"
#include "Renderer.hpp"

void Label::setFont(sf::Font& font)
{
    m_front.setFont(font);
    m_shadow.setFont(font);
    m_front << sf::Color::White;
    m_shadow << sf::Color::Black;
}

void Label::setCharacterSize(int size)
{
    m_front.setCharacterSize(size);
    m_shadow.setCharacterSize(size);
}

void Label::setString(const std::wstring& text)
{
    m_str.clear();
    clear();
    m_front << sf::Color::White;
    std::wstring word = L"";

    for (int i = 0; i < text.size(); i++)
    {
        if (text[i] == '$' && std::iswdigit(text[i+1]))
        {
            m_front << word;
            m_shadow << word;
            word.clear();
            wchar_t color = text[i+1];

            sf::Color chosenOne = sf::Color::White;

            switch (color)
            {
                case '0':
                    m_front << sf::Color::White;
                    break;
                case '1':
                    m_front << sf::Color::Black;
                    break;
                case '2':
                    m_front << sf::Color::Red;
                    break;
                case '3':
                    m_front << sf::Color(0,192,0);
                    break;
                case '4':
                    m_front << sf::Color::Blue;
                    break;
                case '5':
                    m_front << sf::Color::Yellow;
                    break;
                case '6':
                    m_front << sf::Color(128 * 1.1f,0,192 * 1.1f);
                    break;
                case '7':
                    m_front << sf::Color(128,128,128);
                    break;
                default: break;
            }

            i++;
        }
        else if (i == (text.size()-1))
        {
            word += text[i];
            m_front << word;
            m_shadow << word;
            m_str += word;
        }
        else
            word += text[i];
    }
}

void Label::setPosition(const vec2& pos)
{
    vec2 posi(int(pos.x), int(pos.y));
    m_front.setPosition(posi);
    m_shadow.setPosition(posi + vec2(2,2));
}

void Label::draw()
{
    Renderer.draw(m_shadow);
    Renderer.draw(m_front);
}

void Label::clear()
{
    m_front.clear();
    m_shadow.clear();
}

void Label::setOrigin(const vec2& origin)
{
    vec2 origini(int(origin.x), int(origin.y));
    m_front.setOrigin(origini);
    m_shadow.setOrigin(origini);
}

vec2 Label::getSize() const
{
    return {m_front.getLocalBounds().width, m_front.getLocalBounds().height};
}

void Label::setColor(const sf::Color& color)
{
    clear();
    m_front << color << m_str;
    m_shadow << m_str;
}