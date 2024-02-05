#include "hangman.h"
#include <iostream>

int main() {
    srand(time(0));
    std::string guesses;
    std::string wordToGuess;
    wordToGuess = LoadRandomWord("words.txt");
    int tries = 0;
    bool win = false;

    do {
        system("cls");
        PrintMessage("HANGMAN");
        DrawHangman(tries);
        PrintAvailableLetters(guesses);
        PrintMessage("Guess the word");
        win = PrintWordAndCheckWin(wordToGuess, guesses);

        if (win)
            break;

        char x;
        std::cout << ">";
        std::cin >> x;

        if (guesses.find(x) == std::string::npos)
            guesses += x;

        tries = TriesLeft(wordToGuess, guesses);

    } while (tries < 10);

    if (win)
        PrintMessage("YOU WON!");
    else
        PrintMessage("GAME OVER");

    system("pause");
    getchar();
    return 0;
}
