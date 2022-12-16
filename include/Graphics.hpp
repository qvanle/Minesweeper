#include <Data.hpp>

namespace Graphics
{
    class Button
    {
    private:
        sf::Texture image;
        sf::Vector2f position;
    public:
        int getW();
        int getH();
        Button();
        Button(std::string link);
        sf::Sprite getSprite();
        sf::Sprite getSprite(float x, float y);
        void setImage(std::string);
    };

    namespace StartingScreen
    {
        void Draw();
    }

    void INIT();
    void RunGraphics();
}
