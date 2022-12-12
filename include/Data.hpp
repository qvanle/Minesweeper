#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <array>
#include <iostream>
#include <iomanip>

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

    extern std::vector<std::vector<int> > Components;
    extern std::vector<int> ComponentID;
    void init(int n, int m, int k);
    void init();
    void show();
}


namespace GraphicsData
{
    extern std::vector<sf::Texture> icons;
    extern const int Width;
    extern const int Height;
}