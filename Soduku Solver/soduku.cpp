#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <istream>
#include <conio.h>

using namespace std;

#define empty 0
#define N 9

bool isGridSafe(int grid[N][N], int row, int col, int num);
bool isEmptyLocation(int grid[N][N], int& row, int& col);

/* assign values to all the zero (not assigned) values for Sudoku solution
 */

bool SolveSudoku(int grid[N][N])
{
	int row, col;
	if (!isEmptyLocation(grid, row, col))
		return true;
	for (int num = 1; num <= 9; num++)
	{
		if (isGridSafe(grid, row, col, num))
		{
			grid[row][col] = num;
			if (SolveSudoku(grid))
				return true;
			grid[row][col] = empty;
		}
	}
	return false;
}

/* Check for entries that don't have a value. */
bool isEmptyLocation(int grid[N][N], int& row, int& col)
{
	for (row = 0; row < N; row++)
		for (col = 0; col < N; col++)
			if (grid[row][col] == empty)
				return true;
	return false;
}


/* Returns whether the assigned entry n in the particular row matches
   the given number num. */

bool UsedInRow(int grid[N][N], int prow, int number)
{
	for (int col = 0; col < N; col++)
		if (grid[prow][col] == number)
			return true;
	return false;
}

/* Returns true if the number num matches any number in the column */

bool UsedInCol(int grid[N][N], int pcol, int number)
{
	for (int row = 0; row < N; row++)
		if (grid[row][pcol] == number)
			return true;
		else
			return false;
}

//Check if the entry used already in the grid box

bool UsedInBox(int grid[N][N], int boxBeginRow, int boxBeginCol, int number)
{
	bool tf = false;
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (grid[row + boxBeginRow][col + boxBeginCol] == number)
				tf = true;
	return tf;
}

/* Checks if num can be assigned to a given prow,pcol location. */

bool isGridSafe(int grid[N][N], int prow, int pcol, int number)
{
	return !UsedInRow(grid, prow, number) && !UsedInCol(grid, pcol, number) &&
		!UsedInBox(grid, prow - prow % 3, pcol - pcol % 3, number);
}

/* print result  */

void printResult(int finalgrid[N][N])
{
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
			cout << finalgrid[row][col] << "  ";
		cout << endl;
	}
}

/* Main */

int main()
{
	
	cout << "***************SODUKU SOLVER**************" << endl;

	char soduku[N][N];

	cout << "Enter the available value for grid." << endl;
	cout << "For the blank space, Enter either * or 0" << endl;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << "_\b"; soduku[i][j] = _getch(); cout << soduku[i][j] << " ";  // For gcc , try cin.get() instead of _getch
		}
		cout << endl;
	}
	
	int grid[N][N];
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (soduku[i][j] > '0' && soduku[i][j] <= '9') {
				grid[i][j] = soduku[i][j] - '0';
			}
			else if (soduku[i][j] == '*' || soduku[i][j] == '0') {
				grid[i][j] = 0;
			}
			else {
				cout << "Wrong Input Given!!!" << endl;
				cout << "Please Try again......" << endl;
				cout << endl;
				main();
			}
		}
	}

	if (SolveSudoku(grid) == true) {
		cout << "The answer is as follows: " << endl;
		printResult(grid);
	}
	else{
		cout << "No solution found" << endl;
	}

	return 0;
}