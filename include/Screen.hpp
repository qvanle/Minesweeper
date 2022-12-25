#include <INIT.hpp>
#include <Button.hpp>

class Screen
{
private:
    int id, maxScrolls, scrolls;
    sf::Texture background, title;
    std::vector<Button> buttons; // function button

public:
    void setID(int i);
    int getID();

    bool isVisible(int id);
    void setVisible(int id, bool visible);
    
    bool isButtonVisible(int id);
    void changeButtonVisible(int id, bool show);

    void setMaxScrolls(int k);
    int getMaxScrolls();

    bool scrolling(int k);
    int getScrolls();

    void addBackground(std::string link);
    sf::Sprite getBackground();
    
    void setButtonScreenID(int id, int key);
    void addButton(std::string link);
    void addButton(std::string link, int x, int y);
    void addButtonTexture(std::string link, int id);
    void setButtonPos(int id, float x, float y);
    int buttonsSize();
    int ButtonW(int id);
    int ButtonH(int id);
    sf::Sprite getButton(int id);

    void MouseChangeStatus(int x, int y);
    int MouseChangeScreen(int x, int y);

    sf::Sprite getTitle();
    void addTitle(std::string link);
};