#include <Screen.hpp>
#include <GraphicsVariables.hpp>

void Screen::setID(int i)
{
    Screen::id = i;
}

int Screen::getID()
{
    return Screen::id;
}

bool Screen::isVisible(int id)
{
    return buttons[id].isVisible();
}

void Screen::setVisible(int id, bool visible)
{
    buttons[id].setVisible(visible);
}

void Screen::addBackground(std::string link)
{
    Screen::background.loadFromFile(link);
    return ;
}

void Screen::setMaxScrolls(int k)
{
    Screen::maxScrolls = k;
}
int Screen::getMaxScrolls()
{
    return Screen::maxScrolls;
}

bool Screen::scrolling(int k)
{
    k *= -1;
    if((Screen::scrolls == 0 && k < 0) || (Screen::scrolls == maxScrolls && k > 0))
        return false;
    else if(Screen::scrolls + k < 0)
        Screen::scrolls = 0;
    else if(Screen::scrolls + k > maxScrolls)
        Screen::scrolls = maxScrolls;
    else Screen::scrolls += k;
    return true;
}
int Screen::getScrolls()
{
    return Screen::scrolls;
}

sf::Sprite Screen::getBackground()
{
    sf::Sprite temp(Screen::background);
    double scaleX = GraVar::WIDTH / (double) Screen::background.getSize().x;
    double scaleY = GraVar::HEIGHT / (double) Screen::background.getSize().y;
    temp.setScale(scaleX, scaleY);
    return temp;
}

void Screen::setButtonScreenID(int id, int key)
{   
    Screen::buttons[id].setScreenID(key);
}

void Screen::addButton(std::string link)
{
    Screen::buttons.emplace_back();
    Screen::buttons.back().addImage(link);
    Screen::buttons.back().setPosition(0, 0);
}

void Screen::addButton(std::string link, int x, int y)
{
    Screen::buttons.emplace_back();
    Screen::buttons.back().addImage(link);
    Screen::buttons.back().setPosition(x, y);
    Screen::buttons.back().setScreenID(Screen::id);
}

void Screen::addButtonTexture(std::string link, int id)
{
    if(id >= (int) Screen::buttons.size()) return ;
    Screen::buttons[id].addImage(link);
    return ;
}

void Screen::setButtonPos(int id, float x, float y)
{
    if(id >= (int) Screen::buttons.size()) return ;
    Screen::buttons[id].setPosition(x, y);
}

int Screen::buttonsSize()
{
    return Screen::buttons.size();
}
int Screen::ButtonW(int id)
{
    return Screen::buttons[id].getW();
}

int Screen::ButtonH(int id)
{
    return Screen::buttons[id].getH();
}

sf::Sprite Screen::getButton(int id)
{
    return Screen::buttons[id].getSprite();
}

void Screen::MouseChangeStatus(int x, int y)
{
    int n = Screen::buttonsSize();

    for(int i = 0; i < n; i++)
        if(buttons[i].isVisible())
        {
            buttons[i].isMouseInside(x, y);
        }
}

int Screen::MouseChangeScreen(int x, int y)
{
    int n = Screen::buttonsSize();
    for(int i = n - 1; i >= n - 6 && i >= 0; i--)
    {
        if(buttons[i].isVisible() && Screen::buttons[i].isMouseInside(x, y))
        {
            Screen::buttons[i].setStatus(0);
            return buttons[i].getScreenID();
        }
    }
    return Screen::id;
}

sf::Sprite Screen::getTitle()
{
    sf::Vector2u size = title.getSize();
    sf::Vector2f pos = sf::Vector2f((GraVar::WIDTH - size.x) / 2.0, 120);

    sf::Sprite temp(Screen::title);
    temp.setPosition(pos);
    return temp;
}
void Screen::addTitle(std::string link)
{
    Screen::title.loadFromFile("data/title/header.png");
    return ;
}