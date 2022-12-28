#include <Data.hpp>

class InputBox
{
private:
    sf::RectangleShape background;
    sf::Text title, num;
    int inp;
    bool focus;
public:
    InputBox();
    void setPosition(float x, float y);
    void setTitle(std::string s);
    bool isMouseInside(int x, int y);
    void setFocus(bool isFocus);
    bool addDigit(int d);
    void typing(sf::Keyboard::Key code);
    bool pop();
    sf::RectangleShape getBackground();
    sf::Text getTitle();
    sf::Text getNum();
    int getValue();
};