
#include<iostream>
#include<string>
#include<fstream>
#include<time.h>
#include<vector>
#include<queue>

using namespace std;

// A Table defining how Pengu changes its position accross the board depending on the direction. 
constexpr int MoveTable[10][2] = {{0, 0}, {1, -1}, {1, 0}, {1, 1}, {0, -1}, {0, 0}, {0, 1}, {-1, -1}, {-1, 0}, {-1, 1}};


// Class GameBoard stores the state of the game.
// read_from_file() reads from input text file and write_to_file()writes to the output text file.
// validMoves() to generate set of valid moves using information from MoveTable
// isDead() returns true whenever Pengu dies.
// makeMove() moves Pengu accross the grid in the input direction.
// executePlan() takes a sequence of moves as input and calls makeMove() to move Pengu accross the grid.
// clone() creates a snapshot of the class GameBoard
// print_board() prints the grid.
// print_board2() prints the grid with the updated Pengu location.
class GameBoard
{
    public:
        char** grid;
        int gridR, gridC;
        int pengurow;
        int pengucol;
        int fish_collected;
        int num_fish;

        GameBoard();
        void read_from_file(string filename);
        void print_board();
        void print_board2();
        vector<int> validMoves();
        bool isDead();
        void makeMove(int direction);
        void executePlan(vector<int> seq_actions);
        void clone( GameBoard& orginal );
        void write_to_file(string filename, vector<int> solution);
    
};

// constructor for class GameBoard with initialization.
GameBoard::GameBoard():grid{NULL},gridR{0},gridC{0},pengurow{0},pengucol{0},fish_collected{0},num_fish{0}
{}

// read_from_file() reads from input text file
// input: name of the input file from cmd line
// outcome: information in the game board is populated from input file. 
void GameBoard::read_from_file(string filename)
{
    ifstream ist;
    string line;
    char c;
    ist.open(filename);
    ist>>gridR>>gridC;
    cout<<gridR<<" "<<gridC<<endl;

    grid = new char*[gridR];
    for(int i = 0; i < gridR; i++)
        grid[i] = new char[gridC];

    getline(ist, line);
    for(int i = 0; i < gridR; i++)
    {
        getline(ist, line);
        for(int j = 0; j < gridC; j++)
        {
            c = line[j];
            if( c == 'P')
            {
                pengurow = i;
                pengucol = j;
                c = ' ';
            }
            if(c == '*')
            {
                num_fish++;
            }
            grid[i][j] = c;
        }
    }
}

// clone() creates a snapshot of the class GameBoard.
// input: an original game board to duplicate
// outcome: current game board is the copy of the original game board.
void GameBoard::clone( GameBoard& original )
{
    gridR = original.gridR;
    gridC = original.gridC;
    pengurow = original.pengurow;
    pengucol = original.pengucol;
    num_fish = original.num_fish;
    fish_collected = original.fish_collected;
    
    grid = new char*[gridR];
    for(int i = 0; i < gridR; i++)
        grid[i] = new char[gridC];

    for(int i = 0; i < gridR; i++)
    {
        for(int j = 0; j < gridC; j++)
        {
            grid[i][j] = original.grid[i][j];
        }
    }
}

// isDead() returns true whenever Pengu dies.
// input: position of pengu in the grid.
// output: returns true or false depending on whether pengu is alive or dead.
bool GameBoard::isDead()
{
    if((grid[pengurow][pengucol] == 'S') || (grid[pengurow][pengucol] == 'U')) return true;
    return false;
}

// print_board() prints the grid.
// input: character grid representing the board
// outcome: prints the board onto screen
void GameBoard::print_board()
{
    for(int i = 0; i < gridR; i++)
    {
        for(int j = 0; j < gridC; j++)
        {
            cout<<grid[i][j];
        }
        cout<<endl;
    }
    cout << "Pengu at " << pengurow << "," << pengucol << endl;
}

// print_board2() prints the grid with the updated Pengu location.
// input: character grid representing the board
// outcome: prints the board onto screen with updated pengu position
void GameBoard::print_board2()
{
    for(int i = 0; i < gridR; i++)
    {
        for(int j = 0; j < gridC; j++)
        {
            if (i == pengurow && j == pengucol){
                if (isDead()){
                    cout << 'X';
                }
                else
                    cout << 'P';
            }
            else
                cout<<grid[i][j];
        }
        cout<<endl;
    }
    cout << "Pengu at " << pengurow << "," << pengucol << " : " << fish_collected << endl;
}

// validMoves() to generate set of valid moves using information from MoveTable
// input: pengu's position
// output: generates a vector of valid moves pengu can make
vector<int> GameBoard::validMoves()
{
    vector<int> valid_moves;
    int r = 0; 
    int c = 0;

    if (!isDead()){
        for(int i = 1; i < 10; i++)
        {   
            if(i==5) continue;
            r = pengurow + MoveTable[i][0];
            c = pengucol + MoveTable[i][1];
            if((grid[r][c] != '#'))
            {
                valid_moves.push_back(i);
                //cout<<i<<' '<<r<<' '<<c<<endl;
            }
        }
    }
    return valid_moves;
}

// makeMove() moves Pengu accross the grid in the input direction.
// input: direction in which pengu has to move
// outcome: latest pengu;s position after making a move and updated fish_collected count.
void GameBoard::makeMove(int direction)
{
    int r = pengurow + MoveTable[direction][0];
    int c = pengucol + MoveTable[direction][1];
    bool stop = false;
    while(!stop)
    {
        if(grid[r][c] == '#')
            stop = true;
        else
        {
            pengurow = r;
            pengucol = c;
            if(grid[r][c] == '0')
                stop = true;
            else if((grid[r][c] == 'U')||(grid[r][c] == 'S'))
                    stop = true;
            else if (grid[r][c] == '*')
            {
                    fish_collected++;
                    grid[r][c] = ' ';
            }
        }

        r = pengurow + MoveTable[direction][0];
        c = pengucol + MoveTable[direction][1];
    }
    //cout<<"Final"<<' '<<pengurow<<' '<<pengucol<<endl;
}

// executePlan() takes a sequence of moves as input and calls makeMove() to move Pengu accross the grid.
// input: vector of actions
// outcome: invokes makeMove() for the actions available in the input vector.
void GameBoard::executePlan(vector<int> seq_actions)
{
    for(int i = 0; i < seq_actions.size(); i++)
    {
        makeMove(seq_actions[i]);
    }
}

// write_to_file()writes to the output text file.
// input: output file name and vector of moves pengu makes to reach score of atleast 8.
// outcome: creates an output text file containing sequence of pengu's moves, its score and the final game board representation.
void GameBoard::write_to_file(string filename, vector<int> solution)
{
    ofstream ost;
    char c = ' ';
    ost.open(filename);
    for (int i=0; i<solution.size(); i++) {
        ost << solution[i];
    }
    ost << endl;

    ost << fish_collected << endl;
    for(int i = 0; i < gridR; i++)
    {
        for(int j = 0; j < gridC; j++)
        {
            if (i == pengurow && j == pengucol){
                if (isDead()){
                    ost << 'X';
                }
                else
                    ost << 'P';
            }
            else
                ost << grid[i][j];
        }
        ost << endl;
    }


}

// operator overloading to print vectors with << operator.
template <typename T>
ostream& operator<< (ostream &s, vector<T> v )
{
    s << "[";
    for (int i=0; i<v.size(); i++) {
        s << v[i] << ",";
    }
    s << "]";
    return s;
}