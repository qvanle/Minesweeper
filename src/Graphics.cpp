#include <Graphics.hpp>

std::vector<sf::Texture> GraphicsData::icons;
const int GraphicsData::Width = 800;
const int GraphicsData::Height = 565;

void GraphicsData::LoadTextures()
{
    std::vector<sf::Texture> icons;
    icons.resize(12);
    for(int i = 0; i < 12; i++)
    {
        std::string direct = "data/icons/" + std::to_string(i) + ".png";
        if(!icons[i].loadFromFile(direct));
    }
}

void Graphics::RunGraphics()
{
    sf::RenderWindow app(sf::VideoMode(GraphicsData::Width, GraphicsData::Height), "Minesweeper", sf::Style::Close);  
    GraphicsData::LoadTextures();
    
    while(app.isOpen())
    {
        sf::Event e;
        while(app.pollEvent(e))
        {
            switch (e.type)
            {
                case sf::Event::Closed:
                    app.close();
                    break;
            }
        }
        app.clear();
        app.display();
    }    
}