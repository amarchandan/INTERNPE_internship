#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Constants
const int ROWS = 6;
const int COLS = 7;
const char EMPTY = ' ';
const char PLAYER1 = 'X';
const char PLAYER2 = 'O';

// Function to print the board
void printBoard(const vector<vector<char>>& board) {
    cout << "\n";

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << "| " << board[i][j] << " ";
        }
        cout << "|\n";
    }

    cout << "-----------------------------\n";
    cout << "| 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n";
    cout << "-----------------------------\n";
}

// Check if move is valid
bool isValidMove(const vector<vector<char>>& board, int col) {
    return (col >= 0 && col < COLS && board[0][col] == EMPTY);
}

// Drop the coin into the board
void makeMove(vector<vector<char>>& board, int col, char player) {
    for (int i = ROWS - 1; i >= 0; i--) {
        if (board[i][col] == EMPTY) {
            board[i][col] = player;
            break;
        }
    }
}

// Check if board is full
bool isBoardFull(const vector<vector<char>>& board) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == EMPTY)
                return false;
        }
    }
    return true;
}

// Check Winner
bool checkWinner(const vector<vector<char>>& board, char player) {

    // Horizontal Check
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col <= COLS - 4; col++) {
            if (board[row][col] == player &&
                board[row][col + 1] == player &&
                board[row][col + 2] == player &&
                board[row][col + 3] == player)
                return true;
        }
    }

    // Vertical Check
    for (int row = 0; row <= ROWS - 4; row++) {
        for (int col = 0; col < COLS; col++) {
            if (board[row][col] == player &&
                board[row + 1][col] == player &&
                board[row + 2][col] == player &&
                board[row + 3][col] == player)
                return true;
        }
    }

    // Diagonal (\)
    for (int row = 0; row <= ROWS - 4; row++) {
        for (int col = 0; col <= COLS - 4; col++) {
            if (board[row][col] == player &&
                board[row + 1][col + 1] == player &&
                board[row + 2][col + 2] == player &&
                board[row + 3][col + 3] == player)
                return true;
        }
    }

    // Diagonal (/)
    for (int row = 3; row < ROWS; row++) {
        for (int col = 0; col <= COLS - 4; col++) {
            if (board[row][col] == player &&
                board[row - 1][col + 1] == player &&
                board[row - 2][col + 2] == player &&
                board[row - 3][col + 3] == player)
                return true;
        }
    }

    return false;
}


// AI chooses a random valid column
int getAIMove(const vector<vector<char>>& board) {

    vector<int> validMoves;

    for (int col = 0; col < COLS; col++) {
        if (isValidMove(board, col)) {
            validMoves.push_back(col);
        }
    }

    int index = rand() % validMoves.size();
    return validMoves[index];
}


int main() {

    srand(time(0));
    int mode;

    cout << "=============================\n";
    cout << "      CONNECT 4 GAME\n";
    cout << "=============================\n";
    cout << "1. Human vs Human\n";
    cout << "2. Human vs Machine\n";
    cout << "Choose Mode: ";
    cin >> mode;

    vector<vector<char>> board(ROWS, vector<char>(COLS, EMPTY));
    bool player1Turn = true;

    cout << "=============================\n";
    cout << "      CONNECT 4 GAME\n";
    cout << "=============================\n";

    while (true) {

        printBoard(board);

        char currentPlayer = player1Turn ? PLAYER1 : PLAYER2;

        int col;

        if (mode == 2 && !player1Turn) {

            cout << "\nMachine is thinking...\n";

            col = getAIMove(board);

            cout << "Machine selected column: "
         << col + 1 << endl;

}
else {

    cout << "Player "
         << currentPlayer
         << ", Enter Column (1-7): ";

    cin >> col;
    col--;
}

        if (!isValidMove(board, col)) {
            cout << "\nInvalid Move! Try Again.\n\n";
            continue;
        }

        // Make Move
        makeMove(board, col, currentPlayer);

        // Check Winner
        if (checkWinner(board, currentPlayer)) {
            printBoard(board);
            cout << "\n🎉 Player " << currentPlayer << " Wins! 🎉\n";
            break;
        }

        // Check Tie
        if (isBoardFull(board)) {
            printBoard(board);
            cout << "\nGame Draw! Board is Full.\n";
            break;
        }

        // Switch Player
        player1Turn = !player1Turn;
    }

    return 0;
}
