#include <INIT.hpp>

class Button
{
private:
    std::vector<sf::Texture> image;
    int status = 0;
    sf::Vector2f position;
    int ScreenID;
    bool invisible;
public:
    bool isVisible();
    void setVisible(bool visible);
    int getW();
    int getH();
    
    Button();
    Button(std::string link);
    
    sf::Sprite getSprite();
    sf::Sprite getSprite(float c);
    sf::Sprite getSprite(float x, float y);
    sf::Sprite getSprite(float x, float y, float c);

    void addImage(std::string link);
    
    bool isMouseInside(float x, float y);
    
    void setStatus(int value);
    int getStatus();
    
    void setPosition(float x, float y);
    
    void setScreenID(int i);
    int getScreenID();
};
