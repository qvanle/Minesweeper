#include <Button.hpp>
#include <InputBox.hpp>
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

namespace TutorialScreen
{
    sf::Texture textureBackground, logoTexture;
    sf::Sprite spriteBackground;
    sf::Vector2u logoSize;
    sf::Vector2f logoPosition;
    sf::Sprite logo;
    sf::RectangleShape board;
    Button goback;
    sf::Text content;

    void INIT()
    {
        textureBackground.loadFromFile("data/background/ocean/sunset.jpg");   
        spriteBackground.setTexture(textureBackground);


        logoTexture.loadFromFile("data/title/header.png");
        logoSize = logoTexture.getSize();
        logoPosition = sf::Vector2f((GraphicsData::WIDTH - logoSize.x * 0.6) - 50, 100);
        logo.setScale(0.6f, 0.6f);
        logo.setTexture(logoTexture);
        logo.setPosition(logoPosition);


        board.setSize(sf::Vector2f(600, 600));
        board.setPosition(50, 50);
        board.setFillColor(sf::Color(64, 64, 200));

        goback.addImage("data/button/goback.png");
        goback.addImage("data/button/choosing_goback.png");
        goback.setPosition(GraphicsData::WIDTH - goback.getW() - 160, 280);

        content.setString("\t\t  WELLCOME TO MY FIRST GAME\n\n"
        "This is the tutorial to play this game.\n"
        "-------------------------------------------------\n\n"
        "To open a cell, left click to that cell.\n\n"
        "I you not sure a cell is a mine, right click two \ntime and the cell'll become suspected cell.\n\n"
        "If you think a cell is a mine, right click to \nthat cell and the cell will be marked.\n\n"
        "To return a cell to its initial state, right\n-click it until it works.\n\n"
        "If the board are to big, use arrow button on\nkeyboard to move the board display.\n\n"
        "\n\n\n\n"
        "\t\t\t\t\t\t  Becareful and have fun!\n\n"
        );
        content.setFont(GraphicsData::font);
        content.setCharacterSize(24);
        content.setFillColor(sf::Color::White);
        content.setPosition(60, 60);
    }

    void draw()
    {
        GraphicsData::screen.draw(spriteBackground);
        GraphicsData::screen.draw(logo);
        GraphicsData::screen.draw(board);
        GraphicsData::screen.draw(goback.getSprite());
        GraphicsData::screen.draw(content);
    }

    void Run()
    {
        INIT();

        while(GraphicsData::screen.isOpen())
        {
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
                        goback.isMouseInside(e.mouseMove.x, e.mouseMove.y);
                        break;
                }
            }
        }
    }
}

namespace HighScoresScreen
{
    sf::Texture textureBackground, logoTexture;
    sf::Sprite spriteBackground;
    sf::Vector2u logoSize;
    sf::Vector2f logoPosition;
    sf::Sprite logo;
    sf::RectangleShape board;
    Button goback;
    std::vector<sf::Text> texts[4];
    sf::Text title;
    std::vector< std::array<float, 4> > scores;
    int px;
    int status;

    bool cmp(std::array<float, 4> a, std::array<float, 4> b)
    {
        return (double) a[0] / a[3] / a[3] * a[1] * a[2] > (double) a[0] / a[3] * a[1] / a[3] * a[2];
    }
    void INIT()
    {

        texts[0].clear();
        texts[1].clear();
        texts[2].clear();
        texts[3].clear();

        scores.clear();

        textureBackground.loadFromFile("data/background/ocean/sunset.jpg");   
        spriteBackground.setTexture(textureBackground);


        logoTexture.loadFromFile("data/title/header.png");
        logoSize = logoTexture.getSize();
        logoPosition = sf::Vector2f((GraphicsData::WIDTH - logoSize.x * 0.6) - 50, 100);
        logo.setScale(0.6f, 0.6f);
        logo.setTexture(logoTexture);
        logo.setPosition(logoPosition);


        board.setSize(sf::Vector2f(600, 600));
        board.setPosition(50, 50);
        board.setFillColor(sf::Color(64, 64, 200));

        goback.addImage("data/button/goback.png");
        goback.addImage("data/button/choosing_goback.png");
        goback.setPosition(GraphicsData::WIDTH - goback.getW() - 160, 280);

        title.setString("HIGH SCORE");
        title.setFont(GraphicsData::font);
        title.setCharacterSize(64);
        title.setFillColor(sf::Color::White);
        title.setPosition(190, 50);
        
        px = 0;
        status = 0;

        std::ifstream getData("data/.highscores");
        std::array<float, 4> temp;
        while(getData >> temp[0] >> temp[1] >> temp[2] >> temp[3])
        {   
            scores.push_back(temp);
        }
        getData.close();
        
        std::sort(scores.begin(), scores.end(), cmp);
        for(int i = 0; i < (int)scores.size(); i++)
        {
            for(int j = 0; j < 4; j++)
            {
                texts[j].emplace_back();
                texts[j].back().setFont(GraphicsData::font);
                texts[j].back().setCharacterSize(24);
                texts[j].back().setFillColor(sf::Color::White);
            }
            int y = 150 + 30 * i;
            texts[0].back().setString(std::to_string(i + 1));
            texts[0].back().setPosition(80, y);

            texts[1].back().setString(std::to_string((int)scores[i][0]) + "x" + std::to_string((int)scores[i][1]));
            texts[1].back().setPosition(200, y);

            texts[2].back().setString(std::to_string((int)scores[i][2]));
            texts[2].back().setPosition(350, y);

            texts[3].back().setString(std::to_string(scores[i][3]));
            texts[3].back().setPosition(500, y);
        }
        
    }
    
    void draw()
    {
        GraphicsData::screen.draw(spriteBackground);
        GraphicsData::screen.draw(logo);
        GraphicsData::screen.draw(board);
        GraphicsData::screen.draw(goback.getSprite());
        GraphicsData::screen.draw(title);
        for(int i = px; i < px + 16 && i < (int) texts[0].size(); i++)
        {
            GraphicsData::screen.draw(texts[0][i]);
            GraphicsData::screen.draw(texts[1][i]);
            GraphicsData::screen.draw(texts[2][i]);
            GraphicsData::screen.draw(texts[3][i]);
        }
    }
    
    void Scrolling(int delta)
    {
        if(delta > 0 && px != 0) px--;
        if(delta < 0 && px + 16 != (int) scores.size()) px++;
        for(int i = px; i < px + 16; i++)
        {
            int y = 150 + 30 * (i - px);
            texts[0][i].setPosition(80, y);

            texts[1][i].setPosition(200, y);

            texts[2][i].setPosition(350, y);

            texts[3][i].setPosition(500, y);

        }
    }
    void Run()
    {
        INIT();

        while(GraphicsData::screen.isOpen())
        {
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
                        goback.isMouseInside(e.mouseMove.x, e.mouseMove.y);
                        break;
                    case sf::Event::MouseWheelScrolled:
                        Scrolling(e.mouseWheelScroll.delta);
                }
            }
        }
    }
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

                        if(highScore.isMouseInside(e.mouseButton.x, e.mouseButton.y))
                        {
                            highScore.setStatus(0);
                            HighScoresScreen::Run();
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

    void Run(float result, int n, int m, int k)
    {
        std::ofstream honors;
        honors.open("data/.highscores", std::ios_base::app);
        honors << n << " " << m << " " << k << " " << result << "\n";
        honors.close();
        INIT();
        while(GraphicsData::screen.isOpen())
        {
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
                        if(highScore.isMouseInside(e.mouseButton.x, e.mouseButton.y))
                        {
                            highScore.setStatus(0);
                            HighScoresScreen::Run();
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

        openCells(x + 1, y + 1);
        openCells(x - 1, y + 1);
        openCells(x + 1, y - 1);
        openCells(x - 1, y - 1);
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
                WinningScreen::Run(BoardData::time.asSeconds(), BoardData::Rows, BoardData::Columns, BoardData::Mines);
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
    
    void TextBox(int &n ,int &m, int &k)
    {
        n = 10;
        m = 10;
        k = 16;
        sf::RectangleShape background;

        background.setSize(sf::Vector2f(800, 300));
        background.setFillColor(sf::Color(0, 64, 128));
        background.setPosition((1200-800) / 2, (700 - 400) / 2 + 100);

        InputBox cols, rows, mines;
        Button play;

        cols.setPosition(260, 300);
        cols.setTitle("Enter number of columns:\nMinimum is 10, maximum is 32");

        rows.setPosition(260, 400);
        rows.setTitle("Enter number of rows:\nMinimum is 10, maximum is 32");

        mines.setPosition(260, 500);
        mines.setTitle("Enter number of mines:");
        
        play.addImage("data/button/play.png");
        play.addImage("data/button/choosing_play.png");
        
        while(true)
        {
            GraphicsData::screen.draw(background);
            GraphicsData::screen.draw(cols.getBackground());
            GraphicsData::screen.draw(cols.getTitle());
            GraphicsData::screen.draw(cols.getNum());

            GraphicsData::screen.draw(rows.getBackground());
            GraphicsData::screen.draw(rows.getTitle());
            GraphicsData::screen.draw(rows.getNum());

            GraphicsData::screen.draw(mines.getBackground());
            GraphicsData::screen.draw(mines.getTitle());
            GraphicsData::screen.draw(mines.getNum());

            GraphicsData::screen.draw(play.getSprite(480, 560));

            GraphicsData::screen.display();
            sf::Event e;
            cols.setRange(10, 32);
            rows.setRange(10, 32);

            while(GraphicsData::screen.pollEvent(e))
            {
                switch(e.type)
                {
                    case sf::Event::Closed:
                        GraphicsData::screen.close();
                        return ;
                    case sf::Event::MouseButtonPressed:
                        if(cols.isMouseInside(e.mouseButton.x, e.mouseButton.y))
                            cols.setFocus(true);
                        else 
                            cols.setFocus(false), cols.setRange(10, 32);
                        if(rows.isMouseInside(e.mouseButton.x, e.mouseButton.y))
                            rows.setFocus(true);
                        else 
                            rows.setFocus(false), rows.setRange(10, 32);
                        if(mines.isMouseInside(e.mouseButton.x, e.mouseButton.y))
                            mines.setFocus(true);
                        else 
                            mines.setFocus(false);
                        if(play.isMouseInside(e.mouseButton.x, e.mouseButton.y))
                        {
                            play.setStatus(0);
                            n = rows.getValue();
                            m = cols.getValue();
                            k = mines.getValue();
                            if(n <= 0) n = 10;
                            if(m <= 0) m = 10;
                            if(k < 0) k = 0;
                            if(k > n * m) k = n * m;
                            return ;
                        }
                        break;
                    case sf::Event::MouseMoved:
                        play.isMouseInside(e.mouseMove.x, e.mouseMove.y);
                        break;
                    case sf::Event::KeyPressed:

                        rows.typing(e.key.code);
                        cols.typing(e.key.code);
                        mines.typing(e.key.code);
                        break;
                }
            }
        }

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
                            int n, m, k;
                            TextBox(n, m, k);
                            GameScreen::Run(n, m, k);
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
                        if(highScore.isMouseInside(e.mouseButton.x, e.mouseButton.y))
                        {
                            highScore.setStatus(0);
                            HighScoresScreen::Run();
                        }
                        if(tutorial.isMouseInside(e.mouseButton.x, e.mouseButton.y))
                        {
                            tutorial.setStatus(0);
                            TutorialScreen::Run();
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
