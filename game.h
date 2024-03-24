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

private:
    char s_game[GRID_SIZE][GRID_SIZE];

};

#endif // GAME_H