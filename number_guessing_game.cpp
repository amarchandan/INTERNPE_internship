#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(0));

    char playAgain;

    do {
        int num = rand() % 100 + 1;
        int guess;
        int attempts = 0;

        cout << "\nNumber Guessing Game\n";
        cout << "I have chosen a number between 1 and 100.\n";

        do {
            cout << "Enter your guess: ";
            cin >> guess;

            // Input validation
            if (guess < 1 || guess > 100) {
                cout << "Please enter a number between 1 and 100.\n";
                continue;
            }

            attempts++;

            if (guess > num) {
                cout << "Too high! Guess lower.\n";
            }
            else if (guess < num) {
                cout << "Too low! Guess higher.\n";
            }
            else {
                cout << "\nCongratulations! You guessed the number.\n";
                cout << "Attempts taken: " << attempts << "\n";
            }

            // Hint system
            if (guess != num) {
                int diff = abs(guess - num);

                if (diff <= 5)
                    cout << "Hint: Very close!\n";
                else if (diff <= 15)
                    cout << "Hint: Close.\n";
                else
                    cout << "Hint: Far away.\n";
            }

        } while (guess != num);

        cout << "\nDo you want to play again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "\nThanks for playing!\n";
    return 0;
}
