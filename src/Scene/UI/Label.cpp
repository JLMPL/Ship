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
    clear();
    m_front << sf::Color::White;
    std::wstring word = L"";

    for (int i = 0; i < text.size(); i++)
    {
        if (text[i] == '$')
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
                    m_front << sf::Color::Green;
                    break;
                case '4':
                    m_front << sf::Color::Blue;
                    break;
                case '5':
                    m_front << sf::Color::Yellow;
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
        }
        else
            word += text[i];
    }
}

void Label::setPosition(const vec2& pos)
{
    m_front.setPosition(pos);
    m_shadow.setPosition(pos + vec2(2,2));
}

void Label::draw()
{
    Renderer::get().draw(m_shadow);
    Renderer::get().draw(m_front);
}

void Label::clear()
{
    m_front.clear();
    m_shadow.clear();
}

void Label::setOrigin(const vec2& origin)
{
    m_front.setOrigin(origin);
    m_shadow.setOrigin(origin);
}