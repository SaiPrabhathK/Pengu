#include<iostream>
#include<string>
#include<fstream>
#include<time.h>
#include<vector>
#include<queue>

using namespace std;
// import user-defined header file.
#include"gameboard.h"

const int FISH_GOAL = 16;

// DFS function returns the sequence of moves that make pengu collect atleast 16 fishes if it hits the depth limit, else it calls Pengu_ID_DFS to increase the depth limit to test again.
// input: s0: the initial game board config, depth limit, and boolean reference called limit_hit (to check if the path length hit the depth limit)
// output: a sequence of actions that pengu makes to collect atleast 16 fishes.
vector<int> Pengu_Bounded_DFS( GameBoard& s0, int depth_limit, bool& limit_hit)
{
    deque< vector<int> > frontier;
    bool done;
    vector<int> p0;
    vector<int> plan;
    GameBoard Sprime;
    vector<int> planPrime;
    vector<int> actionList;

    done = false;
    limit_hit = false;
    frontier.push_back(p0);
    while(!frontier.empty())
    {

        plan = frontier.back();
        frontier.pop_back();
        //cout << "% " << plan << endl;
        Sprime.clone(s0);
        Sprime.executePlan(plan);
        actionList = Sprime.validMoves();

        if (plan.size() == depth_limit)
        {
            

            if(Sprime.fish_collected >= FISH_GOAL)
            {
                done = true;
                return plan;
            }
        
            if(actionList.size() > 0)
            {
                limit_hit = true;
            }
        
        }
        else
        {
            for(int i=0; i < actionList.size(); i++)
            {
                planPrime = plan;
                planPrime.push_back(actionList[i]);
                //cout << "& " << planPrime << endl;
                frontier.push_back(planPrime);
            }
        }
    }
    plan.clear();
    return plan;
}

// Pengu_ID_DFS function iteratively calls the DFS function to find a path that gives Pengu a chance to collect atleast 16 fish.
// input: s0: the initial game board config
// output: a sequence of actions that pengu makes to collect atleast 16 fishes.
vector<int> Pengu_ID_DFS( GameBoard& s0 )
{
    bool hit;
    int depth = 0;
    vector<int> res;

    do 
    {
        cout<< "depth = "<< depth<<endl;
        res = Pengu_Bounded_DFS( s0, depth, hit);
        //cout<<res<< res.size() << endl;
        if(res.size() > 0)
        {
            cout << "Plan found!!" << endl;
            return res;
        }
        depth++;
    }
    while(hit);

    cout << "ID_DFS failed" << endl;
    return res;

}

// input: commandline arguments - input file name and output file name.
// output: performs BFS for pengu to collect atleast 8 fishes.
int main(int argc, char *argv[])
{
    cout<<"Hello Program!"<<endl;
    GameBoard state0, stateF;
    bool hit = false;
    vector<int> solution;

    state0.read_from_file(argv[1]); // takes input file name from command line as input.
    //state0.print_board2();

   // returns a vector of moves that pengu makes to collect atleast 16 fishes.
    solution = Pengu_ID_DFS( state0 );
    cout << "-" << endl;
    cout << boolalpha << hit << " " << solution << endl;

    stateF.clone( state0 );
    stateF.executePlan( solution );
    cout << solution << endl;
    cout << stateF.fish_collected << endl;
    //stateF.print_board2();
    stateF.write_to_file(argv[2], solution);
    cout<<"Bye Program!"<<endl;
    return 0;
}


