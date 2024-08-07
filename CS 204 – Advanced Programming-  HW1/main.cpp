#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
using namespace std;
/******************************************************************************
Sabanci  University CS204 Advanced Programming Homework1 – Tile Movement Game
Coded by: Osman Kantarcioglu    -   30891   - Section:B2
Date: 20/02/2024
******************************************************************************/

/******************************************************************************
This function checks whether matrix is valid or not
These two sentences that describe input check is taken from homework document
1)program check for consistency of the number of characters in each row. In
    other words, all rows must be of the same length.
2)program check that the file only contains 4 lowercase letters and dash
    character as mentioned above. Any other letter/symbol (even blank character
    or blank lines) in a file will make that file invalid.
******************************************************************************/
bool isMatrixValid(const vector<vector<char>>& matrix) {
    //Firstly, check whether all rows have same length
    int rowLength = matrix[0].size();
    for (int idx = 0; idx < matrix.size(); ++idx) {
        if (matrix[idx].size() != rowLength) // if all rows do not have same length
        {
            return false;
        }
    }
    //Secondly, check whether all characters in a matrix are 4 lowercase letters or dash character
    for (int idx1 = 0; idx1 < matrix.size(); idx1++) {
        for (int idx2 = 0; idx2 < matrix[idx1].size(); ++idx2) {
            if ((matrix[idx1][idx2] != 'r') && (matrix[idx1][idx2] != 'l')
                && (matrix[idx1][idx2] != 'u') && (matrix[idx1][idx2] != 'd')
                && (matrix[idx1][idx2] != '-'))
            {
                return false;
            }
        }
    }
    //Else, if it passes first and second validity check, it is valid
    return true;
}
/******************************************************************************
This function displays content of the matrix
******************************************************************************/
void printMatrixContent(const vector<vector<char>>& matrix) {
    for (int idx1 = 0; idx1 < matrix.size(); ++idx1) {
        for (int idx2 = 0; idx2 < matrix[idx1].size(); ++idx2) {
            cout << matrix[idx1][idx2];
        }
        cout << endl;
    }
}
/******************************************************************************
This function is used to check whether matrix is empty
******************************************************************************/
bool isMatrixEmpty(const vector<vector<char>>& matrix) {
    for (int idx1 = 0; idx1 < matrix.size(); ++idx1) {
        for (int idx2 = 0; idx2 < matrix[idx1].size(); ++idx2) {
            if (matrix[idx1][idx2] != '-') {
                //if one of the element of the matrix is different than '-',matrix is not empty
                return false;
            }
        }
    }
    return true; // If all elements are '-', the matrix is empty
}
/******************************************************************************
This function is used to check whether SPECIFIC element of the matrix can move
******************************************************************************/
bool noMovementPossible(int rowInput, int columnInput, const vector<vector<char>>& matrix) {
    char direction = matrix[rowInput][columnInput];
    if (direction == '-')
    {
        return true;
    }
    else if (direction == 'u' && rowInput > 0 && matrix[rowInput - 1][columnInput] != '-')
    {
        //if direction is up and it is in the first row, there is a movement. Therefore, it does not check for u letter in which is in the first row. However, it works for other conditions.
        return true;
    }
    else if (direction == 'l' && columnInput > 0 && matrix[rowInput][columnInput - 1] != '-')
    {
        //if direction is left and it is in the first column, there is a movement. Therefore, it does not check for l letter in which is in the first column. However, it works for other conditions.
        return true;
    }
    else if (direction == 'r' && columnInput < matrix[0].size() - 1 && matrix[rowInput][columnInput + 1] != '-')
    {
        //if direction is right and it is in the last column, there is a movement. Therefore, it does not check for r letter in which is in the last column. However, it works for other conditions.
        return true;
    }
    else if (direction == 'd' && rowInput < matrix.size() - 1 && matrix[rowInput + 1][columnInput] != '-')
    {
        //if direction is down and it is in the last row, there is a movement. Therefore, it does not check for d letter in which is in the last row. However, it works for other conditions.
        return true;
    }
    return false;
}
/******************************************************************************
This function is used to check whether EVERY element of the matrix can move by using previously defined function
******************************************************************************/
bool noPossibleMovementForEveryCell(const vector<vector<char>>& matrix) {
    for (int idx1 = 0; idx1 < matrix.size(); ++idx1) {
        for (int idx2 = 0; idx2 < matrix[idx1].size(); ++idx2) {
            if (noMovementPossible(idx1, idx2, matrix) == false) { //If any movement exists, return false.
                return false;
            }
        }
    }
    return true;
}
/******************************************************************************
This function is used to get coordinate input from the user
******************************************************************************/
void getCoordinateInput(int& rowInput, int& columnInput) {
    cout << "Please enter the row and column of the tile that you want to move:" << endl;
    cin >> rowInput >> columnInput;
}
/******************************************************************************
This function checks whether keyboard input is correct
******************************************************************************/
bool isInputCorrect(int rowInput, int columnInput, const vector<vector<char>>& matrix) {//matrix
    int biggestRowIndex = matrix.size() - 1;
    int biggestColumnIndex = matrix[0].size() - 1;
    if (rowInput < 0 || columnInput < 0 || rowInput > biggestRowIndex || columnInput > biggestColumnIndex) {
        return false;
    }
    else
    {
        return true;
    }
}
/******************************************************************************
This function is used to check whether the cell can drop off. It checks both first and second condition.
 1)It returns true when current location on the edge of the matrix and cell can drop
 2)It also return true path in the cell's direction is clear ALL THE WAY
******************************************************************************/
bool isPathClear(int rowInput, int columnInput, const vector<vector<char>>& matrix) {
    char direction = matrix[rowInput][columnInput];
    if (direction == 'u')
    {
        //To check upper cells, we need to decrease the row coordinate when column coordinate keeps same
        for (int idx = rowInput - 1; idx >= 0; --idx) {
            if (matrix[idx][columnInput] != '-')
            {
                return false;
            }
        }
    }
    else if (direction == 'l')
    {
        //To check left cells, we need to decrease the column coordinate when row coordinate keeps same
        for (int idx = columnInput - 1; idx >= 0; --idx) {
            if (matrix[rowInput][idx] != '-')
            {
                return false;
            }
        }
    }
    else if (direction == 'r')
    {
        //To check right cells, we need to increase the column coordinate when row coordinate keeps same
        for (int idx = columnInput + 1; idx < matrix[0].size(); ++idx) {
            if (matrix[rowInput][idx] != '-')
            {
                return false;
            }
        }
    }
    else if (direction == 'd')
    {
        //To check down cells, we need to increase the row coordinate when column coordinate keeps same
        for (int idx = rowInput + 1; idx < matrix.size(); ++idx) {
            if (matrix[idx][columnInput] != '-')
            {
                return false;
            }
        }
    }
    else if (direction == '-') {
        return false;
    }
    return true;
}
/******************************************************************************
This function is used to drop the cell from matrix when path is ALL THE WAY CLEAR or it is on the EDGE
******************************************************************************/
void processIfCellDrops(int rowInput, int columnInput, vector<vector<char>>& matrix) {
    cout << "Tile at (" << rowInput << "," << columnInput << ") has been moved." << endl;
    matrix[rowInput][columnInput] = '-';
    printMatrixContent(matrix);
}
/******************************************************************************
This function is used to check when path is NOT ALL THE WAY CLEAR but some MOVEMENTS EXIST.
It returns true when first cell in the direction path is '-'.
******************************************************************************/
bool atLeastOneEmptyCell(int rowInput, int columnInput, const vector<vector<char>>& matrix) {
    char direction = matrix[rowInput][columnInput];
    if (direction == 'u')
    {
        //If '-' exist at the upper cell when the direction is u, it can move
        if (matrix[rowInput - 1][columnInput] == '-')
        {
            return true;
        }
    }
    else if (direction == 'l')
    {
        //If '-' exist at the left cell when the direction is l, it can move
        if (matrix[rowInput][columnInput - 1] == '-')
        {
            return true;
        }
    }
    else if (direction == 'r')
    {
        //If '-' exist at the right cell when the direction is r, it can move
        if (matrix[rowInput][columnInput + 1] == '-')
        {
            return true;
        }
    }
    else if (direction == 'd')
    {
        //If '-' exist at the bottom cell when the direction is d, it can move
        if (matrix[rowInput + 1][columnInput] == '-')
        {
            return true;
        }
    }
    return false;
}
/******************************************************************************
This function is used to replace current cell with the new cell where it is blocked
******************************************************************************/
void replaceCurrentCellWithBlockedOne(int rowInput, int columnInput, vector<vector<char>>& matrix) {
    bool is_it_blocked = false;
    int currentRow = rowInput;
    int currentCol = columnInput;
    while (is_it_blocked == false)
    {
        if (matrix[rowInput][columnInput] == 'u') {
            currentRow--;//If current direction is u, decrease current row until cell is blocked
            if (matrix[currentRow][currentCol] != '-') {
                matrix[currentRow + 1][currentCol] = matrix[rowInput][columnInput];//If it is blocked, change their coordinates
                matrix[rowInput][columnInput] = '-';
                is_it_blocked = true;
            }
        }
        else if (matrix[rowInput][columnInput] == 'd') {
            currentRow++;//If current direction is d, increase current row until cell is blocked
            if (matrix[currentRow][currentCol] != '-') {
                matrix[currentRow - 1][currentCol] = matrix[rowInput][columnInput];//If it is blocked, change their coordinates
                matrix[rowInput][columnInput] = '-';
                is_it_blocked = true;
            }
        }
        else if (matrix[rowInput][columnInput] == 'l') {
            currentCol--;//If current direction is l, decrease current column until cell is blocked
            if (matrix[currentRow][currentCol] != '-') {
                matrix[currentRow][currentCol + 1] = matrix[rowInput][columnInput];//If it is blocked, change their coordinates
                matrix[rowInput][columnInput] = '-';
                is_it_blocked = true;
            }
        }
        else if (matrix[rowInput][columnInput] == 'r') {
            currentCol++;//If current direction is r, increase current column until cell is blocked
            if (matrix[currentRow][currentCol] != '-') {
                matrix[currentRow][currentCol - 1] = matrix[rowInput][columnInput];//If it is blocked, change their coordinates
                matrix[rowInput][columnInput] = '-';
                is_it_blocked = true;
            }
        }
    }
}
int main() {
    //Program starts by asking user to enter a file name for input file
    string fileName;
    cout << "Please enter the file name:" << endl;
    cin >> fileName;
    //Program opens file
    ifstream input;
    input.open(fileName.c_str());
    //Check whether the file is opened successfully or not
    //While file is not opened successfully, get input until user enter correct one
    while (!input.is_open())
    {
        cout << "Could not open the file. Please enter a valid file name:" << endl;
        cin >> fileName;
        input.open(fileName.c_str());
    }
    //After opening the file ,places the characters in the matrix (read content into matrix)
    vector<vector<char>> matrix;
    string line;
    while (!input.eof())
    {
        getline(input, line);//reads the file line by line until end of the file
        stringstream ss(line);
        vector<char> row;
        char ch;
        while (ss >> ch) {     //reads the line character by character
            row.push_back(ch); //push back character to construct row vector
        }
        matrix.push_back(row); //push row vector to vector of vector which is named as matrix to construct matrix
    }
    input.close(); //Close file after reading over
    //It is time to validity check for the matrix
    if (!isMatrixValid(matrix))
    {
        cout << "Erroneous file content. Program terminates."; //If matrix is not valid, gives error message and program terminates
    }
    else
    {   // if it passes validity check, print matrix
        cout << "The matrix file contains:" << endl;
        printMatrixContent(matrix);
        bool is_game_end = false;// I used flag-controlled while loop to stop the loop when I need it
        int rowInput, columnInput;
        //Now, It's time for the game to be played
        while (is_game_end != true) {
            //If updated/current matrix is empty or there is no possible movement, game over!
            if (isMatrixEmpty(matrix) || noPossibleMovementForEveryCell(matrix))
            {
                is_game_end = true;
            }
            else //If there's still a movement to be made, keep playing
            {
                getCoordinateInput(rowInput, columnInput); //Get coordinate inputs from the user
                while (!isInputCorrect(rowInput, columnInput, matrix))
                {
                    cout << "Invalid row or column index." << endl; // while there is an invalid input, gives error and
                    getCoordinateInput(rowInput, columnInput);// get new input from the user
                }
                if (isPathClear(rowInput, columnInput, matrix))//This function is used to check whether the cell can drop off (checks both first and second condition)
                {
                    processIfCellDrops(rowInput, columnInput, matrix); //This function is used to drop the cell from matrix
                }
                else if (isPathClear(rowInput, columnInput, matrix) == false && atLeastOneEmptyCell(rowInput, columnInput, matrix))//This function is used to check when path is NOT ALL THE WAY CLEAR but some MOVEMENTS EXIST
                {
                    replaceCurrentCellWithBlockedOne(rowInput, columnInput, matrix); //This function is used to replace current cell with the new cell where it is blocked
                    cout << "Tile at (" << rowInput << "," << columnInput << ") has been moved." << endl;
                    printMatrixContent(matrix);
                }
                else if (noMovementPossible(rowInput, columnInput, matrix))//This function is used to check whether SPECIFIC element of the matrix can move
                {
                    cout << "No tiles have been moved." << endl;
                    printMatrixContent(matrix);
                }
            }
        }
        if (isMatrixEmpty(matrix)) //checks if the matrix created after the game is played is empty or not
        {
            cout << "The matrix is empty.";
        }
        else if (noPossibleMovementForEveryCell(matrix)) //checks if the matrix created after the game is played involves any movement or not
        {
            cout << "No more moves are possible.";
        }
    }
    return 0;
}