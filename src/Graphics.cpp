#include <Graphics.hpp>
//declare variable

sf::Font GraphicsData::font;
int GraphicsData::WIDTH = 1200;
int GraphicsData::HEIGHT = 700;
sf::RenderWindow GraphicsData::screen(sf::VideoMode(GraphicsData::WIDTH, GraphicsData::HEIGHT), "Minesweeper", sf::Style::Close);  


void GraphicsData::INIT()
{
    GraphicsData::font.loadFromFile("data/font/lemon_jelly/font.ttf");
}

Graphics::Button::Button()
{
    Graphics::Button::status = 0;
}

Graphics::Button::Button(std::string link)
{
    Graphics::Button::status = 0;
    sf::Texture temp;
    temp.loadFromFile(link);
    Graphics::Button::image.push_back(temp);
}

void Graphics::Button::addImage(std::string link)
{
    sf::Texture temp;
    temp.loadFromFile(link);
    Graphics::Button::image.push_back(temp);
}

sf::Sprite Graphics::Button::getSprite()
{
    Graphics::Button::position = sf::Vector2f(0, 0);
    return sf::Sprite(Graphics::Button::image[Graphics::Button::status]);
}

int Graphics::Button::getW()
{
    return Graphics::Button::image[Graphics::Button::status].getSize().x;
}

int Graphics::Button::getH()
{
    return Graphics::Button::image[Graphics::Button::status].getSize().y;
}

sf::Sprite Graphics::Button::getSprite(float x, float y)
{
    Graphics::Button::position = sf::Vector2f(x, y);
    sf::Sprite temp(Graphics::Button::image[Graphics::Button::status]);
    temp.setPosition(x, y);
    return temp;
}

sf::Sprite Graphics::Button::getSprite(float x, float y, float c)
{
    Graphics::Button::position = sf::Vector2f(x, y);
    sf::Sprite temp(Graphics::Button::image[Graphics::Button::status]);
    temp.setPosition(x, y);
    temp.scale(c, c);
    return temp;
}

bool Graphics::Button::isMouseInside(float x, float y)
{
    if(x < Graphics::Button::position.x || x > Graphics::Button::position.x + Graphics::Button::getW())
    {
        Graphics::Button::status = 0;
        return 0;
    }
    if(y < Graphics::Button::position.y || y > Graphics::Button::position.y + Graphics::Button::getH())
    {
        Graphics::Button::status = 0;    
        return 0;
    }

    Graphics::Button::status = 1;
    return 1;
}

void Graphics::Button::setStatus(int value)
{
    Graphics::Button::status = value;
}

void Graphics::delay(int t)
{
    sf::Clock clock;
    sf::Time start = clock.getElapsedTime();
    while(clock.getElapsedTime() - start < sf::milliseconds(t));
    return ;
}   

int Graphics::Button::getStatus()
{
    return Graphics::Button::status;
}

namespace DeadScreen
{
    const int shilfButVer = 0; // shilf button vertical
    const int shilfButHor = -80; // shilf button horizonal

    sf::Texture textureBackground, logoTexture, titleTexture;
    sf::Sprite spriteBackground;
    sf::Vector2u logoSize, titleSize;
    sf::Vector2f logoPosition, titlePosition;
    sf::Sprite logo, title;
    
    Graphics::Button goback, highScore;

    void draw()
    {
        GraphicsData::screen.draw(spriteBackground);
        GraphicsData::screen.draw(title);

        // draw "high score" button
        GraphicsData::screen.draw(highScore.getSprite(GraphicsData::WIDTH / 2 - highScore.getW() / 2 + shilfButVer,
                                                GraphicsData::HEIGHT / 2 + highScore.getH() / 2 + shilfButHor));
        // draw "go back" button
        GraphicsData::screen.draw(goback.getSprite(GraphicsData::WIDTH / 2 - goback.getW() / 2 + shilfButVer,
                                                GraphicsData::HEIGHT / 2 + 2 * goback.getH() + shilfButHor));
    }
    
    void INIT()
    {
        textureBackground.loadFromFile("data/background/ocean/darkocean.jpg");   
        spriteBackground.setTexture(textureBackground);


        logoTexture.loadFromFile("data/title/header.png");
        logoSize = logoTexture.getSize();
        logoPosition = sf::Vector2f((GraphicsData::WIDTH - logoSize.x * 0.6) - 50, 50);
        logo.setTexture(logoTexture);
        logo.setScale(0.6, 0.6);
        logo.setPosition(logoPosition);


        titleTexture.loadFromFile("data/title/lose.png");
        titleSize = titleTexture.getSize();
        titlePosition = sf::Vector2f((GraphicsData::WIDTH - titleSize.x) / 2.0, (GraphicsData::HEIGHT - titleSize.y) / 2.0 - 200);
        title.setTexture(titleTexture);
        title.setPosition(titlePosition);

        goback.addImage("data/button/goback.png");
        goback.addImage("data/button/choosing_goback.png");

        highScore.addImage("data/button/high_score.png");
        highScore.addImage("data/button/choosing_high_score.png");
    }
    
    void mouseChangeStatus(int x, int y)
    {
        goback.isMouseInside(x, y);
        highScore.isMouseInside(x, y);
    }

    void Run()
    {
        INIT();
        while(GraphicsData::screen.isOpen())
        {
            GraphicsData::screen.clear(sf::Color::White);
            draw();
            GraphicsData::screen.display();

            sf::Event e;
            while(GraphicsData::screen.pollEvent(e))
            {
                switch(e.type)
                {
                    case sf::Event::Closed:
                        GraphicsData::screen.close();
                        break;
                    case sf::Event::MouseButtonPressed:
                        if(goback.isMouseInside(e.mouseButton.x, e.mouseButton.y))
                        {
                            goback.setStatus(0);
                            return ; 
                        }
                        break;
                    case sf::Event::MouseMoved:
                        mouseChangeStatus(e.mouseMove.x, e.mouseMove.y);
                }
            }
        }
    }
}

namespace WinningScreen
{

}

namespace GameScreen
{
    sf::Texture textureBackground, logoTexture;
    sf::Sprite spriteBackground;
    sf::Vector2u logoSize;
    sf::Vector2f logoPosition;
    sf::Sprite logo;

    std::vector<Graphics::Button> Tab;

    const int SHILF_DOWN = 50;
    const int SHILF_RIGHT = 50;
    const int ICON_WIDTH = 120;
    const int ICON_HEIGHT = 120;
    const float SCALE = 0.5;

    int px = 0;
    int py = 0;
    bool isDead = 0;
    
    int cellsLeft;
    int mineLeft;
    int flags;

    sf::RectangleShape horLine(sf::Vector2f(ICON_WIDTH * SCALE + 5 , 2.f));
    sf::RectangleShape verLine(sf::Vector2f(2.f, ICON_HEIGHT * SCALE + 5));
    sf::Color frameColor(60, 60, 60);

    void INIT(int n, int m, int k)
    {

        horLine.setFillColor(frameColor);
        verLine.setFillColor(frameColor);
        isDead = false;
        cellsLeft = n * m;
        mineLeft = k;
        flags = 0;

        BoardData::init(n, m, k);


        textureBackground.loadFromFile("data/background/ocean/darkocean.jpg");   
        spriteBackground.setTexture(textureBackground);

        logoTexture.loadFromFile("data/title/header.png");
        logoSize = logoTexture.getSize();
        logoPosition = sf::Vector2f((int)(GraphicsData::WIDTH - logoSize.x * 0.6) - 50, 50);


        logo.setTexture(logoTexture);
        logo.setScale(0.6, 0.6);
        logo.setPosition(logoPosition);

        Tab.clear();
        Tab.resize(n * m);

        for(int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int id = i * m + j;
                Tab[id].addImage("data/icons/ocean/12.png");
                Tab[id].addImage("data/icons/ocean/" + std::to_string(BoardData::Board[id]) + ".jpg");
                Tab[id].addImage("data/icons/ocean/9.jpg");
                Tab[id].addImage("data/icons/ocean/10.jpg");
            }
        }
    }

    void INIT(int x, int y)
    {

        int n = BoardData::Columns;
        int m = BoardData::Rows;
        int k = BoardData::Mines;
        
        isDead = false;
        cellsLeft = n * m;
        mineLeft = k;
        flags = 0;
        
        BoardData::init(n, m, k, x, y);

        Tab.clear();
        Tab.resize(n * m);

        for(int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int id = i * m + j;
                Tab[id].addImage("data/icons/ocean/12.png");
                Tab[id].addImage("data/icons/ocean/" + std::to_string(BoardData::Board[id]) + ".jpg");
                Tab[id].addImage("data/icons/ocean/9.jpg");
                Tab[id].addImage("data/icons/ocean/10.jpg");
            }
        }
    }

    void draw()
    {
        GraphicsData::screen.draw(spriteBackground);
        for(int i = 0; i <= 10; i++)
        {
            for(int j = 0; j <= 10; j++)
            {
                int id = (i + px) * BoardData::Columns + (j + py);
                
                if(i != 10 && j != 10)
                {
                    if(isDead && BoardData::Board[id] == BoardData::MineCell)
                        Tab[id].setStatus(1);
                    GraphicsData::screen.draw(Tab[id].getSprite(j * (1 + ICON_WIDTH * SCALE) + SHILF_RIGHT, 
                                                                i * (1 + ICON_HEIGHT * SCALE) + SHILF_DOWN, SCALE));
                }

                verLine.setPosition(j * (1 + ICON_WIDTH * SCALE) + SHILF_RIGHT - 2, 
                                    i * (1 + ICON_HEIGHT * SCALE) + SHILF_DOWN - 2);
                horLine.setPosition(j * (1 + ICON_WIDTH * SCALE) + SHILF_RIGHT - 2, 
                                    i * (1 + ICON_HEIGHT * SCALE) + SHILF_DOWN - 2);

                if(i != 10) GraphicsData::screen.draw(verLine);
                if(j != 10) GraphicsData::screen.draw(horLine);
            }
        } 
    }

    void openCells(int x, int y)
    {
        if(x < 0 || x >= BoardData::Rows) return ;
        if(y < 0 || y >= BoardData::Columns) return ;
        
        int id = x * BoardData::Columns + y;
        if(Tab[id].getStatus() == 1 || Tab[id].getStatus() == 2) return ; 
        Tab[id].setStatus(1);

        cellsLeft--;

        if(BoardData::Board[id] == BoardData::MineCell) isDead = true;
        if(BoardData::Board[id] != BoardData::SafeCells[0]) return ; 

        openCells(x - 1, y);
        openCells(x + 1, y);
        openCells(x, y - 1);
        openCells(x, y + 1); 
        return ;
    }

    bool isOpenCells(int x, int y, bool &firstTry)
    {
        x = (x - SHILF_RIGHT) / (int)(ICON_WIDTH * SCALE);
        y = (y - SHILF_DOWN) / (int)(ICON_HEIGHT * SCALE);

        if(x < 0 || x >= 10) return false;
        if(y < 0 || y >= 10) return false;
        
        x = x + px;
        y = y + py;
        
        if(firstTry) 
        {
            firstTry = false;
            INIT(x, y);
        }

        
        openCells(x, y);

        return true;
    }

    void flagCell(int x, int y)
    {
        int id = x * BoardData::Columns + y;
        
        if(Tab[id].getStatus() == 3) Tab[id].setStatus(0);
        else if(Tab[id].getStatus() == 2) 
        {
            flags--;
            cellsLeft++;
            if(BoardData::Board[id] == BoardData::MineCell) mineLeft++;
            Tab[id].setStatus(3);
        }
        else if(Tab[id].getStatus() == 0) 
        {
            flags++;
            cellsLeft--;
            if(BoardData::Board[id] == BoardData::MineCell) mineLeft--;
            Tab[id].setStatus(2);
        }
    }

    bool isFlagCells(int x, int y)
    {
        x = (x - SHILF_RIGHT) / (int)(ICON_WIDTH * SCALE);
        y = (y - SHILF_DOWN) / (int)(ICON_HEIGHT * SCALE);

        if(x < 0 || x >= 10) return false;
        if(y < 0 || y >= 10) return false;

        x = x + px;
        y = y + py;

        flagCell(x, y);

        return true;
    }
    
    void openAround(int x, int y)
    {

        int id = x * BoardData::Columns + y;

        for(int i = -1; i <= 1; i++)
        {
            for(int j = -1; j <= 1; j++)
            {
                int nx = x + i;
                int ny = y + j;
                int nid = nx * BoardData::Columns + ny;
    
                if(nx < 0 || nx >= BoardData::Columns) continue;
                if(ny < 0 || ny >= BoardData::Rows) continue;
                
                openCells(nx, ny);
            }
        }
    }

    bool isOpenAround(int x, int y)
    {
        x = (x - SHILF_RIGHT) / (int)(ICON_WIDTH * SCALE);
        y = (y - SHILF_DOWN) / (int)(ICON_HEIGHT * SCALE);

        if(x < 0 || x >= 10) return false;
        if(y < 0 || y >= 10) return false;

        x = x + px;
        y = y + py;
        openAround(x, y);

        return true;
    }

    void Run(int n, int m, int k)
    {
        INIT(n, m, k);
        
        bool firstTry = true;

        GraphicsData::screen.clear(sf::Color::White);
        
        while (GraphicsData::screen.isOpen())
        {
            if(isDead)
            {
                draw();
                GraphicsData::screen.display();
                Graphics::delay(2000);
                DeadScreen::Run();
                return ;
            }
            draw();
            GraphicsData::screen.display();

            sf::Event e;
            while(GraphicsData::screen.pollEvent(e))
            {
                switch(e.type)
                {
                    case sf::Event::Closed:
                        GraphicsData::screen.close();
                        break;

                    case sf::Event::KeyPressed:
                        if(e.key.code == sf::Keyboard::A || e.key.code == sf::Keyboard::Left)
                            if(py > 0) py--;
                        if(e.key.code == sf::Keyboard::D || e.key.code == sf::Keyboard::Right)
                            if(py + 10 < BoardData::Columns) py++;
                        if(e.key.code == sf::Keyboard::W || e.key.code == sf::Keyboard::Up)
                            if(px > 0) px--;
                        if(e.key.code == sf::Keyboard::S || e.key.code == sf::Keyboard::Down)
                            if(px + 10 < BoardData::Rows) px++;
                        break;

                    case sf::Event::MouseButtonPressed:
                        if(e.mouseButton.button == sf::Mouse::Left)
                        {
                            isOpenCells(e.mouseButton.y, e.mouseButton.x, firstTry);
                        }
                        if(e.mouseButton.button == sf::Mouse::Right)
                        {
                            isFlagCells(e.mouseButton.y, e.mouseButton.x);
                        }
                        if(e.mouseButton.button == sf::Mouse::Middle)
                        {
                            isOpenAround(e.mouseButton.y, e.mouseButton.x);
                        }
                        break;
                }
            }
        }
        
    }
}

namespace NewGameModeScreen
{
    Graphics::Button easy, medium, hard, custom, goback;
    int wheel = 0;
    sf::Texture textureBackground, logoTexture;;
    sf::Sprite spriteBackground;
    sf::Vector2u logoSize;
    sf::Vector2f logoPosition;
    sf::Sprite logo;

    void INIT()
    {
        textureBackground.loadFromFile("data/background/ocean/startingscreen.jpg");   
        spriteBackground.setTexture(textureBackground);
        spriteBackground.setScale(0.342f, 0.2824f);
        logoTexture.loadFromFile("data/title/header.png");
                
        
        logoSize = logoTexture.getSize();
        logoPosition = sf::Vector2f((GraphicsData::WIDTH - logoSize.x) / 2.0, 120);

        logo.setTexture(logoTexture);
        logo.setPosition(logoPosition);

        easy.addImage("data/button/easy.png");
        easy.addImage("data/button/choosing_easy.png");
        
        medium.addImage("data/button/medium.png");
        medium.addImage("data/button/choosing_medium.png");

        hard.addImage("data/button/hard.png");
        hard.addImage("data/button/choosing_hard.png");

        custom.addImage("data/button/custom.png");
        custom.addImage("data/button/choosing_custom.png");

        goback.addImage("data/button/goback.png");
        goback.addImage("data/button/choosing_goback.png");

    }

    void DrawButton(Graphics::Button &a, Graphics::Button &b, Graphics::Button &c)
    {
        const int shilfButVer = 0; // shilf button vertical
        const int shilfButHor = 150; // shilf button horizonal
        
        GraphicsData::screen.draw(a.getSprite(GraphicsData::WIDTH / 2 - a.getW() / 2 + shilfButVer,
                                                GraphicsData::HEIGHT / 2 - 2 * a.getH() + shilfButHor));

        GraphicsData::screen.draw(b.getSprite(GraphicsData::WIDTH / 2 - b.getW() / 2 + shilfButVer,
                                                GraphicsData::HEIGHT / 2 - b.getH() / 2 + shilfButHor));

        GraphicsData::screen.draw(c.getSprite(GraphicsData::WIDTH / 2 - c.getW() / 2 + shilfButVer,
                                                GraphicsData::HEIGHT / 2 + c.getH() + shilfButHor));
    }

    void draw()
    {

        // draw background
        GraphicsData::screen.draw(spriteBackground);

    
        //draw button
        GraphicsData::screen.draw(logo);


        //draw button
        if(wheel == 0)
            DrawButton(easy, medium, hard);
        if(wheel == 1)
            DrawButton(medium, hard, custom);
        if(wheel == 2)
            DrawButton(hard, custom, goback);
    }

    void mouseChangeStatus(int x, int y)
    {
        easy.isMouseInside(x, y);
        medium.isMouseInside(x, y);
        hard.isMouseInside(x, y);
        custom.isMouseInside(x, y);
        goback.isMouseInside(x, y);
    }
    
    void ClearStatus()
    {
        easy.setStatus(0);
        medium.setStatus(0);
        hard.setStatus(0);
        custom.setStatus(0);
        goback.setStatus(0);
    }
    
    void Run()
    {
        INIT();
        while(GraphicsData::screen.isOpen())
        {
            GraphicsData::screen.clear(sf::Color::White);
            draw();
            GraphicsData::screen.display();

            sf::Event e;
            while(GraphicsData::screen.pollEvent(e))
            {
                switch(e.type)
                {
                    case sf::Event::Closed:
                        GraphicsData::screen.close();
                        break;
                    case sf::Event::MouseMoved:
                        mouseChangeStatus(e.mouseMove.x, e.mouseMove.y);
                        break;
                    case sf::Event::MouseButtonPressed:
                        if(goback.isMouseInside(e.mouseButton.x, e.mouseButton.y))
                        {
                            goback.setStatus(0);
                            return ;
                        }
                        if(easy.isMouseInside(e.mouseButton.x, e.mouseButton.y))
                        {
                            easy.setStatus(0);
                            GameScreen::Run(10, 10, 16);
                            return ;
                        }
                        if(medium.isMouseInside(e.mouseButton.x, e.mouseButton.y))
                        {
                            medium.setStatus(0);
                            GameScreen::Run(20, 20, 80);
                            return ;
                        }
                        break;
                    case sf::Event::MouseWheelScrolled:
                        if(e.mouseWheelScroll.delta > 0 && wheel > 0)
                        {
                            ClearStatus();
                            wheel = (wheel - 1);
                        }
                        if(e.mouseWheelScroll.delta < 0 && wheel < 2)
                        {
                            ClearStatus();      
                            wheel = (wheel + 1);
                        }
                        break;
                }
            }
        }
    }
}

namespace ChooseGameDataSreen
{
    Graphics::Button newGame, _continue, goback;
    sf::Texture textureBackground, logoTexture;
    sf::Sprite spriteBackground, logo;
    sf::Vector2u logoSize;
    sf::Vector2f logoPosition;
    void INIT()
    {
        ;
        textureBackground.loadFromFile("data/background/ocean/startingscreen.jpg");   
        spriteBackground.setTexture(textureBackground);
        spriteBackground.setScale(0.342f, 0.2824f);

        logoTexture.loadFromFile("data/title/header.png");
        logoSize = logoTexture.getSize();

        logoPosition = sf::Vector2f((GraphicsData::WIDTH - logoSize.x) / 2.0, 120);

        logo.setTexture(logoTexture);
        logo.setPosition(logoPosition);

        newGame.addImage("data/button/newgame.png");
        newGame.addImage("data/button/choosing_newgame.png");

        _continue.addImage("data/button/continue.png");
        _continue.addImage("data/button/choosing_continue.png");

        goback.addImage("data/button/goback.png");
        goback.addImage("data/button/choosing_goback.png");
    }

    void draw()
    {
        // draw background
        GraphicsData::screen.draw(spriteBackground);

        //draw "logo"
        GraphicsData::screen.draw(logo);

        const int shilfButVer = 0; // shilf button vertical
        const int shilfButHor = 150; // shilf button horizonal

        //draw "new game" button
        GraphicsData::screen.draw(newGame.getSprite(GraphicsData::WIDTH / 2 - newGame.getW() / 2 + shilfButVer,
                                                GraphicsData::HEIGHT / 2 - 2 * newGame.getH() + shilfButHor));
        

        // draw "continue" button
        GraphicsData::screen.draw(_continue.getSprite(GraphicsData::WIDTH / 2 - _continue.getW() / 2 + shilfButVer,
                                                GraphicsData::HEIGHT / 2 - _continue.getH() / 2 + shilfButHor));
        
        // draw "go back" button
        GraphicsData::screen.draw(goback.getSprite(GraphicsData::WIDTH / 2 - goback.getW() / 2 + shilfButVer,
                                                GraphicsData::HEIGHT / 2 + goback.getH() + shilfButHor));
    }
    bool mouseChangeStatus(int x, int y)
    {
        newGame.isMouseInside(x, y);
        _continue.isMouseInside(x, y);
        goback.isMouseInside(x, y);
    }
    void Run()
    {
        INIT();
        while(GraphicsData::screen.isOpen())
        {
            GraphicsData::screen.clear(sf::Color::White);
            draw();
            GraphicsData::screen.display();

            sf::Event e;
            while(GraphicsData::screen.pollEvent(e))
            {
                switch(e.type)
                {
                    case sf::Event::Closed:
                        GraphicsData::screen.close();
                        break;
                    case sf::Event::MouseMoved:
                        mouseChangeStatus(e.mouseMove.x, e.mouseMove.y);
                        break;
                    case sf::Event::MouseButtonPressed:
                        if(goback.isMouseInside(e.mouseButton.x, e.mouseButton.y))
                        {
                            goback.setStatus(0);
                            return ;
                        }
                        if(newGame.isMouseInside(e.mouseButton.x, e.mouseButton.y))
                        {
                            newGame.setStatus(0);
                            NewGameModeScreen::Run();
                        }
                        break;
                }
            }
        }
    }
}

namespace StartingScreen
{
    Graphics::Button play, tutorial, highScore;
    sf::Texture logoTexture, textureBackground;
    sf::Vector2u logoSize;
    sf::Vector2f logoPosition;
    sf::Sprite logo, spriteBackground;

    const int shilfButVer = 0; // shilf button vertical
    const int shilfButHor = 150; // shilf button horizonal

    void INIT()
    {
    
        textureBackground.loadFromFile("data/background/ocean/startingscreen.jpg");   
        spriteBackground.setTexture(textureBackground);
        spriteBackground.setScale(0.342f, 0.2824f);
        

        logoTexture.loadFromFile("data/title/header.png");
        logoSize = logoTexture.getSize();
        logoPosition = sf::Vector2f((GraphicsData::WIDTH - logoSize.x) / 2.0, 120);
        logo.setTexture(logoTexture);
        logo.setPosition(logoPosition);


        play.addImage("data/button/play.png");
        play.addImage("data/button/choosing_play.png");

        tutorial.addImage("data/button/tutorial.png");
        tutorial.addImage("data/button/choosing_tutorial.png");

        highScore.addImage("data/button/high_score.png");
        highScore.addImage("data/button/choosing_high_score.png");
    }

    void Draw()
    {
        // draw background picture
        GraphicsData::screen.draw(spriteBackground);

        //draw "logo"

        GraphicsData::screen.draw(logo);

        // draw "play" button
        GraphicsData::screen.draw(play.getSprite(GraphicsData::WIDTH / 2 - play.getW() / 2 + shilfButVer, 
                                                GraphicsData::HEIGHT / 2 - 2 * play.getH() + shilfButHor));
        
        // draw "tutorial" button
        GraphicsData::screen.draw(tutorial.getSprite(GraphicsData::WIDTH / 2 - tutorial.getW() / 2 + shilfButVer,
                                                GraphicsData::HEIGHT / 2 - tutorial.getH() / 2 + shilfButHor));
        
        // draw "high score" button
        GraphicsData::screen.draw(highScore.getSprite(GraphicsData::WIDTH / 2 - highScore.getW() / 2 + shilfButVer,
                                                GraphicsData::HEIGHT / 2 + highScore.getH() + shilfButHor));
        
    }

    void mouseChangeStatus(int x, int y)
    {
        play.isMouseInside(x, y);
        tutorial.isMouseInside(x, y);
        highScore.isMouseInside(x, y);
    }

    void Run()
    {
        INIT();
        while(GraphicsData::screen.isOpen())
        {
            GraphicsData::screen.clear(sf::Color::White);    
            Draw();
            GraphicsData::screen.display();

            sf::Event e;
            while(GraphicsData::screen.pollEvent(e))
            {
                switch(e.type)
                {
                    case sf::Event::Closed:
                        GraphicsData::screen.close();
                        break;
                    case sf::Event::MouseButtonPressed:
                        if(play.isMouseInside(e.mouseButton.x, e.mouseButton.y))
                        {
                            play.setStatus(0);
                            ChooseGameDataSreen::Run();
                        }
                        break;
                    case sf::Event::MouseMoved:
                        mouseChangeStatus(e.mouseMove.x, e.mouseMove.y);
                        break;
                }
            }
        }
    }
}

void Graphics::Run()
{
    GraphicsData::INIT();
    
    StartingScreen::Run();
        
}
