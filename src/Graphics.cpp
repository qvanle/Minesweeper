#include <Graphics.hpp>
//declare variable

std::vector<sf::Texture> GraphicsData::icons;
sf::Font GraphicsData::font;
int GraphicsData::WIDTH = 1200;
int GraphicsData::HEIGHT = 700;;
sf::RenderWindow GraphicsData::screen(sf::VideoMode(GraphicsData::WIDTH, GraphicsData::HEIGHT), "Minesweeper", sf::Style::Close);  

void GraphicsData::INIT()
{
    icons.resize(12);
    for(int i = 0; i < 12; i++)
    {
        std::string direct = "data/icons/ocean/" + std::to_string(i) + ".jpg";
        if(!icons[i].loadFromFile(direct));
    }
    GraphicsData::font.loadFromFile("data/font/lemon_jelly/font.ttf");
}

Graphics::Button::Button(std::string link)
{
    Graphics::Button::image.loadFromFile(link);
}
sf::Sprite Graphics::Button::getSprite()
{
    Graphics::Button::position = sf::Vector2f(0, 0);
    return sf::Sprite(Graphics::Button::image);
}
int Graphics::Button::getW()
{
    return Graphics::Button::image.getSize().x;
}
int Graphics::Button::getH()
{
    return Graphics::Button::image.getSize().y;
}
sf::Sprite Graphics::Button::getSprite(float x, float y)
{

    Graphics::Button::position = sf::Vector2f(x, y);
    sf::Sprite temp(Graphics::Button::image);
    temp.setPosition(x, y);
    return temp;
}
void Graphics::StartingScreen::Draw()
{
    // draw background picture
    sf::Texture textureBackground;
    textureBackground.loadFromFile("data/background/ocean/startingscreen.jpg");   
    sf::Sprite spriteBackground(textureBackground);
    spriteBackground.setScale(0.3893f, 0.30948f);
    GraphicsData::screen.draw(spriteBackground);

    const int shilfButVer = 0;
    const int shilfButHor = 150;

    //draw "logo"
    sf::Texture logoTexture;
    logoTexture.loadFromFile("data/title/title.png");
    sf::Vector2u logoSize = logoTexture.getSize();

    sf::Vector2f logoPosition = sf::Vector2f((GraphicsData::WIDTH - logoSize.x) / 2.0, 120);

    sf::Sprite logo(logoTexture);
    logo.setPosition(logoPosition);
    GraphicsData::screen.draw(logo);

    // draw "play" button
    Button play("data/button/start_screen/play.png");
    GraphicsData::screen.draw(play.getSprite(GraphicsData::WIDTH / 2 - play.getW() / 2 + shilfButVer, 
                                             GraphicsData::HEIGHT / 2 - 2 * play.getH() + shilfButHor));
    

    // draw "tutorial" button
    Button tutorial("data/button/start_screen/tutorial.png");
    
    GraphicsData::screen.draw(tutorial.getSprite(GraphicsData::WIDTH / 2 - tutorial.getW() / 2 + shilfButVer,
                                             GraphicsData::HEIGHT / 2 - tutorial.getH() / 2 + shilfButHor));
    
    // draw "high score" button
    Button highScore("data/button/start_screen/high_score.png");
    GraphicsData::screen.draw(highScore.getSprite(GraphicsData::WIDTH / 2 - highScore.getW() / 2 + shilfButVer,
                                             GraphicsData::HEIGHT / 2 + highScore.getH() + shilfButHor));
    

}

void Graphics::RunGraphics()
{
    GraphicsData::INIT();

    while(GraphicsData::screen.isOpen())
    {
        GraphicsData::screen.clear(sf::Color::White);    
        Graphics::StartingScreen::Draw();
        GraphicsData::screen.display();

        sf::Event e;

        while(GraphicsData::screen.pollEvent(e))
        {
            switch (e.type)
            {
            case sf::Event::Closed:
                GraphicsData::screen.close();
                break;
            
            default:
                break;
            }
        }
    }    
}
