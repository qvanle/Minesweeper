#include <SystemVariables.hpp>

std::mt19937 rng(std::chrono::steady_clock().now().time_since_epoch().count());

//  declare constant
const CellType SysVar::SafeCells[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
const CellType SysVar::FlagCell = 9;
const CellType SysVar::QuestionCell = 10;
const CellType SysVar::MineCell = 11;


//  variable
std::vector<CellType> SysVar::Board;
int SysVar::Columns, SysVar::Rows;
std::vector<int> SysVar::deadCells;
int SysVar::Mines;


//  change 2d cell point into 1d board 
int GetBoardPos(Cell Point)
{
    return Point[0] * SysVar::Columns + Point[1];
}

//  change 1d board into 2d cell
Cell GetCoordinatePos(int i)
{
    return Cell{i / SysVar::Columns,  i % SysVar::Columns};
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
            if(nx < 0 || nx >= SysVar::Columns) continue;
            if(ny < 0 || ny >= SysVar::Rows) continue;
            if(SysVar::Board[GetBoardPos(Cell{nx, ny})] == SysVar::MineCell)
                res = res + 1;
        }
    }
    return res;
}

void BuildBoard(int n, int m, int k, int x = -1, int y = -1)
{
    SysVar::Columns = n;
    SysVar::Rows = m;
    SysVar::Mines = k; 

    SysVar::Board.clear();
    SysVar::Board.resize(n * m, 0);

    for(int i = 0; i < SysVar::Mines; i++)
    {
        SysVar::Board[i] = SysVar::MineCell; 
    }
    int loop = 20;
    do
    {
        std::shuffle(SysVar::Board.begin(), SysVar::Board.end(), rng);
    }while(CountMines(Cell{x, y}) != 0 && loop--);

    for(int i = 0; i < SysVar::Rows; i++)
    {
        for (int j = 0; j < SysVar::Columns; j++)
        {
            int id = GetBoardPos(Cell{i, j});
            if(SysVar::Board[id] == SysVar::MineCell) 
            {
                SysVar::deadCells.push_back(id);
                continue;
            }
            SysVar::Board[id] = CountMines(Cell{i, j});
        }
    }
}

//  I have no idea with this
void SysVar::init(int n, int m, int k)
{
    BuildBoard(n, m, k);
}

void SysVar::init(int n, int m, int k, int x, int y)
{
    BuildBoard(n, m, k, x, y);
}

// and this :))))
void SysVar::init()
{
    return SysVar::init(10, 10, 16);
}

// print variable to console
void SysVar::show()
{
    std::cout << "Columns: " << SysVar::Columns << "\t";
    std::cout << "Rows: " << SysVar::Rows << "\t";
    std::cout << "Mines: " << SysVar::Mines << "\n";
    for (int i = 0; i < SysVar::Rows; i++)
    {
        for(int j = 0; j < SysVar::Columns; j++)
            std::cout << std::setfill('0') << std::setw(2) << SysVar::Board[GetBoardPos(Cell{i, j})] << "\t";
        std::cout << std::endl;
    }
}