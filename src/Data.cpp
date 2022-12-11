#include <Data.hpp>

namespace MyRandom
{
    std::mt19937 rng(std::chrono::steady_clock().now().time_since_epoch().count());
}

namespace BoardData
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

    std::vector<std::vector<int> > Components;
    std::vector<int> ComponentID;


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

    void BuildBoard(int n, int m, int k)
    {
        Columns = n;
        Rows = m;
        Mines = k; 
        Board.resize(n * m, 0);

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
                if(Board[id] == MineCell) 
                    continue;
                Board[id] = CountMines(Cell{i, j});
            }
        }
    }

    void LoopOverComponent(int x, int y, int k)
    {
        int id = GetBoardPos(Cell{x, y});
        if(x < 0 || x >= Rows) return ;
        if(y < 0 || y >= Columns) return ;
        if(ComponentID[id] != -1) return ;

        ComponentID[id] = k;
        Components[k].push_back(id);
        
        if(Board[GetBoardPos(Cell{x, y})] != 0) return ;

        LoopOverComponent(x - 1, y, k);
        LoopOverComponent(x + 1, y, k);
        LoopOverComponent(x, y - 1, k);
        LoopOverComponent(x, y + 1, k);

    }

    void SplitComponents()
    {
        ComponentID.resize(Rows * Columns, -1);
        Components.push_back(std::vector<int> (0));

        for(int i = 0; i < Rows; i++)
        {
            for(int j = 0; j < Columns; j++)
            {
                int id = GetBoardPos(Cell{i, j});
                if(Board[id] == MineCell)
                {
                    ComponentID[id] = 0;
                    Components[0].push_back(id);
                    continue;
                }
            }
        }

        for(int i = 0; i < Rows; i++)
        {
            for(int j = 0; j < Columns; j++)
            {
                int id = GetBoardPos(Cell{i, j});
                if(ComponentID[id] != -1) continue;

                Components.push_back(std::vector<int> (0));

                LoopOverComponent(i, j, Components.size() - 1);
            }
        }

    }

//  I have no idea with this
    void init(int n, int m, int k)
    {
        BuildBoard(n, m, k);
        SplitComponents();
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

        std::cout << "Number of components: " << Components.size() << std::endl;
        for(int i = 0; i < (int) Components.size(); i++)
        {
            for(int j : Components[i])
                std::cout << j << " ";
            std::cout << std::endl;
        }
    }
}