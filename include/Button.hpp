/*
this library help you to create buttons
*/
#include <Data.hpp>

class Button
{
private:
    std::vector<sf::Texture> image; // textures of button
    int status = 0; // current texture
    sf::Vector2f position; // position of Button
    
public:
    
    int getW(); // get width of the current texture
    int getH(); // get height of the current texture
    Button(); // construction
    Button(std::string link); // construction (add a new texture)
    sf::Sprite getSprite(); // get sprite of current texture 
    sf::Sprite getSprite(float x, float y); // get sprite of current texture and change it's position to (x, y)
    sf::Sprite getSprite(float x, float y, float c); // get sprite of current texture, change it's position to (x, y) and scaling the texture
    void addImage(std::string link); // add new texture
    bool isMouseInside(float x, float y); // return true if mouse position is inside button area
    void setStatus(int value); // change texture
    int getStatus(); // get the id of current texture
    void setPosition(float x, float y); // change position of button to (x, y)
};