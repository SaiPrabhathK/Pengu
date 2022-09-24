#include<iostream>
#include<string>
#include<fstream>
#include<time.h>
#include<vector>
#include<queue>

using namespace std;
// import user-defined header file.
#include"gameboard.h"

const int FISH_GOAL = 8;

// BFS function returns the sequence of moves that make pengu collect atleast 8 fishes.
// input: s0: the initial game board config.
// output: a sequence of actions that pengu makes to collect atleast 8 fishes.
vector<int> Pengu_BFS( GameBoard& s0 )
{
    deque< vector<int> > frontier;
    bool done;
    vector<int> p0;
    vector<int> plan;
    GameBoard Sprime;
    vector<int> planPrime;
    vector<int> actionList;

    done = false;
    frontier.push_back(p0);
    while(!done)
    {
        plan = frontier.front();
        frontier.pop_front();
        cout << "% " << plan << endl;
        Sprime.clone(s0);
        Sprime.executePlan(plan);

        if(Sprime.fish_collected >= FISH_GOAL)
        {
            done = true;
            return plan;
        }
        
        actionList = Sprime.validMoves();
        //cout << "a=" << actionList << actionList.size() << endl;
        for(int i=0; i < actionList.size(); i++)
        {
            planPrime = plan;
            planPrime.push_back(actionList[i]);
            //cout << "& " << planPrime << endl;
            frontier.push_back(planPrime);
        }
    }
    p0.push_back(-666);
    return p0;
}

// input: commandline arguments - input file name and output file name.
// output: performs BFS for pengu to collect atleast 8 fishes.
int main(int argc, char *argv[])
{
    cout<<"Hello Program!"<<endl;
    GameBoard state0, stateF;
    vector<int> solution;

    state0.read_from_file(argv[1]); // takes input file name from command line as input.
    state0.print_board2();

    solution = Pengu_BFS( state0 ); // returns a vector of moves that pengu makes to collect atleast 8 fishes.
    cout << "-" << endl;
    cout << solution << endl;

    stateF.clone( state0 );
    stateF.executePlan( solution );
    cout << solution << endl;
    cout << stateF.fish_collected << endl;
    stateF.print_board2();
    stateF.write_to_file(argv[2], solution);
    cout<<"Bye Program!"<<endl;
    return 0;
}