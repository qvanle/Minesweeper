#include <Data.hpp>

class Button
{
private:
    std::vector<sf::Texture> image;
    int status = 0;
    sf::Vector2f position;
    
public:
    
    int getW();
    int getH();
    Button();
    Button(std::string link);
    sf::Sprite getSprite();
    sf::Sprite getSprite(float x, float y);
    sf::Sprite getSprite(float x, float y, float c);
    void addImage(std::string link);
    bool isMouseInside(float x, float y);
    void setStatus(int value);
    int getStatus();
};