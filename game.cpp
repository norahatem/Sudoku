#include "game.h"

game::game() {
    for(int row = 0; row<9;row++){
        for(int col = 0; col<9;col++){
            s_game[row][col] = '0';
        }
    }

    //We don't need the constructor to read from a specified file, only initialize an empty board
}

void game::getBoard(char (&board)[GRID_SIZE][GRID_SIZE]){
    //code to copy the board into a board passes to the function
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            board[row][col] = s_game[row][col];
        }
    }
}
void game::setBoard(char (&board)[GRID_SIZE][GRID_SIZE]){
    //use a board passed to the function to populate the array
    for(int row = 0; row<GRID_SIZE; row++){
        for(int col = 0; col<GRID_SIZE; col++){
            s_game[row][col] = board[row][col];
        }
    }
}
void game::setBoardFromFile(std::string fileName){
    //code to set read the board from a file
    char Buffer;
    std::string line;
    int row = 0;
    std::ifstream MyReadFile(fileName);
    while (getline(MyReadFile, line)) {
        for(int col =0; col< GRID_SIZE; col++){
            Buffer = line[col];
            s_game[row][col] = Buffer;
        }
        row++;
    }
    MyReadFile.close();
}

void game::clearBoard(){
    //code to clear the board by setting all componenets of array to zero
    for(int row = 0; row<GRID_SIZE; row++){
        for(int col = 0; col<GRID_SIZE; col++){
            s_game[row][col] = '0';
        }
    }
}

void game::printBoard(){
    //code to print board in the dubugging console for debugging reasons
    for(int i =0;i<GRID_SIZE;i++){
        for(int j=0;j<GRID_SIZE;j++){
            qDebug() << s_game[i][j];
        }
        qDebug() << "\n";
    }
}

char game::getCell(int row, int col){
    return s_game[row][col];
}

//check if the board is filled with values
bool game::isBoardComplete(){
    for(int row = 0; row <9; row++){
        for(int col = 0; col<9; col++){
            if(s_game[row][col] == '0')
                return false;
        }
    }
    return true;
}

//check if a cell value is valid
bool game::isValidCell(int row, int col){
    char value = s_game[row][col];

    // Skip the check for empty cells
    if (value == '0')
        return true;

    for(int i = 0; i< GRID_SIZE; i++){
        //check if number is in row
        if(s_game[row][i] == value && i != col)
            return false;

        //check if number is in col
        if (s_game[i][col] == value && i != row)
            return false;
    }

    //to implement the checking of the cell in the small box, you need to
    //identify the starting point of the box whether it is the x direction
    //or y direction
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;

    //code to check from start row and column to 3 cells plus which is the small box
    for(int i = startRow; i< startRow + 3; i++){
        for(int j = startCol; j< startCol + 3; j++){
            if(s_game[i][j] == value && (i != row || j!=col))
                return false;
        }
    }
    return true;
}


bool game::isBoardValid(){
    for(int row = 0; row<GRID_SIZE; row++){
        for(int col =0;col<9; col++){
            if(!isValidCell(row, col))
                return false;
        }
    }
    return true;
}

void game::setCell(char value, int row, int col){
    s_game[row][col] = value;
}
