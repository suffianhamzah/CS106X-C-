// This is a .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "lexicon.h"
#include "set.h"
#include "grid.h"
#include "shuffle.h"
#include "bogglegui.h"

using namespace std;

class Boggle {
public:
    Boggle(Lexicon& dictionary, string boardText = "");
    bool checkWord(string word);
    bool humanWordSearch(string word);
    Set<string> computerWordSearch();
    int getScoreHuman();
    int getScoreComputer();
    string getCubes();
    // TODO: add any other member functions/variables necessary
    friend ostream& operator<<(ostream& out, Boggle& boggle);
    int getRows();
    int getCols();
    Set<string> getFoundWords();
private:
    // TODO: add any other member functions/variables necessary
    Grid<char> board;
    Lexicon dictionary;
    Set<string> foundWords;
    int humanScore = 0;
    int compScore = 0;
    int addScore(string& word);
    bool humanWordSearchHelper(Grid<bool> &checker, string word, string prefix, int row, int col);
    void computerWordSearchHelper(Grid<bool> & checker, Set<string> & result, string prefix, int row, int col);

};

#endif // _boggle_h
