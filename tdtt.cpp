//19/02/2021: I started this project about a week ago, its a 3d version of tic tac toe I invented in high school where you can either win by winning on one of the grids with the classic rules, or by having the same position on each grid (which, if you superpose the grids makes a line in the 3rd dimension). The idea here was to work on bit manipulation instead of using a simple 3d matrix;
#include <iostream>
#include <bitset>
#include <cmath>
using namespace std;

int display(int g1, int g2)
{
	int i, j, k;
	//simply displays the first 3 bits, crates a new line adn creates a new line evry 3 lines to represent the 3 grids
	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			for(k=0; k<3; k++)
			{
				if(g1 & 1 == 1)
				{
					cout << "X";
				}
				else if(g2 & 1 ==1)
				{
					cout << "O";
				}
				else
				{
					cout << "+";
				}
				g1 = g1 >> 1;
				g2 = g2 >> 1;
			}
			cout << "\n";
		}
		cout << "\n";
	}
}

bool check(int g)
{
	//the idea here is to compare winning patterns to the 3d grid in 3d3t this means either a line, a column or a diagonal on one of the grids
	//or a column in 3d that is the same position on each grid (no 3d diagonals)
	//the patterns correspond to the following numbers:
	int line = 7;
	int col = 73;
	int rdiag = 273;
	int ldiag = 21;
	int tdcol = 262657;	
	for(int i=0; i<3; i++) //browse every matrix
	{
		for(int j=0; j<9; j++) //browse every cell
		{
			if(i == 0 && (g & tdcol) == tdcol) //only check for 3d lines from the first grid
			{
				//cout << "\ntdcol \n";
				return true;
			}
			if(j%3 == 0 && (g & line) == line) //check for the pattern when on the right edge of the grid
			{
				//cout << "\nline \n";
				return true;
			}
			if(j<3 && (g & col) == col) //check for columns when on the bottom of the grid
			{
				//cout << "\ncol \n";
				return true;
			}
			if(j == 0 && (g & rdiag) == rdiag)
			{
				//cout <<"\ndiag \n";
				return true;
			}
			if(j == 2 && (g & ldiag) == ldiag)
			{
				//cout <<"\ndiag \n";
				return true;
			}
			g = g >> 1;
		}
	}
	return false;
}

bool check_input(int in)
{
	if(in>=0 && in<=2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	int a[] = {0, 0}; //three 3x3 grids can be represented as one array of lenght 27 of values either true or false (check or unchecked) we can store that in the 32 bits of an int, one per player
	int turn = 0;
	int mat, row, col, pos, mask, play;
	do
	{
		play = turn % 2; //1 or 0, alternates
		cout << "Player " << play << "\n";
		cout << "grid: ";
		cin >> mat;
		cout << "row: ";
		cin >> row;
		cout << "column: ";
		cin >> col;
		cout << "\n";
		pos = 9*mat + 3*row + col; //the nth bit the player wants to change
		mask = pow(2,pos); //to verify if the cell is already taken
		int compare = a[0]&mask + a[1]&mask; //verify the position isnt already taken by either player
		if(compare == 0 && check_input(mat) && check_input(row) && check_input(col)) //check for conflicts
		{
			a[play] += mask;
			if(check(a[play]) == true)
			{
				cout << "player " << play << " wins \n";
				display(a[0], a[1]);
				return 0;
			}
			turn += 1; //chqnges player
			display(a[0], a[1]);
		}
		else
		{
			cout << "invalid \n";
		}
	} while(check(a[0]) == check(a[1])); //they should both be false
	display(a[0], a[1]);
	return 0;
}
