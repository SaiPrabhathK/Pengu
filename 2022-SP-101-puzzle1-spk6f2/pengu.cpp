#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <ctype.h>
#include<time.h>

using namespace std;

int rows = 0, cols = 0;
int pi = 0, pj = 0, num_fish = 0;
char* arr;
bool pengu_alive = 1, pengu_dead = 0;
int fish_collected = 0;
int valid_moves[8] = { 0 };
int count_of_valid_moves = 0;
int h = 0;
int random_move = 0;
int moves_made_count = 0, moves_made_array [6] = { 0 };

void print_valid_moves() // Prints the valid moves generated for each turn.
	{
		h=0;
		while(h < count_of_valid_moves)
		{
			cout<<valid_moves[h];
			h++;
		}
		cout<<"\n"<<"No. of moves in the valid_moves array: "<<h;
	}

void print_board()
{
	cout << endl;
	for (int i = 0; i < rows; i++) 
	{
        for (int j = 0; j < cols; j++) {
            cout << *(arr + i * cols + j);
        }
        cout << endl;
    }
}

void Gen_Valid_Moves() // From the Pengu's position, checks and generates an array of valid moves Pengu can make.
	{
		valid_moves[8] = { 0 };
		count_of_valid_moves = 0;
		if(*(arr + (pi+1) * cols + (pj-1)) != '#')
		{
			valid_moves[count_of_valid_moves++] = 1;
		}
		if(*(arr + (pi+1) * cols + pj) != '#')
		{
			valid_moves[count_of_valid_moves++] = 2;
		}
		if(*(arr + (pi+1) * cols + (pj+1)) != '#')
		{
			valid_moves[count_of_valid_moves++] = 3;
		}
		if(*(arr + pi * cols + (pj-1)) != '#')
		{
			valid_moves[count_of_valid_moves++] = 4;
		}
		if(*(arr + pi * cols + (pj+1)) != '#')
		{
			valid_moves[count_of_valid_moves++] = 6;
		}
		if(*(arr + (pi-1) * cols + (pj-1)) != '#')
		{
			valid_moves[count_of_valid_moves++] = 7;
		}
		if(*(arr + (pi-1) * cols + pj) != '#')
		{
			valid_moves[count_of_valid_moves++] = 8;
		}
		if(*(arr + (pi-1) * cols + (pj+1)) != '#')
		{
			valid_moves[count_of_valid_moves++] = 9;
		}
		cout<<"count_of_valid_moves: "<<count_of_valid_moves<<"\n";
	}

void Random_Move_Gen() // Random Generator function chooses a move randomly from the available valid moves.
	{	random_move = 0;
		srand ( time(NULL) );
		int random_index = rand() % h;
		random_move = valid_moves[random_index];
		cout <<"\nRandom Move: "<< random_move;
	}

void Make_Move() // This function moves Pengu accross the board.
	{
		switch (random_move)
		{
			case 1: // Logic to move in direction 1.
			{
			cout<<"\nEntered Case 1\n";
				int i = pi + 1, j = pj - 1;
				while((i < rows) && (j >= 0))
				{
					char cell_value = *(arr + i * cols + j);
					if(cell_value == '#')
					{
						pi = i-1; pj = j+1;
						break; 
					}

					if((cell_value == '0'))
					{
						pi = i; pj = j;
						break;
					}

					if(cell_value == '*')
					{
						fish_collected+=1;
						*(arr + i * cols +j) = ' ';
					}

					if((cell_value == 'S') || (cell_value == 'U'))
					{
						pengu_alive = false; pengu_dead = true;
						pi = i; pj = j;
						break;
					}
					i+=1; j-=1;
				}
				print_board();
				break;
			}
			case 2: // Logic to move in direction 2.
			{
			cout<<"\nEntered Case 2 \n";
			int i = pi + 1, j = pj;
			while(i < rows)
			{
					char cell_value = *(arr + i * cols + j);
					if(cell_value == '#')
					{
						pi = i-1; pj = j;
						break; 
					}
					
					if((cell_value == '0'))
					{
						pi = i; pj = j;
						break;
					}

					else if(cell_value == '*')
					{
						fish_collected+=1;
						*(arr + i * cols +j) = ' ';
					}

					else if((cell_value == 'S') || (cell_value == 'U'))
					{
						pengu_alive = false; pengu_dead = true;
						pi = i; pj = j;
						break;
			
					}
					i+=1;
			}
			print_board();
			break;
			}
			case 3: // Logic to move in direction 3.
			{
			cout<<"\nEntered Case 3\n";
			int i = pi + 1, j = pj + 1;
				while(i < rows && j < cols)
				{
					char cell_value = *(arr + i * cols + j);
					if(cell_value == '#')
					{
						pi = i-1; pj = j-1;
						break; 
					}

					if((cell_value == '0'))
					{
						pi = i; pj = j;
						break;
					}

					if(cell_value == '*')
					{
						fish_collected+=1;
						*(arr + i * cols +j) = ' ';
					}

					if((cell_value == 'S') || (cell_value == 'U'))
					{
						pengu_alive = false; pengu_dead = true;
						pi = i; pj = j;
						break;
					}
					i+=1; j+=1;
				}
			print_board();
			break;
			}
			case 4: // Logic to move in direction 4.
			{
			cout<<"\nEntered Case "<<random_move<<" \n";
				int i = pi, j = pj - 1;
				while(j >= 0)
				{
					char cell_value = *(arr + pi * cols + j);
					if(cell_value == '#')
					{
						pi = i; pj = j+1;
						break; 
					}

					if((cell_value == '0'))
					{
						pi = i; pj = j;
						break;
					}

					if(cell_value == '*')
					{
						fish_collected+=1;
						*(arr + i * cols +j) = ' ';
					}

					if((cell_value == 'S') || (cell_value == 'U'))
					{
						pengu_alive = false; pengu_dead = true;
						pi = i; pj = j;
						break;
					}
					j-=1;
				}
			print_board();
			break;
			}
			case 6: // Logic to move in direction 6.
			{
			cout<<"\nEntered Case "<<random_move<<" \n";

				int i = pi, j = pj + 1;
				while(j < cols)
				{
					char cell_value = *(arr + pi * cols + j);
					if(cell_value == '#')
					{
						pi = i; pj = j-1;
						break; 
					}

					if((cell_value == '0'))
					{
						pi = i; pj = j;
						break;
					}

					if(cell_value == '*')
					{
						fish_collected+=1;
						*(arr + i * cols +j) = ' ';
					}

					if((cell_value == 'S') || (cell_value == 'U'))
					{
						pengu_alive = false; pengu_dead = true;
						pi = i; pj = j;
						break;
					}
					j+=1;
				}
			print_board();
			break;
			}
			case 7: // Logic to move in direction 7.
			{
			cout<<"\nEntered Case "<<random_move<<" \n";
			int i = pi - 1, j = pj - 1;
			while( (i >= 0) && (j >= 0))
			{
					char cell_value = *(arr + i * cols + j);
					if(cell_value == '#')
					{
						pi = i+1; pj = j+1;
						break; 
					}

					if((cell_value == '0'))
					{
						pi = i; pj = j;
						break;
					}

					if(cell_value == '*')
					{
						fish_collected+=1;
						*(arr + i * cols +j) = ' ';
					}

					if((cell_value == 'S') || (cell_value == 'U'))
					{
						pengu_alive = false; pengu_dead = true;
						pi = i; pj = j;
						break;
					}
					i-=1; j-=1;
			}
			print_board();
			break;
			}
			case 8: // Logic to move in direction 8.
			{
			cout<<"\nEntered Case "<<random_move<<" \n";
			int i = pi - 1, j = pj;
			while(i >= 0)
			{
					char cell_value = *(arr + i * cols + pj);
					if(cell_value == '#')
					{
						pi = i+1; pj = j;
						break; 
					}

					if((cell_value == '0'))
					{
						pi = i; pj = j;
						break;
					}

					if(cell_value == '*')
					{
						fish_collected+=1;
						*(arr + i * cols +j) = ' ';
					}

					if((cell_value == 'S') || (cell_value == 'U'))
					{
						pengu_alive = false; pengu_dead = true;
						pi = i; pj = j;
						break;
					}
					i-=1;
			}
			print_board();
			break;
			}
			case 9: // Logic to move in direction 9.
			{
			cout<<"\nEntered Case "<<random_move<<" \n";
			int i = pi - 1, j = pj + 1;
			while((i >= 0) && (j < cols))
			{
					char cell_value = *(arr + i * cols + j);
					if(cell_value == '#')
					{
						pi = i+1; pj = j-1;
						break; 
					}

					if((cell_value == '0'))
					{
						pi = i; pj = j;
						break;
					}

					if(cell_value == '*')
					{
						fish_collected+=1;
						*(arr + i * cols +j) = ' ';
					}

					if((cell_value == 'S') || (cell_value == 'U'))
					{
						pengu_alive = false; pengu_dead = true;
						pi = i; pj = j;
						break;
					}
					i-=1; j+=1;
			}
			print_board();
			break;
			}
		}
	}

int main(int argc, char *argv[])
{
	if(argc == 3)
	{

	string r, c;
	string first_line = " ";
	string board;
	cout<<"Enter Input File Name: \n";
	ifstream ist ; //create ifstream object named ist and pass the file to the stream.
	ist.open(argv[1]);
	if (ist.is_open())
	{
	getline(ist, first_line);
	int i=0; 
	string temp="";
	while(i<first_line.length())
	{
		if(first_line[i]!=' ')
		temp+=first_line[i];
		else
		{
    		r = temp;
    		temp = "";
    	}
		i++;
	}
	c=temp;
    rows = stoi(r);
    cols = stoi(c);
    cout<<rows<<" "<<cols;
    arr = new char[rows*cols]; // Initializes a dynamic char array of size rows X cols.
    int k=0;

	while(ist) //read each line of the game board 
	{

		getline(ist, board);

        for(int j =0; j < cols; j++)
        {

            *(arr + k*cols+j) = board[j];
			if(board[j]=='P')
			{
				pi = k;
				pj = j;
			}
			if(board[j]=='*')
			{
				num_fish+=1;
			}
        }
        k++;
	}
	}
	else cout << "Unable to open file." << endl;
    cout<<"\n"<<"num_fish: "<<num_fish<<endl;

     for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
 
            cout << *(arr + i * cols + j);
        }
        cout << endl;
    }

	*(arr + pi * cols + pj) = ' '; // Erase initial pengu position.
	while(moves_made_count < 6 || pengu_alive == true || fish_collected <= 4) // Until Pengu dies or collects all the fish or makes 6 moves, this loop
																			  // runs the following functions.
	{
		Gen_Valid_Moves(); // Gets all the valid moves Pengu can make from its position.
		print_valid_moves(); // Prints the list of valid directions Pengu can move in.
		Random_Move_Gen(); // Randomly chooses a valid move in a direction.
		Make_Move(); // Pengu moves in a direction.
		moves_made_array[moves_made_count] = random_move;
		moves_made_count += 1;
		cout<<endl<<"Moves made till now: "<<moves_made_count<<endl;
		
		if (moves_made_count == 6)
		{
			*(arr + pi * cols + pj) = 'P';
			break;
		}

		if(pengu_dead == true)
		{
			*(arr + pi * cols + pj) = 'X';
			break;
		}

		if(fish_collected == 4)
		{
			*(arr + pi * cols + pj) = 'P';
			break;
		}
	}
	cout<<"Moves made count: "<<moves_made_count<<endl;
	int element = 0;
	while(element < moves_made_count)
	{
		cout<<moves_made_array[element];
		element++;
	}
	cout<<"\nFinal Board: \n";
	print_board();
	ist.close();

	ofstream ost (argv[2]); // create ofstream object named ost and pass the file to the stream.
  	if (ost.is_open())
  	{
		if(moves_made_count == 0)
		{
			ost << moves_made_count << endl;
		}
		else
		{
		for(int i = 0; i < moves_made_count; i++)
			{
				ost << moves_made_array[i];
			}
			ost << endl;
			ost << fish_collected; // Write Final Score to the output file.
			ost << endl;
		for (int i = 0; i < rows; i++) 
		{
        	for (int j = 0; j < cols; j++) 
			{
        		ost << *(arr + i * cols + j); //Writes the board to the output file, character-by-character.
			}
			ost << endl;
    	}
		}
    	ost.close();
  	}
  	else cout << "Unable to open output file";
	}
	else 
		cout << "Enter commands in the format: file_name (type: executable) input_text_file output_text_file"<< endl;
	return 0;
}