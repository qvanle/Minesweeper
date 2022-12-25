#include <GraphicsVariables.hpp>
#include <SystemVariables.hpp>
//#include <Button.hpp>
#include <Screen.hpp>

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
    const int shiftButVer = 0; // shift button vertical
    const int shiftButHor = -80; // shift button horizonal

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
        GraVar::screen.draw(highScore.getSprite(GraVar::WIDTH / 2 - highScore.getW() / 2 + shiftButVer,
                                                GraVar::HEIGHT / 2 + highScore.getH() / 2 + shiftButHor));
        // draw "go back" button
        GraVar::screen.draw(goback.getSprite(GraVar::WIDTH / 2 - goback.getW() / 2 + shiftButVer,
                                                GraVar::HEIGHT / 2 + 2 * goback.getH() + shiftButHor));
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
    const int shiftButVer = 0; // shift button vertical
    const int shiftButHor = -80; // shift button horizonal

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
        GraVar::screen.draw(highScore.getSprite(GraVar::WIDTH / 2 - highScore.getW() / 2 + shiftButVer,
                                                GraVar::HEIGHT / 2 + highScore.getH() / 2 + shiftButHor));
        // draw "go back" button
        GraVar::screen.draw(goback.getSprite(GraVar::WIDTH / 2 - goback.getW() / 2 + shiftButVer,
                                                GraVar::HEIGHT / 2 + 2 * goback.getH() + shiftButHor));
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

    const int shift_DOWN = 50;
    const int shift_RIGHT = 50;
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
                    GraVar::screen.draw(Tab[id].getSprite(j * (1 + ICON_WIDTH * SCALE) + shift_RIGHT, 
                                                                i * (1 + ICON_HEIGHT * SCALE) + shift_DOWN, SCALE));
                }

                verLine.setPosition(j * (1 + ICON_WIDTH * SCALE) + shift_RIGHT - 2, 
                                    i * (1 + ICON_HEIGHT * SCALE) + shift_DOWN - 2);
                horLine.setPosition(j * (1 + ICON_WIDTH * SCALE) + shift_RIGHT - 2, 
                                    i * (1 + ICON_HEIGHT * SCALE) + shift_DOWN - 2);

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
        x = (x - shift_RIGHT) / (int)(ICON_WIDTH * SCALE);
        y = (y - shift_DOWN) / (int)(ICON_HEIGHT * SCALE);

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
        x = (x - shift_RIGHT) / (int)(ICON_WIDTH * SCALE);
        y = (y - shift_DOWN) / (int)(ICON_HEIGHT * SCALE);

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
        x = (x - shift_RIGHT) / (int)(ICON_WIDTH * SCALE);
        y = (y - shift_DOWN) / (int)(ICON_HEIGHT * SCALE);

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

void draw(Screen &scr)
{

    int n = scr.buttonsSize();
    
    GraVar::screen.draw(scr.getBackground());
    GraVar::screen.draw(scr.getTitle());

    for(int i = 0; i < n; i++)
        if(scr.isVisible(i))
            GraVar::screen.draw(scr.getButton(i));

    GraVar::screen.display();
}

void newGameChangeButton(Screen &scr)
{

    const int shiftDown = 150;
    const int shiftRight = 0;
    if(scr.getScrolls() == 0)
    {
        int i = 0;
        scr.setButtonPos(i, GraVar::WIDTH / 2 - scr.ButtonW(i) / 2 + shiftRight,
                    GraVar::HEIGHT / 2 - scr.ButtonH(i) * 2 + shiftDown);
        scr.setVisible(i, true);
        scr.setButtonPos(i + 1, GraVar::WIDTH / 2 - scr.ButtonW(i + 1) / 2 + shiftRight,
                    GraVar::HEIGHT / 2 - scr.ButtonH(i + 1) / 2 + shiftDown);
        scr.setVisible(i + 1, true);
        scr.setButtonPos(i + 2, GraVar::WIDTH / 2 - scr.ButtonW(i + 2) / 2 + shiftRight,
                    GraVar::HEIGHT / 2 + scr.ButtonH(i + 2) + shiftDown);
        scr.setVisible(i + 2, true);

        scr.setVisible(i + 3, false);
        scr.setVisible(i + 4, false);
    }
    if(scr.getScrolls() == 1)
    {
        int i = 1;
        scr.setButtonPos(i, GraVar::WIDTH / 2 - scr.ButtonW(i) / 2 + shiftRight,
                    GraVar::HEIGHT / 2 - scr.ButtonH(i) * 2 + shiftDown);
        scr.setVisible(i, true);
        scr.setButtonPos(i + 1, GraVar::WIDTH / 2 - scr.ButtonW(i + 1) / 2 + shiftRight,
                    GraVar::HEIGHT / 2 - scr.ButtonH(i + 1) / 2 + shiftDown);
        scr.setVisible(i + 1, true);
        scr.setButtonPos(i + 2, GraVar::WIDTH / 2 - scr.ButtonW(i + 2) / 2 + shiftRight,
                    GraVar::HEIGHT / 2 + scr.ButtonH(i + 2) + shiftDown);
        scr.setVisible(i + 2, true);

        scr.setVisible(i + 3, false);
        scr.setVisible(i - 1, false);
    }
    if(scr.getScrolls() == 2)
    {
        int i = 2;
        scr.setButtonPos(i, GraVar::WIDTH / 2 - scr.ButtonW(i) / 2 + shiftRight,
                    GraVar::HEIGHT / 2 - scr.ButtonH(i) * 2 + shiftDown);
        scr.setVisible(i, true);
        scr.setButtonPos(i + 1, GraVar::WIDTH / 2 - scr.ButtonW(i + 1) / 2 + shiftRight,
                    GraVar::HEIGHT / 2 - scr.ButtonH(i + 1) / 2 + shiftDown);
        scr.setVisible(i + 1, true);
        scr.setButtonPos(i + 2, GraVar::WIDTH / 2 - scr.ButtonW(i + 2) / 2 + shiftRight,
                    GraVar::HEIGHT / 2 + scr.ButtonH(i + 2) + shiftDown);
        scr.setVisible(i + 2, true);

        scr.setVisible(i - 1, false);
        scr.setVisible(i - 2, false);
    }
}

Screen Playing(int id)
{
    Screen s;
    s.setID(id);
    s.setMaxScrolls(0);
}

Screen NewGame(int id)
{
    Screen s;
    s.setMaxScrolls(2);
    s.setID(id);

    // background
    s.addBackground("data/background/ocean/choosingscreen.jpg");

    // title
    s.addTitle("data/title/header.png");  

    const int shiftDown = 150;
    const int shiftRight = 0;

    // easy button
    s.addButton("data/button/easy.png");
    s.addButtonTexture("data/button/choosing_easy.png", 0);
    s.setButtonPos(0, GraVar::WIDTH / 2 - s.ButtonW(0) / 2 + shiftRight,
                      GraVar::HEIGHT / 2 - s.ButtonH(0) * 2 + shiftDown);

    // medium button
    s.addButton("data/button/medium.png");
    s.addButtonTexture("data/button/choosing_medium.png", 1);
    s.setButtonPos(1, GraVar::WIDTH / 2 - s.ButtonW(1) / 2 + shiftRight,
                      GraVar::HEIGHT / 2 - s.ButtonH(1) / 2 + shiftDown);

    // hard button
    s.addButton("data/button/hard.png");
    s.addButtonTexture("data/button/choosing_hard.png", 2);
    s.setButtonPos(2, GraVar::WIDTH / 2 - s.ButtonW(2) / 2 + shiftRight,
                      GraVar::HEIGHT / 2 + s.ButtonH(2) + shiftDown);
    
    // custom button
    s.addButton("data/button/custom.png");
    s.addButtonTexture("data/button/choosing_custom.png", 3);
    s.setVisible(3, false);


    // go back button
    s.addButton("data/button/goback.png");
    s.addButtonTexture("data/button/choosing_goback.png", 4);
    s.setVisible(4, false);
    
    return s;   
}

Screen Choosing(int id)
{   
    Screen s;
    s.setID(id);
    s.setMaxScrolls(0);

    // background
    s.addBackground("data/background/ocean/choosingscreen.jpg");

    // title
    s.addTitle("data/title/header.png");

    const int shiftDown = 150;
    const int shiftRight = 0;

    // "newgame" button
    s.addButton("data/button/newgame.png");
    s.addButtonTexture("data/button/choosing_newgame.png", 0);
    s.setButtonPos(0, GraVar::WIDTH / 2 - s.ButtonW(0) / 2 + shiftRight,
                      GraVar::HEIGHT / 2 - s.ButtonH(0) * 2 + shiftDown);
    s.setButtonScreenID(0, 2); // point to new-game screen


    // "continue" button
    s.addButton("data/button/continue.png");
    s.addButtonTexture("data/button/choosing_continue.png", 1);
    s.setButtonPos(1, GraVar::WIDTH / 2 - s.ButtonW(1) / 2 + shiftRight,
                      GraVar::HEIGHT / 2 - s.ButtonH(1) / 2 + shiftDown);
    s.setButtonScreenID(1, 5);


    // "go back" button
    s.addButton("data/button/goback.png");
    s.addButtonTexture("data/button/choosing_goback.png", 2);
    s.setButtonPos(2, GraVar::WIDTH / 2 - s.ButtonW(2) / 2 + shiftRight,
                      GraVar::HEIGHT / 2 + s.ButtonH(2) + shiftDown);
    s.setButtonScreenID(2, 0);
    return s;
}

Screen Starting(int id)
{
    Screen s;

    s.setID(id);
    s.setMaxScrolls(0);

    // background
    s.addBackground("data/background/ocean/startingscreen.jpg");

    // title
    s.addTitle("data/title/header.png");

    const int shiftDown = 150;
    const int shiftRight = 0;

    // "play" button
    s.addButton("data/button/play.png");
    s.addButtonTexture("data/button/choosing_play.png", 0);
    s.setButtonPos(0, GraVar::WIDTH / 2 - s.ButtonW(0) / 2 + shiftRight,
                      GraVar::HEIGHT / 2 - s.ButtonH(0) * 2 + shiftDown);
    s.setButtonScreenID(0, 1);


    // "tutorial" button
    s.addButton("data/button/tutorial.png");
    s.addButtonTexture("data/button/choosing_tutorial.png", 1);
    s.setButtonPos(1, GraVar::WIDTH / 2 - s.ButtonW(1) / 2 + shiftRight,
                      GraVar::HEIGHT / 2 - s.ButtonH(1) / 2 + shiftDown);
    s.setButtonScreenID(1, 5);


    // "high score" button
    s.addButton("data/button/high_score.png");
    s.addButtonTexture("data/button/choosing_high_score.png", 2);
    s.setButtonPos(2, GraVar::WIDTH / 2 - s.ButtonW(2) / 2 + shiftRight,
                      GraVar::HEIGHT / 2 + s.ButtonH(2) + shiftDown);
    s.setButtonScreenID(2, 6);

    return s;
}

void StartGame()
{
    GraVar::INIT();
    //StartingScreen::Run();
    
    std::vector<Screen> scrs;
    
    
    scrs.emplace_back(Starting(0));// scrs[0]: starting screen 

    scrs.emplace_back(Choosing(1));// scrs[1]: choosing screen

    scrs.emplace_back(NewGame(2));// scrs[2]: new-game screen

    scrs.emplace_back(Playing(3));// scrs[3]: game screen
    
    scrs.emplace_back();// scrs[4]: game-end screen

    scrs.emplace_back();// scrs[5]: game-tutorial screen

    scrs.emplace_back();// scrs[6]: high-score screen


    int status = 0;
    
    while(GraVar::screen.isOpen())
    {
        draw(scrs[status]);
        sf::Event e;
        while(GraVar::screen.pollEvent(e))
        {
            switch(e.type)
            {
                case sf::Event::Closed:
                    GraVar::screen.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    Button key = scrs[status].MouseClickButton(e.mouseButton.x, e.mouseButton.y);
                    status = key.getScreenID();
                    scrs[status].setLastButton(key);
                    break;
                case sf::Event::MouseMoved:
                    scrs[status].MouseChangeStatus(e.mouseMove.x, e.mouseMove.y);
                    break;
                case sf::Event::MouseWheelScrolled:
                    if(scrs[status].scrolling(e.mouseWheelScroll.delta)) newGameChangeButton(scrs[status]);
                    break;
            }
        }
    }

    return ;
}