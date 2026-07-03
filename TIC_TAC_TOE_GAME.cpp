#include <iostream>
#include <string>
#include <climits>
#include <cstdlib>
#include <ctime>
using namespace std;

class Player {
private:
    char symbol;
    string name;
    bool isComputer;

public:
    Player(char sym = 'X', string n = "Player X", bool comp = false)
        : symbol(sym), name(n), isComputer(comp) {}

    char getSymbol() const { return symbol; }
    string getName() const { return name; }
    bool getIsComputer() const { return isComputer; }
};

class Board {
private:
    char grid[3][3];
    int filledCells;

public:
    Board() : filledCells(0) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                grid[i][j] = ' ';
            }
        }
    }

    void drawBoard() const {
        cout << "-------------" << endl;
        for (int i = 0; i < 3; i++) {
            cout << "| ";
            for (int j = 0; j < 3; j++) {
                cout << grid[i][j] << " | ";
            }
            cout << endl << "-------------" << endl;
        }
    }

    bool isValidMove(int row, int col) const {
        return (row >= 0 && row < 3 && col >= 0 && col < 3 && grid[row][col] == ' ');
    }

    void makeMove(int row, int col, char symbol) {
        if (isValidMove(row, col)) {
            grid[row][col] = symbol;
            filledCells++;
        }
    }

    void undoMove(int row, int col) {
        if (grid[row][col] != ' ') {
            grid[row][col] = ' ';
            filledCells--;
        }
    }

    bool checkWin(char symbol) const {
        for (int i = 0; i < 3; i++) {
            if (grid[i][0] == symbol && grid[i][1] == symbol && grid[i][2] == symbol) {
                return true;
            }
        }

        for (int i = 0; i < 3; i++) {
            if (grid[0][i] == symbol && grid[1][i] == symbol && grid[2][i] == symbol) {
                return true;
            }
        }

        if (grid[0][0] == symbol && grid[1][1] == symbol && grid[2][2] == symbol) {
            return true;
        }
        if (grid[0][2] == symbol && grid[1][1] == symbol && grid[2][0] == symbol) {
            return true;
        }

        return false;
    }

    bool isFull() const {
        return filledCells == 9;
    }

    int getFilledCellsCount() const {
        return filledCells;
    }

    char getCell(int row, int col) const {
        return grid[row][col];
    }
};

class Computer {
public:
    static void getRandomMove(Board& board, int& row, int& col) {
        int emptyCells[9][2];
        int count = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board.isValidMove(i, j)) {
                    emptyCells[count][0] = i;
                    emptyCells[count][1] = j;
                    count++;
                }
            }
        }
        int choice = rand() % count;
        row = emptyCells[choice][0];
        col = emptyCells[choice][1];
    }

    static int minimax(Board& board, char aiSymbol, char humanSymbol, bool isMaximizing) {
        if (board.checkWin(aiSymbol)) return 10;
        if (board.checkWin(humanSymbol)) return -10;
        if (board.isFull()) return 0;

        if (isMaximizing) {
            int bestScore = INT_MIN;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board.isValidMove(i, j)) {
                        board.makeMove(i, j, aiSymbol);
                        int score = minimax(board, aiSymbol, humanSymbol, false);
                        board.undoMove(i, j);
                        bestScore = max(bestScore, score);
                    }
                }
            }
            return bestScore;
        } else {
            int bestScore = INT_MAX;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board.isValidMove(i, j)) {
                        board.makeMove(i, j, humanSymbol);
                        int score = minimax(board, aiSymbol, humanSymbol, true);
                        board.undoMove(i, j);
                        bestScore = min(bestScore, score);
                    }
                }
            }
            return bestScore;
        }
    }

    static void getBestMove(Board& board, char aiSymbol, char humanSymbol, int& row, int& col) {
        int bestScore = INT_MIN;
        row = -1; col = -1;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board.isValidMove(i, j)) {
                    board.makeMove(i, j, aiSymbol);
                    int score = minimax(board, aiSymbol, humanSymbol, false);
                    board.undoMove(i, j);

                    if (score > bestScore) {
                        bestScore = score;
                        row = i;
                        col = j;
                    }
                }
            }
        }
    }
};

class TicTacToe {
private:
    Board board;
    Player players[2];
    int currentPlayerIndex;
    int difficulty;

    void getHumanMove(Player& player, int& row, int& col) {
        while (true) {
            cout << player.getName() << " (" << player.getSymbol()
                 << "), enter row (1-3) and column (1-3): ";
            cin >> row >> col;
            row--; col--;

            if (board.isValidMove(row, col)) {
                break;
            } else {
                cout << "Invalid move. Try again." << endl;
            }
        }
    }

    void getComputerMove(Player& player, char humanSymbol, int& row, int& col) {
        cout << player.getName() << " (" << player.getSymbol() << ") is thinking..." << endl;
        if (difficulty == 1) {
            Computer::getRandomMove(board, row, col);
        } else {
            Computer::getBestMove(board, player.getSymbol(), humanSymbol, row, col);
        }
        cout << player.getName() << " chooses row " << (row + 1)
             << ", column " << (col + 1) << endl;
    }

public:
    TicTacToe() : currentPlayerIndex(0), difficulty(2) {
        players[0] = Player('X', "Player X", false);
        players[1] = Player('O', "Player O", false);
    }

    void setupGame() {
        int modeChoice;
        cout << "===== Tic-Tac-Toe =====" << endl;
        cout << "1. Human vs Human" << endl;
        cout << "2. Human vs Computer" << endl;
        cout << "Enter choice (1-2): ";
        cin >> modeChoice;

        if (modeChoice == 2) {
            players[1] = Player('O', "Computer", true);

            cout << "Choose difficulty:" << endl;
            cout << "1. Easy" << endl;
            cout << "2. Hard (Unbeatable)" << endl;
            cout << "Enter choice (1-2): ";
            cin >> difficulty;
            if (difficulty != 1 && difficulty != 2) difficulty = 2;
        }
    }

    Player& getCurrentPlayer() {
        return players[currentPlayerIndex];
    }

    void switchTurn() {
        currentPlayerIndex = (currentPlayerIndex + 1) % 2;
    }

    void play() {
        int row, col;
        cout << "Welcome to Tic-Tac-Toe!" << endl;

        setupGame();

        while (!board.isFull()) {
            board.drawBoard();

            Player& currentPlayer = getCurrentPlayer();
            Player& otherPlayer = players[(currentPlayerIndex + 1) % 2];

            if (currentPlayer.getIsComputer()) {
                getComputerMove(currentPlayer, otherPlayer.getSymbol(), row, col);
            } else {
                getHumanMove(currentPlayer, row, col);
            }

            board.makeMove(row, col, currentPlayer.getSymbol());

            if (board.checkWin(currentPlayer.getSymbol())) {
                board.drawBoard();
                cout << currentPlayer.getName() << " wins!" << endl;
                return;
            }

            switchTurn();
        }

        board.drawBoard();
        cout << "It's a draw!" << endl;
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0)));
    TicTacToe game;

    game.play();
    return 0;
}
