#include "hangman.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

void PrintMessage(std::string message, bool printTop, bool printBottom) {
    if (printTop) {
        std::cout << "+---------------------------------+" << std::endl;
        std::cout << "|";
    }
    else {
        std::cout << "|";
    }

    bool front = true;
    for (int i = message.length(); i < 33; i++) {
        if (front) {
            message = " " + message;
        }
        else {
            message = message + " ";
        }
        front = !front;
    }
    std::cout << message.c_str();

    if (printBottom) {
        std::cout << "|" << std::endl;
        std::cout << "+---------------------------------+" << std::endl;
    }
    else {
        std::cout << "|" << std::endl;
    }
}

void DrawHangman(int guessCount) {
    if (guessCount >= 1)
        PrintMessage("|", false, false);
    else
        PrintMessage("", false, false);

    if (guessCount >= 2)
        PrintMessage("|", false, false);
    else
        PrintMessage("", false, false);

    if (guessCount >= 3)
        PrintMessage("O", false, false);
    else
        PrintMessage("", false, false);

    if (guessCount == 4)
        PrintMessage("/  ", false, false);

    if (guessCount == 5)
        PrintMessage("/| ", false, false);

    if (guessCount >= 6)
        PrintMessage("/|\\", false, false);
    else
        PrintMessage("", false, false);

    if (guessCount >= 7)
        PrintMessage("|", false, false);
    else
        PrintMessage("", false, false);

    if (guessCount == 8)
        PrintMessage("/", false, false);

    if (guessCount >= 9)
        PrintMessage("/ \\", false, false);
    else
        PrintMessage("", false, false);
}

void PrintLetters(std::string input, char from, char to) {
    std::string s;
    for (char i = from; i <= to; i++) {
        if (input.find(i) == std::string::npos) {
            s += i;
            s += " ";
        }
        else
            s += "  ";
    }
    PrintMessage(s, false, false);
}

void PrintAvailableLetters(std::string taken) {
    PrintMessage("Available letters");
    PrintLetters(taken, 'A', 'M');
    PrintLetters(taken, 'N', 'Z');
}

bool PrintWordAndCheckWin(std::string word, std::string guessed) {
    bool won = true;
    std::string s;
    for (int i = 0; i < word.length(); i++) {
        if (guessed.find(word[i]) == std::string::npos) {
            won = false;
            s += "_ ";
        }
        else {
            s += word[i];
            s += " ";
        }
    }
    PrintMessage(s, false);
    return won;
}

std::string LoadRandomWord(std::string path) {
    int lineCount = 0;
    std::string word;
    std::vector<std::string> v;
    std::ifstream reader(path);
    if (reader.is_open()) {
        while (std::getline(reader, word))
            v.push_back(word);

        int randomLine = rand() % v.size();

        word = v.at(randomLine);
        reader.close();
    }
    return word;
}

int TriesLeft(std::string word, std::string guessed) {
    int error = 0;
    for (int i = 0; i < guessed.length(); i++) {
        if (word.find(guessed[i]) == std::string::npos)
            error++;
    }
    return error;
}
