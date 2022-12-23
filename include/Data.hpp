#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <array>
#include <iostream>
#include <iomanip>
#include <string>

#include <SFML/Graphics.hpp>

using CellType = int;
using Cell = std::array<int, 2>;

namespace BoardData
{
    //  declare constant
    extern const CellType SafeCells[];
    extern const CellType FlagCell;
    extern const CellType QuestionCell;
    extern const CellType MineCell;

    //  variable
    extern std::vector<CellType> Board;
    extern int Columns, Rows;
    extern int Mines;
    extern std::vector<int> deadCells;

    extern sf::Clock time;
    extern sf::Time start;

    void init(int n, int m, int k);
    void init(int n, int m, int k, int x, int y);
    void init();
    void show();
}

namespace GraphicsData
{
    extern sf::Font font;
    extern int WIDTH;
    extern int HEIGHT;
    extern sf::RenderWindow screen;
    void INIT();
}
