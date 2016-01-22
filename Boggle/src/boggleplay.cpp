// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <ctype.h>
#include "lexicon.h"
#include "simpio.h"
#include "console.h"
#include "Boggle.h"
#include "strlib.h"
#include "bogglegui.h"
using namespace std;

bool checkInput(const string& prompt);
void printStatus(const string& message, const string& who, int score, const Set<string>& word, Boggle& boggle);
string boardText();
void humanTurn(string message, Boggle& boggleobj);
string compTurn(Boggle& boggleobj, string message);

void playOneGame(Lexicon& dictionary) {
    // TODO: implement
    string random = "";
    if (!getYesOrNo("Do you want to generate a random board? ")) {
       random = boardText();
    }
    //initilization of GUI
    Boggle boggleobj(dictionary, random);
    if (!BoggleGUI::isInitialized()) {
        BoggleGUI::initialize(boggleobj.getRows(), boggleobj.getCols());
    }
    BoggleGUI::reset();
    BoggleGUI::labelAllCubes(boggleobj.getCubes());
    clearConsole();
    //human player
    humanTurn("This is your turn!", boggleobj);

    //comp turn
    string message = compTurn(boggleobj, "It's my turn!");
    BoggleGUI::setStatusMessage(message);
    cout << message << endl;
    //BoggleGUI::reset();
}

bool checkInput(const string& prompt) {
    for (int i = 0 ; i < prompt.length() ; i++) {
        if(!isalpha(prompt[i])) {
            return false;
        }
    }
    return true;
}

void printStatus(const string& message, const string& who, int score, const Set<string>& word, Boggle& boggle) {
    BoggleGUI::setStatusMessage(message);
    cout << message << endl;
    cout << boggle << who << " words (" << word.size() << "):" << word << endl;
    cout << who << " score: " << score << endl;
}

string boardText() {
    bool breakFrom = true;
    string boardText;
    while (breakFrom) {
        boardText = getLine("Type the 16 letters to appear on the board: ");
        if (boardText.length() == 16 && checkInput(boardText)) {
            breakFrom = false;
        } else {
            cout << "That is not a valid 16-letter board string. Try again." << endl;
        }
    }
    return boardText;
}

void humanTurn(string message, Boggle& boggleobj) {
    while (true) {
        printStatus(message, "Your", boggleobj.getScoreHuman(), boggleobj.getFoundWords(), boggleobj);
        string word = getLine("Type a word (or Enter to stop):");
        word = toLowerCase(word);
        if (word == "") {
            break;
        } else {
            clearConsole();
            if (boggleobj.checkWord(word) && boggleobj.humanWordSearch(word)) {
                message = "You have found a new word! \"" + word + "\"";
                BoggleGUI::recordWord(word, BoggleGUI::HUMAN);
                BoggleGUI::setScore(boggleobj.getScoreHuman(),BoggleGUI::HUMAN);
            } else {
                message = "You must enter an unfound 4+ letter word from the dictionary.";
            }

        }
    }
}

string compTurn(Boggle& boggleobj, string message) {
    Set<string> compWords = boggleobj.computerWordSearch();
    message = "It's my turn!";
    for (auto i : compWords) {
        BoggleGUI::recordWord(i, BoggleGUI::COMPUTER);
    }
    BoggleGUI::setScore(boggleobj.getScoreComputer(),BoggleGUI::COMPUTER);
    printStatus(message, "My", boggleobj.getScoreComputer(), compWords, boggleobj);
    if (boggleobj.getScoreHuman() >= boggleobj.getScoreComputer()) {
        message = "WOW, you defeated me! Congratulations!";
    } else {
        message = "Ha ha ha, I destroyed you. Better luck next time, puny human!";
    }
    return message;
}
