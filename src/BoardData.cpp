#include <Data.hpp>

std::mt19937 rng(std::chrono::steady_clock().now().time_since_epoch().count());

//  declare constant
const CellType BoardData::SafeCells[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
const CellType BoardData::FlagCell = 9;
const CellType BoardData::QuestionCell = 10;
const CellType BoardData::MineCell = 11;


//  variable
std::vector<CellType> BoardData::Board;
int BoardData::Columns, BoardData::Rows;
int BoardData::Mines;

std::vector<std::vector<int> > BoardData::Components;
std::vector<int> BoardData::ComponentID;


//  change 2d cell point into 1d board 
int GetBoardPos(Cell Point)
{
    return Point[0] * BoardData::Columns + Point[1];
}

//  change 1d board into 2d cell
Cell GetCoordinatePos(int i)
{
    return Cell{i / BoardData::Columns,  i % BoardData::Columns};
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
            if(nx < 0 || nx >= BoardData::Columns) continue;
            if(ny < 0 || ny >= BoardData::Rows) continue;
            if(BoardData::Board[GetBoardPos(Cell{nx, ny})] == BoardData::MineCell)
                res = res + 1;
        }
    }
    return res;
}

void BuildBoard(int n, int m, int k)
{
    BoardData::Columns = n;
    BoardData::Rows = m;
    BoardData::Mines = k; 
    BoardData::Board.resize(n * m, 0);

    for(int i = 0; i < BoardData::Mines; i++)
    {
        BoardData::Board[i] = BoardData::MineCell; 
    }
    std::shuffle(BoardData::Board.begin(), BoardData::Board.end(), rng);

    for(int i = 0; i < BoardData::Rows; i++)
    {
        for (int j = 0; j < BoardData::Columns; j++)
        {
            int id = GetBoardPos(Cell{i, j});
            if(BoardData::Board[id] == BoardData::MineCell) 
                continue;
            BoardData::Board[id] = CountMines(Cell{i, j});
        }
    }
}

void LoopOverComponent(int x, int y, int k)
{
    int id = GetBoardPos(Cell{x, y});
    if(x < 0 || x >= BoardData::Rows) return ;
    if(y < 0 || y >= BoardData::Columns) return ;
    if(BoardData::ComponentID[id] != -1) return ;

    BoardData::ComponentID[id] = k;
    BoardData::Components[k].push_back(id);
    
    if(BoardData::Board[GetBoardPos(Cell{x, y})] != 0) return ;

    LoopOverComponent(x - 1, y, k);
    LoopOverComponent(x + 1, y, k);
    LoopOverComponent(x, y - 1, k);
    LoopOverComponent(x, y + 1, k);

}

void SplitComponents()
{
    BoardData::ComponentID.resize(BoardData::Rows * BoardData::Columns, -1);
    BoardData::Components.push_back(std::vector<int> (0));

    for(int i = 0; i < BoardData::Rows; i++)
    {
        for(int j = 0; j < BoardData::Columns; j++)
        {
            int id = GetBoardPos(Cell{i, j});
            if(BoardData::Board[id] == BoardData::MineCell)
            {
                BoardData::ComponentID[id] = 0;
                BoardData::Components[0].push_back(id);
                continue;
            }
        }
    }

    for(int i = 0; i < BoardData::Rows; i++)
    {
        for(int j = 0; j < BoardData::Columns; j++)
        {
            int id = GetBoardPos(Cell{i, j});
            if(BoardData::ComponentID[id] != -1) continue;

            BoardData::Components.push_back(std::vector<int> (0));

            LoopOverComponent(i, j, BoardData::Components.size() - 1);
        }
    }

}

//  I have no idea with this
void BoardData::init(int n, int m, int k)
{
    BuildBoard(n, m, k);
    SplitComponents();
}

// and this :))))
void init()
{
    return BoardData::init(10, 8, 16);
}

// print variable to console
void BoardData::show()
{
    std::cout << "Columns: " << BoardData::Columns << "\t";
    std::cout << "Rows: " << BoardData::Rows << "\t";
    std::cout << "Mines: " << BoardData::Mines << "\n";
    for (int i = 0; i < BoardData::Rows; i++)
    {
        for(int j = 0; j < BoardData::Columns; j++)
            std::cout << std::setfill('0') << std::setw(2) << BoardData::Board[GetBoardPos(Cell{i, j})] << "\t";
        std::cout << std::endl;
    }

    std::cout << "Number of components: " << BoardData::Components.size() << std::endl;
    for(int i = 0; i < (int) BoardData::Components.size(); i++)
    {
        for(int j : BoardData::Components[i])
            std::cout << j << " ";
        std::cout << std::endl;
    }
}