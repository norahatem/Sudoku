#ifndef SUDOKU_H
#define SUDOKU_H

#include <bits/stdc++.h>
using namespace std;

class Sudoku
{
public:
    int **mat;
    int N;
    // number of columns/rows.

    int SRN;
    // square root of N

    int K;
    // No. Of missing digits

    // Constructor
    Sudoku(int N, int K);

    // destructor
    ~Sudoku();

    // Sudoku Generator
    void fillValues();

    // Fill the diagonal SRN number of SRN x SRN matrices
    void fillDiagonal();

    // Returns false if given 3 x 3 block contains num.
    bool unUsedInBox(int rowStart, int colStart, int num);

    // Fill a 3 x 3 matrix.
    void fillBox(int row, int col);

    // Random generator
    int randomGenerator(int num);

    // Check if safe to put in cell
    bool CheckIfSafe(int i, int j, int num);

    // check in the row for existence
    bool unUsedInRow(int i, int num);

    // check in the row for existence
    bool unUsedInCol(int j, int num);

    // A recursive function to fill remaining
    // matrix
    bool fillRemaining(int i, int j);

    // Remove the K no. of digits to
    // complete game
    void removeKDigits();

    // Print sudoku
    void printSudoku();

    //write board to file
    void writeToFile(const string &filename);

};

// This code is contributed by Aarti_Rathi


#endif // SUDOKU_H
