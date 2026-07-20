#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class RockPaperScissors {
private:
    char playerMove;
    char computerMove;

    char generateComputerMove() {
        int move = rand() % 3;

        if (move == 0) return 'r';
        if (move == 1) return 'p';
        return 's';
    }

    int getResult() {
        if (playerMove == computerMove) return 0;

        if (playerMove == 's' && computerMove == 'p') return 1;
        if (playerMove == 's' && computerMove == 'r') return -1;

        if (playerMove == 'p' && computerMove == 'r') return 1;
        if (playerMove == 'p' && computerMove == 's') return -1;

        if (playerMove == 'r' && computerMove == 's') return 1;
        if (playerMove == 'r' && computerMove == 'p') return -1;

        return 0;
    }

public:
    void getPlayerMove() {
        while (true) {
            cin >> playerMove;
            if (playerMove == 'r' || playerMove == 'p' || playerMove == 's')
                break;

            cout << "Invalid Move. Try again: ";
        }
    }

    void playRound() {
        computerMove = generateComputerMove();

        int result = getResult();

        if (result == 0) cout << "Game Draw!\n";
        else if (result == 1) cout << "Player Wins!\n";
        else cout << "Computer Wins!\n";

        cout << "Player Move: " << playerMove << endl;
        cout << "Computer Move: " << computerMove << endl;
    }
};

int main() {
    srand(time(0));

    RockPaperScissors game;
    char choice;

    cout << "Rock Paper Scissors Game\n";
    cout << "Enter r for ROCK, p for PAPER, s for SCISSOR\n";

    do {
        cout << "Rock Paper Scissors Game\n";
        cout << "Enter r for ROCK, p for PAPER, s for SCISSOR\n";
        cout << "\nEnter your move: ";
        game.getPlayerMove();
        game.playRound();

        cout << "\nDo you want to play again? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    cout << "Thanks for playing!\n";
    return 0;
}
