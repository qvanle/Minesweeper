#include <Button.hpp>
#include <Data.hpp>

//declare variable

sf::Font GraphicsData::font;
int GraphicsData::WIDTH = 1200;
int GraphicsData::HEIGHT = 700;
sf::RenderWindow GraphicsData::screen(sf::VideoMode(GraphicsData::WIDTH, GraphicsData::HEIGHT), "Minesweeper", sf::Style::Close);  


void GraphicsData::INIT()
{
    GraphicsData::font.loadFromFile("data/font/monofur/monof55.ttf");
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


        titleTexture.loadFromFile("data/title/you_win.png");
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

namespace GameScreen
{
    sf::Texture textureBackground, logoTexture;
    sf::Sprite spriteBackground;
    sf::Vector2u logoSize;
    sf::Vector2f logoPosition;
    sf::Sprite logo;
    sf::Text textTime, textFlag, gameInfo, tutorial;
    std::vector<Button> Tab;
    Button goback;
    sf::Vector2u choosingCell;
    Button leftBar, rightBar, downBar, upBar;

    const int SHILF_DOWN = 50;
    const int SHILF_RIGHT = 100;
    const int ICON_WIDTH = 120;
    const int ICON_HEIGHT = 120;
    const float SCALE = 0.5;

    int px = 0;
    int py = 0;
    bool isDead = 0;
    bool isPlaying = false;
    bool oldData;
    
    int cellsLeft;
    int mineLeft;
    int flags;

    sf::RectangleShape horLine(sf::Vector2f(ICON_WIDTH * SCALE + 5 , 2.f));
    sf::RectangleShape verLine(sf::Vector2f(2.f, ICON_HEIGHT * SCALE + 5));
    sf::Color frameColor(60, 60, 60);
    
    sf::RectangleShape horLine2(sf::Vector2f(ICON_WIDTH * SCALE + 4, 3.f));
    sf::RectangleShape verLine2(sf::Vector2f(3.f, ICON_HEIGHT * SCALE + 4));
    sf::Color ChoosedColor(255, 64, 0);

    void saving()
    {
        std::ofstream saving ("data/saving.txt");
        saving << BoardData::Columns << " " << BoardData::Rows << " " << BoardData::Mines << "\n";
        saving << cellsLeft << " " << mineLeft << " " << flags << "\n";
        saving << BoardData::time.asSeconds() << "\n"; 
        for(int i = 0; i < (int) BoardData::Board.size(); i++)
            saving << BoardData::Board[i] << " " << Tab[i].getStatus() << "\n";
        saving.close();
    }

    void INIT_GRAPHICS()
    {

        horLine.setFillColor(frameColor);
        verLine.setFillColor(frameColor);

        horLine2.setFillColor(ChoosedColor);
        verLine2.setFillColor(ChoosedColor);

        textureBackground.loadFromFile("data/background/ocean/darkocean.jpg");   
        spriteBackground.setTexture(textureBackground);

        logoTexture.loadFromFile("data/title/header.png");
        logoSize = logoTexture.getSize();
        logoPosition = sf::Vector2f((int)(GraphicsData::WIDTH - logoSize.x * 0.5) - 50, 50);

        logo.setTexture(logoTexture);
        logo.setScale(0.5, 0.5);
        logo.setPosition(logoPosition);
        
        tutorial.setFont(GraphicsData::font);
        tutorial.setCharacterSize(18);
        tutorial.setFillColor(sf::Color::Green);
        tutorial.setPosition(790, 150);
        tutorial.setString("Use arrow key on keyboard to move the board.");

        gameInfo.setFont(GraphicsData::font);
        gameInfo.setCharacterSize(32);
        gameInfo.setFillColor(sf::Color::White);
        gameInfo.setPosition(850, 250);
        gameInfo.setString("Size: " + std::to_string(BoardData::Columns) + "x" + std::to_string(BoardData::Rows) + "\nMines:" + std::to_string(BoardData::Mines) + " mines");


        textTime.setFont(GraphicsData::font);
        textTime.setCharacterSize(32);
        textTime.setFillColor(sf::Color::White);
        textTime.setPosition(848, 315);


        textFlag.setFont(GraphicsData::font);
        textFlag.setCharacterSize(32);
        textFlag.setFillColor(sf::Color::White);
        textFlag.setPosition(850, 345);

        
        goback.addImage("data/button/goback.png");
        goback.addImage("data/button/choosing_goback.png");
        goback.setPosition(GraphicsData::WIDTH - goback.getW() - 150, 550);

        leftBar.addImage("data/button/left_bar.png");
        rightBar.addImage("data/button/right_bar.png");
        downBar.addImage("data/button/down_bar.png");
        upBar.addImage("data/button/up_bar.png");
    }

    void INIT(int n, int m, int k)
    {
        oldData = false;

        isDead = false;
        isPlaying = false;
        cellsLeft = n * m;
        mineLeft = k;
        flags = 0;

        BoardData::init(n, m, k);
        BoardData::time = sf::seconds(0);

        
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
        INIT_GRAPHICS();
    }

    void INIT(std::string link, bool &FirstTry)
    {

        oldData = true;

        std::ifstream Data(link);

        isDead = false;
        isPlaying = false;
        
        Data >> BoardData::Columns >> BoardData::Rows >> BoardData::Mines;
        Data >> cellsLeft >> mineLeft >> flags;
        float temp; Data >> temp;
        BoardData::time = sf::seconds(temp);


        Tab.clear();
        Tab.resize(BoardData::Columns * BoardData::Rows);
        BoardData::Board.resize((BoardData::Columns * BoardData::Rows));
        for(int i = 0; i < BoardData::Rows; i++)
        {
            for (int j = 0; j < BoardData::Columns; j++)
            {
                int id = i * BoardData::Columns + j;
                Tab[id].addImage("data/icons/ocean/12.png");
                Tab[id].addImage("data/icons/ocean/" + std::to_string(BoardData::Board[id]) + ".jpg");
                Tab[id].addImage("data/icons/ocean/9.jpg");
                Tab[id].addImage("data/icons/ocean/10.jpg");
                int temp;
                Data >> BoardData::Board[id] >> temp;
                Tab[id].setStatus(temp);
                if(temp == 0) FirstTry = false;
            }
        }
        INIT_GRAPHICS();
        Data.close();
    }

    void INIT(int x, int y)
    {
        oldData = false;
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

        if(py != 0) GraphicsData::screen.draw(leftBar.getSprite(SHILF_RIGHT - 40, SHILF_DOWN));
        if(px != 0) GraphicsData::screen.draw(upBar.getSprite(SHILF_RIGHT, SHILF_DOWN - 40));
        if(py + 10 < BoardData::Columns) GraphicsData::screen.draw(rightBar.getSprite(610 + SHILF_RIGHT, SHILF_DOWN));
        if(px + 10 < BoardData::Rows) GraphicsData::screen.draw(downBar.getSprite(SHILF_RIGHT, 610 + SHILF_DOWN));
        
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
        GraphicsData::screen.draw(logo);
        if(BoardData::Columns > 10 || BoardData::Rows > 10) GraphicsData::screen.draw(tutorial);
        textTime.setString("Time: " + std::to_string((int)(BoardData::time.asSeconds())) + "s"); 
        GraphicsData::screen.draw(textTime);
        GraphicsData::screen.draw(gameInfo);
        textFlag.setString("Flags: " + std::to_string(flags));
        GraphicsData::screen.draw(textFlag);
        GraphicsData::screen.draw(goback.getSprite());

        if(choosingCell.x != -1)
        {
            
            for(int i = choosingCell.x; i <= choosingCell.x + 1; i++)
                for(int j = choosingCell.y; j <= choosingCell.y + 1; j++)
                {
                    verLine2.setPosition(j * (1 + ICON_WIDTH * SCALE) + SHILF_RIGHT - 2, 
                                        i * (1 + ICON_HEIGHT * SCALE) + SHILF_DOWN - 2);
                    horLine2.setPosition(j * (1 + ICON_WIDTH * SCALE) + SHILF_RIGHT - 2, 
                                        i * (1 + ICON_HEIGHT * SCALE) + SHILF_DOWN - 2);

                    if(i != choosingCell.x + 1) GraphicsData::screen.draw(verLine2);
                    if(j != choosingCell.y + 1) GraphicsData::screen.draw(horLine2);
                }
        }
        
    }

    bool isChoosingCells(int x, int y)
    {
        x = (x - SHILF_RIGHT) / (int)(1 + ICON_WIDTH * SCALE);
        y = (y - SHILF_DOWN) / (int)(1 + ICON_HEIGHT * SCALE);

        choosingCell = sf::Vector2u(-1, -1);

        if(x < 0 || x >= 10) return false;
        if(y < 0 || y >= 10) return false;

        choosingCell = sf::Vector2u(y, x);
        return true;
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
        y = (y - SHILF_RIGHT) / (int)(1 + ICON_WIDTH * SCALE);
        x = (x - SHILF_DOWN) / (int)(1 + ICON_HEIGHT * SCALE);
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
        y = (y - SHILF_RIGHT) / (int)(1 + ICON_WIDTH * SCALE);
        x = (x - SHILF_DOWN) / (int)(1 + ICON_HEIGHT * SCALE);

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

    bool isOpenAround(int x, int y, bool &firstTry)
    {
        x = (x - SHILF_RIGHT) / (int)(1 + ICON_WIDTH * SCALE);
        y = (y - SHILF_DOWN) / (int)(1 + ICON_HEIGHT * SCALE);

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

    void RunTheClock()
    {
        BoardData::clock.restart();
        while(isPlaying) 
        {
            BoardData::time += BoardData::clock.restart();
        }
    }

    void Run(int n, int m, int k, std::string link = "null")
    {   
        bool firstTry = true;
        if(link !="null") INIT(link, firstTry);
        else INIT(n, m, k);
        

        GraphicsData::screen.clear(sf::Color::White);

        
        sf::Thread timing(&RunTheClock);
        timing.launch();

        isPlaying = false;
        while (GraphicsData::screen.isOpen())
        {
            isPlaying = true;
            if(isDead)
            {
                if(oldData) remove("data/saving.txt");
                isPlaying = false;
                draw();
                GraphicsData::screen.display();
                delay(2000);
                DeadScreen::Run();
                return ;
            }
            
            if(cellsLeft == 0 && mineLeft == 0)
            {
                if(oldData) remove("data/saving.txt");
                isPlaying = false;
                draw();
                GraphicsData::screen.display();
                delay(1000);
                WinningScreen::Run();
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
                        isPlaying = false;
                        saving();
                        GraphicsData::screen.close();
                        return ;

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
                            if(!isOpenCells(e.mouseButton.y, e.mouseButton.x, firstTry))
                                if(goback.isMouseInside(e.mouseButton.x, e.mouseButton.y))
                                {   
                                    isPlaying = false;
                                    goback.setStatus(0);
                                    saving();
                                    return ;
                                }
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
                    case sf::Event::MouseMoved:
                        if(!goback.isMouseInside(e.mouseMove.x, e.mouseMove.y))
                        {
                            isChoosingCells(e.mouseMove.x, e.mouseMove.y);
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
    Button up, down;
    sf::Text scroll;

    void INIT()
    {
        textureBackground.loadFromFile("data/background/ocean/startingscreen.jpg");   
        spriteBackground.setTexture(textureBackground);
        spriteBackground.setScale(0.342f, 0.2824f);
        logoTexture.loadFromFile("data/title/header.png");
                
        
        logoSize = logoTexture.getSize();
        logoPosition = sf::Vector2f((GraphicsData::WIDTH - logoSize.x) / 2.0, 110);

        logo.setTexture(logoTexture);
        logo.setPosition(logoPosition);

        scroll.setString("scroll down to get more option!");
        scroll.setFont(GraphicsData::font);
        scroll.setCharacterSize(32);
        scroll.setFillColor(sf::Color::White);
        scroll.setPosition(350, 260);

        up.addImage("data/button/up_arrow.png");

        down.addImage("data/button/down_arrow.png");

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
        const int shilfButHor = 130; // shilf button horizonal
        
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

        if(wheel != 0) GraphicsData::screen.draw(up.getSprite(GraphicsData::WIDTH / 2 - down.getW() / 2, 250));
        if(wheel != 2) GraphicsData::screen.draw(down.getSprite(GraphicsData::WIDTH / 2 - up.getW() / 2, 640));
        if(wheel == 0) GraphicsData::screen.draw(scroll);
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
                        if(hard.isMouseInside(e.mouseButton.x, e.mouseButton.y))
                        {
                            hard.setStatus(0);
                            GameScreen::Run(32, 32, 256);
                            return ;
                        }
                        if(custom.isMouseInside(e.mouseButton.x, e.mouseButton.y) && wheel != 0)
                        {   
                            custom.setStatus(0);
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
    sf::Text noData;
    sf::RectangleShape noDataBackground;

    bool isFileExist(char *link)
    {
        FILE *file;
        if (file = fopen(link, "r")) 
        {
            fclose(file);
            return true;
        }
        return false;
    }
    
    void INIT()
    {
        textureBackground.loadFromFile("data/background/ocean/startingscreen.jpg");   
        spriteBackground.setTexture(textureBackground);
        spriteBackground.setScale(0.342f, 0.2824f);

        logoTexture.loadFromFile("data/title/header.png");
        logoSize = logoTexture.getSize();

        logoPosition = sf::Vector2f((GraphicsData::WIDTH - logoSize.x) / 2.0, 110);

        logo.setTexture(logoTexture);
        logo.setPosition(logoPosition);

        newGame.addImage("data/button/newgame.png");
        newGame.addImage("data/button/choosing_newgame.png");

        _continue.addImage("data/button/continue.png");
        _continue.addImage("data/button/choosing_continue.png");

        goback.addImage("data/button/goback.png");
        goback.addImage("data/button/choosing_goback.png");

        noData.setFont(GraphicsData::font);
        noData.setCharacterSize(32);
        noData.setFillColor(sf::Color::White);
        noData.setPosition(370, 330);
        noData.setString("You have no recent games yet!");

        noDataBackground.setSize(sf::Vector2f(600, 120));
        noDataBackground.setFillColor(sf::Color(0, 88, 122));
        noDataBackground.setPosition(300, 290);
    }

    void draw()
    {
        // draw background
        GraphicsData::screen.draw(spriteBackground);

        //draw "logo"
        GraphicsData::screen.draw(logo);

        const int shilfButVer = 0; // shilf button vertical
        const int shilfButHor = 130; // shilf button horizonal

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
                        if(_continue.isMouseInside(e.mouseButton.x, e.mouseButton.y))
                        {   
                            if(isFileExist("data/saving.txt"))
                            {
                                _continue.setStatus(0);
                                bool temp;
                                GameScreen::INIT("data/saving.txt", temp);
                                GameScreen::Run(-1, -1, -1, "data/saving.txt");
                            }else
                            {
                                
                                GraphicsData::screen.draw(noDataBackground);
                                GraphicsData::screen.draw(noData);
                                GraphicsData::screen.display();
                                delay(1300);
                            }
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
    const int shilfButHor = 130; // shilf button horizonal

    void INIT()
    {
    
        textureBackground.loadFromFile("data/background/ocean/startingscreen.jpg");   
        spriteBackground.setTexture(textureBackground);
        spriteBackground.setScale(0.342f, 0.2824f);
        

        logoTexture.loadFromFile("data/title/header.png");
        logoSize = logoTexture.getSize();
        logoPosition = sf::Vector2f((GraphicsData::WIDTH - logoSize.x) / 2.0, 110);
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

void Run()
{
    GraphicsData::INIT();
    
    StartingScreen::Run();
        
}
