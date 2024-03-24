#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>

#define GRID_SIZE 9

class game
{
public:
    game();
    void getBoard(char (&board)[GRID_SIZE][GRID_SIZE]);
    void setBoard(char (&board)[GRID_SIZE][GRID_SIZE]);
    void setBoardFromFile(std::string fileName);
    void clearBoard();
    void printBoard();
    char getCell(int row, int col);
    bool isBoardComplete();
    bool isValidCell(int row, int col);
    bool isBoardValid();
    bool inRow(char value, int row, int col);
    bool inCol(char value, int row, int col);
    bool inBox(char value, int row, int col);


private:
    char s_game[GRID_SIZE][GRID_SIZE];

};

#endif // GAME_H
