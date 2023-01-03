/*
this library help you create an input box that let user input a number
*/

#include "Data.hpp"

class InputBox
{
private:
    sf::RectangleShape background; // background of input area
    sf::Text title, num; // title and user input (which use to be printed to the screen)
    int inp; // value of num
    bool focus; // focus = true if this box is select 
                // focus = false if this box is not select
                // if mouse have click into input area, focus = true, otherwise, focus = false
public:
    InputBox(); // construction
    void setPosition(float x, float y); // set position of background which have position of top left corner is (x, y)
                                        // and align title and num.
    void setTitle(std::string s); // title of the box
    bool isMouseInside(int x, int y); // check if a mouse inside the box or not
    void setFocus(bool isFocus); // change focus status
    bool addDigit(int d); // add a digit to the end of inp
    void typing(sf::Keyboard::Key code); // user typed 
    void setRange(int Lower, int Upper); // set minimum and maximum value of inp
    bool pop(); // erase the last digit of inp
    sf::RectangleShape getBackground(); // get the background of the box
    sf::Text getTitle(); // get the title of the box
    sf::Text getNum(); // get the num of the box
    int getValue(); // get inp of the box
};