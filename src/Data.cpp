#include "../include/Data.hpp"

namespace MyRandom
{
    std::mt19937 rng(std::chrono::steady_clock().now().time_since_epoch().count());
}

namespace Data
{   

//  declare constant
    using CellType = int; // can turn this into char i.e ...
    using Cell = std::array<int, 2>;

    const CellType SafeCells[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    const CellType FlagCell = 9;
    const CellType QuestionCell = 10;
    const CellType MineCell = 11;


//  variable
    std::vector<CellType> Board;
    int Columns, Rows;
    int Mines;


//  change 2d cell point into 1d board 
    int GetBoardPos(Cell Point)
    {
        return Point[0] * Columns + Point[1];
    }

//  change 1d board into 2d cell
    Cell GetCoordinatePos(int i)
    {
        return Cell{i / Columns,  i % Columns};
    }

//  Count number of mines around a safe cell
    int CountMines(Cell Point)
    {
        int x = Point[0];
        int y = Point[1];
        int res = 0;
        for(int dx = -1; dx <= 1; dx++)
        {
            for(int dy = -1; dy <= 1; dy++)
            {
                int nx = x + dx;
                int ny = y + dy;
                if(nx < 0 || nx >= Columns) continue;
                if(ny < 0 || ny >= Rows) continue;
                if(Board[GetBoardPos(Cell{nx, ny})] == MineCell)
                    res = res + 1;
            }
        }
        return res;
    }

//  I have no idea with this
    void init(int n, int m, int k)
    {
        Columns = n;
        Rows = m;
        Mines = k; 
        Board.resize(n * k, 0);

        
        for(int i = 0; i < Mines; i++)
        {
            Board[i] = MineCell; 
        }
        std::shuffle(Board.begin(), Board.end(), MyRandom::rng);

        for(int i = 0; i < Rows; i++)
        {
            for (int j = 0; j < Columns; j++)
            {
                int id = GetBoardPos(Cell{i, j});
                if(Board[id] == MineCell) continue;
                Board[id] = CountMines(Cell{i, j});
            }
        }
    }

// and this :))))
    void init()
    {
        return init(10, 8, 16);
    }

// print variable to console
    void show()
    {
        std::cout << "Columns: " << Columns << "\t";
        std::cout << "Rows: " << Rows << "\t";
        std::cout << "Mines: " << Mines << "\n";
        for (int i = 0; i < Rows; i++)
        {
            for(int j = 0; j < Columns; j++)
                std::cout << std::setfill('0') << std::setw(2) << Board[GetBoardPos(Cell{i, j})] << "\t";
            std::cout << std::endl;
        }
    }
}