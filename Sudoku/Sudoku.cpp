// Sudoku.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <boost/multi_array.hpp>
#include <string>

//type definiton for 2D matrix using boost library
typedef boost::multi_array<int, 2> grid_type;
typedef grid_type::index index;

void prettyPrintPuzzle(grid_type myPuzzle) {

    for (index i = 0; i != 9; ++i) {
        for (index j = 0; j != 9; ++j) {
            if (myPuzzle[i][j] == 0) std::cout << "_ ";
            else std::cout << myPuzzle[i][j] << " ";
        }
        std::cout << std::endl;
    }

}

void printPuzzle(grid_type myPuzzle){

    for (index i = 0; i != 9; ++i){
        for (index j = 0; j != 9; ++j) {
            std::cout << myPuzzle[i][j] << " ";
        }
        std::cout << std::endl;
    }

}

int main() {

    //Define Sudoku Puzzle to solve
    //Use 0 to indicate empty cell
    std::string puzzleRaw{};
    puzzleRaw.append("400689200");
    puzzleRaw.append("380400600");
    puzzleRaw.append("201300800");
    puzzleRaw.append("008067032");
    puzzleRaw.append("056090080");
    puzzleRaw.append("030850096");
    puzzleRaw.append("600000175");
    puzzleRaw.append("004021008");
    puzzleRaw.append("807006000");

    // Create a 2D array named puzzle that is 9 rows x 9 columns
    grid_type puzzle(boost::extents[9][9]);

    // Read in puzzle from puzzleRaw string
    
    for (index i = 0; i != 9; ++i)
        for (index j = 0; j != 9; ++j)
            puzzle[i][j] = std::stoi(puzzleRaw.substr(i*9+j, 1));

    prettyPrintPuzzle(puzzle);

    system("pause");
    return 0;
}
