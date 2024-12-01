#include <iostream>
using namespace std;


// Function prototypes
bool is_valid(int puzzle[9][9], int val, int row, int col);   // Checks if a number can be placed in a cell  
bool solver(int puzzle[9][9], int row, int col); // Solves the Sudoku puzzle using backtracking

int main() {
    const int size = 9;  // Size of the Sudoku grid (9x9)

    int puzzle[size][size] = {
        {0, 0, 8, 0, 6, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 7, 0, 3, 0},
        {6, 1, 0, 5, 0, 0, 2, 0, 0},   // Represents the Sudoku puzzle grid with some cells pre-filled
        {4, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 5, 0, 0, 0, 6},
        {2, 9, 0, 6, 0, 0, 1, 0, 0},
        {9, 8, 0, 0, 3, 0, 0, 2, 0},
        {0, 0, 4, 9, 0, 0, 0, 0, 0},
        {0, 0, 5, 0, 0, 0, 8, 0, 0}
    };

    if (solver(puzzle, 0, 0)) {  // Starts solving the puzzle from the top-left corner


        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)   // Prints the solved puzzle row by row.
            {
                cout << puzzle[i][j] << " ";
            }
            cout << endl;
        }
    } 
    else {
        cout << "NO SOLUTIONS EXISTS!";
    }

    return 0;
}


// Recursive function to solve the puzzle
bool solver(int puzzle[9][9], int row, int col) {

    if (row == 9) // If all rows are processed, the puzzle is solved
    {
        return true;
    }

    else if (col == 9)  // If the current column exceeds 8, move to the next row
    {
        return solver(puzzle, row + 1, 0);
    }

    else if (puzzle[row][col] != 0)  // If the current cell is pre-filled, move to the next cell in the row
    {
        return solver(puzzle, row, col + 1);
    }


    for (int i = 1; i <= 9; i++)  // HIt and trial by placing numbers 1 to 9 in the current empty cell
    {
        if (is_valid(puzzle, i, row, col))
        {
            puzzle[row][col] = i;  // Place the number

            if (solver(puzzle, row, col + 1)) // Recursively solve for the next cells
            {
                return true;  // If solved, return true
            }
            puzzle[row][col] = 0;  // If placing this number doesn't lead to a solution, backtrack
        }
    }
    return false;  // Return false if no valid number can be placed


}

// Function to check if a number is valid in a given cell
bool is_valid(int puzzle[9][9], int val, int row, int col) {

    int start_row, end_row, start_col, end_col;

    for (int i = 0; i < 9; i++) // Check if the number already exists in the current row
    {
        if (puzzle[row][i] == val) 
        {
            return false;
        }
    }

    for (int i = 0; i < 9; i++)// Check if the number already exists in the current column
    {
        if (puzzle[i][col] == val)
        {
            return false;
        }
    }

    // Determine the starting indices of the 3x3 subgrid
    start_row = (row / 3) * 3;
    end_row = start_row + 3;

    start_col = (col / 3) * 3;
    end_col = start_col + 3;

    //cout<<"Starting row: "<<start_row<<endl;
    //cout<<"Starting col: "<<start_col<<endl;

    for (int i = start_row; i < end_row; i++)  // Check if the number exists in the 3x3 subgrid
    {
        for (int j = start_col; j < end_col; j++)
        {
            if (puzzle[i][j] == val)
            {
                return false;
            }
        }
    }

    return true;  // Return true if the number is valid in the cel
}