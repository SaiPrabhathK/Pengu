#include<iostream>
#include<string>
#include<fstream>
#include<time.h>
#include<vector>
#include<queue>

using namespace std;
// import user-defined header file.
#include"gameboard.h"

const int FISH_GOAL = 20;

// HEURISTIC FUNCTION
// input: s: GameBoard state
// output: number of fish collected by following a specific plan.

// ************************************* //
int Heuristic_function(GameBoard& s)
{
    return s.fish_collected; // Heuristic function uses the number of fish collected by making a move to determine the best path.
}
// ************************************ //

// User defined structure to store priority values(fish collected by following a certain path), and the path itself.
struct frontier_node
{
    int value;
    vector<int> plan;

    frontier_node(){ value = 0; } // default constructor.

    frontier_node(const int v, const vector<int>& p) // Custom constuctor.
    {
        value = v;
        plan = p;
    }

    bool operator< (const frontier_node& rhs) const // Custom comparator for the priority queue to compare fish collected values for each path.
    {
        return value < rhs.value;

    }
};

// GBFS function returns the sequence of moves that make pengu collect atleast 20 fishes.
// input: s0: the initial game board config.
// output: a sequence of actions that pengu makes to collect atleast 20 fishes.
vector<int> Pengu_GBFS( GameBoard& s0 )
{
    priority_queue< frontier_node > frontier; // Priority queue of type frontier_node data structure defined above.
    bool done;
    vector<int> p0;
    vector<int> plan;
    GameBoard Sprime;
    vector<int> planPrime;
    vector<int> actionList;
    int best_direction = 0;
    frontier_node fnode;
    GameBoard s_clone;

    done = false;
    fnode.plan = p0;
    fnode.value = 0;
    frontier.push(fnode);
    while(!done)
    {
        fnode = frontier.top();
        plan = fnode.plan;
        frontier.pop();
        cout << "% " << plan << ":" << fnode.value << endl;
        Sprime.clone(s0);
        Sprime.executePlan(plan);

        if(Sprime.fish_collected >= FISH_GOAL)
        {
            done = true;
            return plan;
        }
        
        actionList = Sprime.validMoves();
        for(int i=0; i < actionList.size(); i++)
        {
            planPrime = plan;
            planPrime.push_back(actionList[i]);
            s_clone.clone(Sprime);
            s_clone.makeMove(actionList[i]);
            frontier.emplace( Heuristic_function(s_clone), planPrime);
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
    //state0.print_board2();

    solution = Pengu_GBFS( state0 ); // returns a vector of moves that pengu makes to collect atleast 8 fishes.
    cout << "-" << endl;
    cout << solution << endl;

    stateF.clone( state0 );
    stateF.executePlan( solution );
    cout << solution << endl;
    cout << stateF.fish_collected << endl;
    //stateF.print_board2();
    stateF.write_to_file(argv[2], solution);
    cout<<"Bye Program!"<<endl;
    return 0;
}