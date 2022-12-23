#include <GraphicsVariables.hpp>
#include <SystemVariables.hpp>
#include <Button.hpp>

//declare variable

sf::Font GraVar::font;
int GraVar::WIDTH = 1200;
int GraVar::HEIGHT = 700;
sf::RenderWindow GraVar::screen(sf::VideoMode(GraVar::WIDTH, GraVar::HEIGHT), "Minesweeper", sf::Style::Close);  

void GraVar::INIT()
{
    GraVar::font.loadFromFile("data/font/lemon_jelly/font.ttf");
}

void delay(int t)
{
    sf::Clock clock;
    sf::Time start = clock.getElapsedTime();
    while(clock.getElapsedTime() - start < sf::milliseconds(t));
    return ;
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
    
    Button goback, highScore;

    void draw()
    {
        GraVar::screen.draw(spriteBackground);
        GraVar::screen.draw(title);

        // draw "high score" button
        GraVar::screen.draw(highScore.getSprite(GraVar::WIDTH / 2 - highScore.getW() / 2 + shilfButVer,
                                                GraVar::HEIGHT / 2 + highScore.getH() / 2 + shilfButHor));
        // draw "go back" button
        GraVar::screen.draw(goback.getSprite(GraVar::WIDTH / 2 - goback.getW() / 2 + shilfButVer,
                                                GraVar::HEIGHT / 2 + 2 * goback.getH() + shilfButHor));
    }
    
    void INIT()
    {
        textureBackground.loadFromFile("data/background/ocean/darkocean.jpg");   
        spriteBackground.setTexture(textureBackground);


        logoTexture.loadFromFile("data/title/header.png");
        logoSize = logoTexture.getSize();
        logoPosition = sf::Vector2f((GraVar::WIDTH - logoSize.x * 0.6) - 50, 50);
        logo.setTexture(logoTexture);
        logo.setScale(0.6, 0.6);
        logo.setPosition(logoPosition);


        titleTexture.loadFromFile("data/title/lose.png");
        titleSize = titleTexture.getSize();
        titlePosition = sf::Vector2f((GraVar::WIDTH - titleSize.x) / 2.0, (GraVar::HEIGHT - titleSize.y) / 2.0 - 200);
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
        while(GraVar::screen.isOpen())
        {
            GraVar::screen.clear(sf::Color::White);
            draw();
            GraVar::screen.display();

            sf::Event e;
            while(GraVar::screen.pollEvent(e))
            {
                switch(e.type)
                {
                    case sf::Event::Closed:
                        GraVar::screen.close();
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
    const int shilfButVer = 0; // shilf button vertical
    const int shilfButHor = -80; // shilf button horizonal

    sf::Texture textureBackground, logoTexture, titleTexture;
    sf::Sprite spriteBackground;
    sf::Vector2u logoSize, titleSize;
    sf::Vector2f logoPosition, titlePosition;
    sf::Sprite logo, title;
    
    Button goback, highScore;

    void draw()
    {
        GraVar::screen.draw(spriteBackground);
        GraVar::screen.draw(title);

        // draw "high score" button
        GraVar::screen.draw(highScore.getSprite(GraVar::WIDTH / 2 - highScore.getW() / 2 + shilfButVer,
                                                GraVar::HEIGHT / 2 + highScore.getH() / 2 + shilfButHor));
        // draw "go back" button
        GraVar::screen.draw(goback.getSprite(GraVar::WIDTH / 2 - goback.getW() / 2 + shilfButVer,
                                                GraVar::HEIGHT / 2 + 2 * goback.getH() + shilfButHor));
    }
    
    void INIT()
    {
        textureBackground.loadFromFile("data/background/ocean/darkocean.jpg");   
        spriteBackground.setTexture(textureBackground);


        logoTexture.loadFromFile("data/title/header.png");
        logoSize = logoTexture.getSize();
        logoPosition = sf::Vector2f((GraVar::WIDTH - logoSize.x * 0.6) - 50, 50);
        logo.setTexture(logoTexture);
        logo.setScale(0.6, 0.6);
        logo.setPosition(logoPosition);


        titleTexture.loadFromFile("data/title/you_win.png");
        titleSize = titleTexture.getSize();
        titlePosition = sf::Vector2f((GraVar::WIDTH - titleSize.x) / 2.0, (GraVar::HEIGHT - titleSize.y) / 2.0 - 200);
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
        while(GraVar::screen.isOpen())
        {
            GraVar::screen.clear(sf::Color::White);
            draw();
            GraVar::screen.display();

            sf::Event e;
            while(GraVar::screen.pollEvent(e))
            {
                switch(e.type)
                {
                    case sf::Event::Closed:
                        GraVar::screen.close();
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

namespace GameScreen
{
    sf::Texture textureBackground, logoTexture;
    sf::Sprite spriteBackground;
    sf::Vector2u logoSize;
    sf::Vector2f logoPosition;
    sf::Sprite logo;

    std::vector<Button> Tab;

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

        SysVar::init(n, m, k);


        textureBackground.loadFromFile("data/background/ocean/darkocean.jpg");   
        spriteBackground.setTexture(textureBackground);

        logoTexture.loadFromFile("data/title/header.png");
        logoSize = logoTexture.getSize();
        logoPosition = sf::Vector2f((int)(GraVar::WIDTH - logoSize.x * 0.6) - 50, 50);


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
                Tab[id].addImage("data/icons/ocean/" + std::to_string(SysVar::Board[id]) + ".jpg");
                Tab[id].addImage("data/icons/ocean/9.jpg");
                Tab[id].addImage("data/icons/ocean/10.jpg");
            }
        }
    }

    void INIT(int x, int y)
    {

        int n = SysVar::Columns;
        int m = SysVar::Rows;
        int k = SysVar::Mines;
        
        isDead = false;
        cellsLeft = n * m;
        mineLeft = k;
        flags = 0;
        
        SysVar::init(n, m, k, x, y);

        Tab.clear();
        Tab.resize(n * m);

        for(int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int id = i * m + j;
                Tab[id].addImage("data/icons/ocean/12.png");
                Tab[id].addImage("data/icons/ocean/" + std::to_string(SysVar::Board[id]) + ".jpg");
                Tab[id].addImage("data/icons/ocean/9.jpg");
                Tab[id].addImage("data/icons/ocean/10.jpg");
            }
        }
    }

    void draw()
    {
        GraVar::screen.draw(spriteBackground);
        for(int i = 0; i <= 10; i++)
        {
            for(int j = 0; j <= 10; j++)
            {
                int id = (i + px) * SysVar::Columns + (j + py);
                
                if(i != 10 && j != 10)
                {
                    if(isDead && SysVar::Board[id] == SysVar::MineCell)
                        Tab[id].setStatus(1);
                    GraVar::screen.draw(Tab[id].getSprite(j * (1 + ICON_WIDTH * SCALE) + SHILF_RIGHT, 
                                                                i * (1 + ICON_HEIGHT * SCALE) + SHILF_DOWN, SCALE));
                }

                verLine.setPosition(j * (1 + ICON_WIDTH * SCALE) + SHILF_RIGHT - 2, 
                                    i * (1 + ICON_HEIGHT * SCALE) + SHILF_DOWN - 2);
                horLine.setPosition(j * (1 + ICON_WIDTH * SCALE) + SHILF_RIGHT - 2, 
                                    i * (1 + ICON_HEIGHT * SCALE) + SHILF_DOWN - 2);

                if(i != 10) GraVar::screen.draw(verLine);
                if(j != 10) GraVar::screen.draw(horLine);
            }
        } 
    }

    void openCells(int x, int y)
    {
        if(x < 0 || x >= SysVar::Rows) return ;
        if(y < 0 || y >= SysVar::Columns) return ;
        
        int id = x * SysVar::Columns + y;
        if(Tab[id].getStatus() == 1 || Tab[id].getStatus() == 2) return ; 
        Tab[id].setStatus(1);

        cellsLeft--;

        if(SysVar::Board[id] == SysVar::MineCell) isDead = true;
        if(SysVar::Board[id] != SysVar::SafeCells[0]) return ; 

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
        int id = x * SysVar::Columns + y;
        
        if(Tab[id].getStatus() == 3) Tab[id].setStatus(0);
        else if(Tab[id].getStatus() == 2) 
        {
            flags--;
            cellsLeft++;
            if(SysVar::Board[id] == SysVar::MineCell) mineLeft++;
            Tab[id].setStatus(3);
        }
        else if(Tab[id].getStatus() == 0) 
        {
            flags++;
            cellsLeft--;
            if(SysVar::Board[id] == SysVar::MineCell) mineLeft--;
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

        int id = x * SysVar::Columns + y;

        for(int i = -1; i <= 1; i++)
        {
            for(int j = -1; j <= 1; j++)
            {
                int nx = x + i;
                int ny = y + j;
                int nid = nx * SysVar::Columns + ny;
    
                if(nx < 0 || nx >= SysVar::Columns) continue;
                if(ny < 0 || ny >= SysVar::Rows) continue;
                
                openCells(nx, ny);
            }
        }
    }

    bool isOpenAround(int x, int y, bool &firstTry)
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

        openAround(x, y);

        return true;
    }

    void Run(int n, int m, int k)
    {
        INIT(n, m, k);
        
        bool firstTry = true;

        GraVar::screen.clear(sf::Color::White);
        
        while (GraVar::screen.isOpen())
        {
            if(isDead)
            {
                draw();
                GraVar::screen.display();
                delay(2000);
                DeadScreen::Run();
                return ;
            }
            if(cellsLeft == 0 && mineLeft == 0)
            {
                std::cout <<"winning\n";
                draw();
                GraVar::screen.display();
                delay(1000);
                WinningScreen::Run();
                return ;
            }
            draw();
            GraVar::screen.display();

            sf::Event e;
            while(GraVar::screen.pollEvent(e))
            {
                switch(e.type)
                {
                    case sf::Event::Closed:
                        GraVar::screen.close();
                        break;

                    case sf::Event::KeyPressed:
                        if(e.key.code == sf::Keyboard::A || e.key.code == sf::Keyboard::Left)
                            if(py > 0) py--;
                        if(e.key.code == sf::Keyboard::D || e.key.code == sf::Keyboard::Right)
                            if(py + 10 < SysVar::Columns) py++;
                        if(e.key.code == sf::Keyboard::W || e.key.code == sf::Keyboard::Up)
                            if(px > 0) px--;
                        if(e.key.code == sf::Keyboard::S || e.key.code == sf::Keyboard::Down)
                            if(px + 10 < SysVar::Rows) px++;
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
                            isOpenAround(e.mouseButton.y, e.mouseButton.x, firstTry);
                        }
                        break;
                }
            }
        }
        
    }
}

namespace NewGameModeScreen
{
    Button easy, medium, hard, custom, goback;
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
        logoPosition = sf::Vector2f((GraVar::WIDTH - logoSize.x) / 2.0, 120);

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

    void DrawButton(Button &a, Button &b, Button &c)
    {
        const int shilfButVer = 0; // shilf button vertical
        const int shilfButHor = 150; // shilf button horizonal
        
        GraVar::screen.draw(a.getSprite(GraVar::WIDTH / 2 - a.getW() / 2 + shilfButVer,
                                                GraVar::HEIGHT / 2 - 2 * a.getH() + shilfButHor));

        GraVar::screen.draw(b.getSprite(GraVar::WIDTH / 2 - b.getW() / 2 + shilfButVer,
                                                GraVar::HEIGHT / 2 - b.getH() / 2 + shilfButHor));

        GraVar::screen.draw(c.getSprite(GraVar::WIDTH / 2 - c.getW() / 2 + shilfButVer,
                                                GraVar::HEIGHT / 2 + c.getH() + shilfButHor));
    }

    void draw()
    {

        // draw background
        GraVar::screen.draw(spriteBackground);

    
        //draw button
        GraVar::screen.draw(logo);


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
        while(GraVar::screen.isOpen())
        {
            GraVar::screen.clear(sf::Color::White);
            draw();
            GraVar::screen.display();

            sf::Event e;
            while(GraVar::screen.pollEvent(e))
            {
                switch(e.type)
                {
                    case sf::Event::Closed:
                        GraVar::screen.close();
                        break;
                    case sf::Event::MouseMoved:
                        mouseChangeStatus(e.mouseMove.x, e.mouseMove.y);
                        break;
                    case sf::Event::MouseButtonPressed:
                        
                        if(easy.isMouseInside(e.mouseButton.x, e.mouseButton.y) && wheel == 0)
                        {
                            easy.setStatus(0);
                            GameScreen::Run(10, 10, 16);
                            return ;
                        }
                        if(medium.isMouseInside(e.mouseButton.x, e.mouseButton.y) && wheel != 2)
                        {
                            medium.setStatus(0);
                            GameScreen::Run(16, 16, 64);
                            return ;
                        }
                        if(hard.isMouseInside(e.mouseButton.x, e.mouseButton.y) && wheel != 1)
                        {
                            hard.setStatus(0);
                            GameScreen::Run(32, 32, 256);
                            return ;
                        }
                        if(goback.isMouseInside(e.mouseButton.x, e.mouseButton.y) && wheel == 2)
                        {   
                            goback.setStatus(0);
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
    Button newGame, _continue, goback;
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

        logoPosition = sf::Vector2f((GraVar::WIDTH - logoSize.x) / 2.0, 120);

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
        GraVar::screen.draw(spriteBackground);

        //draw "logo"
        GraVar::screen.draw(logo);

        const int shilfButVer = 0; // shilf button vertical
        const int shilfButHor = 150; // shilf button horizonal

        //draw "new game" button
        GraVar::screen.draw(newGame.getSprite(GraVar::WIDTH / 2 - newGame.getW() / 2 + shilfButVer,
                                                GraVar::HEIGHT / 2 - 2 * newGame.getH() + shilfButHor));
        

        // draw "continue" button
        GraVar::screen.draw(_continue.getSprite(GraVar::WIDTH / 2 - _continue.getW() / 2 + shilfButVer,
                                                GraVar::HEIGHT / 2 - _continue.getH() / 2 + shilfButHor));
        
        // draw "go back" button
        GraVar::screen.draw(goback.getSprite(GraVar::WIDTH / 2 - goback.getW() / 2 + shilfButVer,
                                                GraVar::HEIGHT / 2 + goback.getH() + shilfButHor));
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
        while(GraVar::screen.isOpen())
        {
            GraVar::screen.clear(sf::Color::White);
            draw();
            GraVar::screen.display();

            sf::Event e;
            while(GraVar::screen.pollEvent(e))
            {
                switch(e.type)
                {
                    case sf::Event::Closed:
                        GraVar::screen.close();
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
    Button play, tutorial, highScore;
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
        logoPosition = sf::Vector2f((GraVar::WIDTH - logoSize.x) / 2.0, 120);
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
        GraVar::screen.draw(spriteBackground);

        //draw "logo"

        GraVar::screen.draw(logo);

        // draw "play" button
        GraVar::screen.draw(play.getSprite(GraVar::WIDTH / 2 - play.getW() / 2 + shilfButVer, 
                                                GraVar::HEIGHT / 2 - 2 * play.getH() + shilfButHor));
        
        // draw "tutorial" button
        GraVar::screen.draw(tutorial.getSprite(GraVar::WIDTH / 2 - tutorial.getW() / 2 + shilfButVer,
                                                GraVar::HEIGHT / 2 - tutorial.getH() / 2 + shilfButHor));
        
        // draw "high score" button
        GraVar::screen.draw(highScore.getSprite(GraVar::WIDTH / 2 - highScore.getW() / 2 + shilfButVer,
                                                GraVar::HEIGHT / 2 + highScore.getH() + shilfButHor));
        
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
        while(GraVar::screen.isOpen())
        {
            GraVar::screen.clear(sf::Color::White);    
            Draw();
            GraVar::screen.display();

            sf::Event e;
            while(GraVar::screen.pollEvent(e))
            {
                switch(e.type)
                {
                    case sf::Event::Closed:
                        GraVar::screen.close();
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

void StartGame()
{
    GraVar::INIT();
    StartingScreen::Run();
    return ;
}