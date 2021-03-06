// Sudoku.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <boost/multi_array.hpp>
#include <string>
#include <tuple>

//type definiton for 2D matrix using boost library
typedef boost::multi_array<int, 2> grid_type;
typedef grid_type::index index;

void PrettyPrintPuzzle(grid_type myPuzzle) {

    for (index i = 0; i != 9; ++i) {
        for (index j = 0; j != 9; ++j) {
            if (myPuzzle[i][j] == 0) std::cout << "_ ";
            else std::cout << myPuzzle[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

}


void PrintPuzzle(grid_type myPuzzle){

    for (index i = 0; i != 9; ++i){
        for (index j = 0; j != 9; ++j) {
            std::cout << myPuzzle[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

}

std::string DefinePuzzle(){
    //Define Sudoku Puzzle to solve
    //Use 0 to indicate empty cell

    //Easy Puzzle
    //std::string puzzleRaw_{};
    //puzzleRaw_.append("400689200");
    //puzzleRaw_.append("380400600");
    //puzzleRaw_.append("201300800");
    //puzzleRaw_.append("008067032");
    //puzzleRaw_.append("056090080");
    //puzzleRaw_.append("030850096");
    //puzzleRaw_.append("600000175");
    //puzzleRaw_.append("004021008");
    //puzzleRaw_.append("807006000");

    //Difficult Puzzle
    std::string puzzleRaw_{};
    puzzleRaw_.append("000000200");
    puzzleRaw_.append("300040000");
    puzzleRaw_.append("010008900");
    puzzleRaw_.append("420050090");
    puzzleRaw_.append("007010500");
    puzzleRaw_.append("000600020");
    puzzleRaw_.append("070103000");
    puzzleRaw_.append("280700000");
    puzzleRaw_.append("503000800");

    return puzzleRaw_;
}

grid_type LoadPuzzle() {
    grid_type puzzleInitial(boost::extents[9][9]);
    
    std::string puzzleRaw = DefinePuzzle();

    // Read in puzzle from puzzleRaw string
    for (index i = 0; i != 9; ++i)
        for (index j = 0; j != 9; ++j)
            puzzleInitial[i][j] = std::stoi(puzzleRaw.substr(i * 9 + j, 1));
    
    return puzzleInitial;
}

bool PuzzleComplete(grid_type puzzle) {
 
    for (index i = 0; i != 9; ++i)
        for (index j = 0; j != 9; ++j)
            if (puzzle[i][j] == 0) return false;
    
    return true;
}

std::tuple<int, int> NextOpenPosition(grid_type puzzle) {
    for (index i = 0; i != 9; ++i)
        for (index j = 0; j != 9; ++j)
            if (puzzle[i][j] == 0) return std::make_tuple(i,j);
}

bool IsValidGuess(grid_type puzzle, int guess, int row, int column) {
    
    for (index i = 0; i != 9; ++i)
        if (puzzle[i][column] == guess) return false;

    for (index j = 0; j != 9; ++j)
        if (puzzle[row][j] == guess) return false;

    //TODO: Add sub matrix check

    int row_start, row_end, column_start, column_end;

    if (row <= 2) {
    row_start = 0;
    row_end = 2;
    }
    else if (row <= 5) {
    row_start = 3;
    row_end = 5;
    }
    else {
    row_start = 6;
    row_end = 8;
    }

    if (column <= 2) {
        column_start = 0;
        column_end = 2;
    }
    else if (column <= 5) {
        column_start = 3;
        column_end = 5;
    }
    else {
        column_start = 6;
        column_end = 8;
    }

    for (index i = row_start; i <= row_end; ++i)
        for (index j = column_start; j <= column_end; ++j)
            if (puzzle[i][j] == guess) return false;

    return true;
    
}

bool Solve(grid_type puzzle) {
    //Recursive Backtracking Solver
    
    //Base Case
    if (PuzzleComplete(puzzle)) {
        PrintPuzzle(puzzle);
        return true;
    }
 
    //Standard Case

    //identify row,column number of next open position
    auto[row, column] = NextOpenPosition(puzzle);

    for (int nextGuess = 1; nextGuess < 10; ++nextGuess) {
        if (IsValidGuess(puzzle, nextGuess, row, column)) {
            //try one choice i, if it works out, your are done.
            //if (Solve(puzzle)) return true;
            puzzle[row][column] = nextGuess;
            if (Solve(puzzle)) return true;
        }
       
        //otherwise unmake choice at the current level of recursion
        puzzle[row][column] = 0;
    }

    return false; //tried all choices, no solution found

}

int main() {

    // Create a 2D array named puzzle that is 9 rows x 9 columns
    grid_type puzzle(boost::extents[9][9]);

    puzzle = LoadPuzzle();

    PrettyPrintPuzzle(puzzle);

    Solve(puzzle);

    system("pause");
    return 0;
}
