// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "Boggle.h"


// letters on all 6 sides of every cube
static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// letters on every cube in 5x5 "Big Boggle" version (extension)
static string BIG_BOGGLE_CUBES[25] = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

Boggle::Boggle(Lexicon& dictionary_, string boardText) : dictionary(dictionary_) {
    // TODO:
    int cubeCount = 0;
    board.resize(4,4);
    boardText = toUpperCase(boardText);

    for (int i = 0 ; i < board.numRows(); i++) {
        for (int j = 0; j < board.numCols(); j ++) {
            board[i][j] = (boardText == "") ? shuffle(CUBES[cubeCount])[0] : boardText[cubeCount];
            cubeCount++;
        }
    }
    if (boardText == "") {
        shuffle(board);
    }
}

bool Boggle::checkWord(string word) {
    word = toLowerCase(word);
    return (word.length() > 3 && dictionary.contains(word)
            && !foundWords.contains(toUpperCase(word)));
}

bool Boggle::humanWordSearch(string word) {
    //word is alreadylowercase;
    word = toUpperCase(word);
    string prefix;
    BoggleGUI::clearHighlighting();
    Grid<bool> checker(4,4);
    checker.fill(false);
    for (int row = 0 ; row < board.numRows() ; row ++) {
        for (int col = 0 ; col < board.numCols() ; col++) {
            if (board[row][col] == word[0]) {
                if (humanWordSearchHelper(checker, word, prefix, row , col)) {
                    humanScore += addScore(word);
                    foundWords.add(word);
                    return true;
                }
                checker.fill(false);
            }
        }
    }
    // TODO: implement
    return false;
}

int Boggle::getScoreHuman() {
    // TODO: implement
    return humanScore;   // remove this
}

Set<string> Boggle::computerWordSearch() {
    // TODO: implement
    Set<string> result;
    string prefix = "";
    Grid<bool> checker(4,4);
    checker.fill(false);
    int rows = board.numRows();
    int cols = board.numCols();
    for (int i = 0 ; i < rows * cols ; i++) {
        computerWordSearchHelper(checker, result, prefix,i / rows, i % cols);
    }
    return result;        // remove this
}

int Boggle::getScoreComputer() {
    // TODO: implement
    return compScore;   // remove this
}

ostream& operator<<(ostream& out, Boggle& boggle) {
    // TODO: implement
    string cubes = boggle.getCubes();
    for (int i = 1 ; i <= cubes.length(); i++) {
        out << cubes[i-1] ;
        if (i % 4 == 0) {
            out << endl;
        }
    }
    return out;
}

int Boggle::addScore(string& word) {
    int score = 0;
    for (int i = 3; i < word.length(); i++) {
        score++;
    }
    return score;
}

bool  Boggle::humanWordSearchHelper(Grid<bool> &checker, string word, string prefix, int row, int col) {
    if (board.inBounds(row, col) && !checker[row][col]) {

        prefix += board[row][col];
        checker[row][col] = true;
        BoggleGUI::setAnimationDelay(100);
        BoggleGUI::setHighlighted(row, col, true);
        if (board[row][col] == word[prefix.length()-1]) {
            if (prefix == word) {
                return true;
            }

            for (int i = row - 1; i <= row + 1; i++) {
                for (int j = col - 1; j <= col + 1; j++) {
                    if (humanWordSearchHelper(checker, word, prefix, i, j)) {
                        return true;
                    }
                }
            }
        }
        prefix.pop_back();
        checker[row][col] = false;
        BoggleGUI::setHighlighted(row, col, false);
    }
    return false;
}

string Boggle::getCubes() {
    string cubes;
    for (int row = 0 ; row < board.numRows() ; row++) {
        for (int col = 0 ; col < board.numCols() ; col++) {
            cubes += board[row][col];
        }
    }

    return cubes;
}

int Boggle::getCols() {
    return board.numCols();
}

int Boggle::getRows() {
    return board.numRows();
}

Set<string> Boggle::getFoundWords() {
    return foundWords;
}

void Boggle::computerWordSearchHelper(Grid<bool> & checker, Set<string> & result, string prefix, int row, int col) {
    if (checkWord(prefix) && !result.contains(prefix)) {
        foundWords.add(prefix);
        result.add(prefix);
        compScore += addScore(prefix);
    }

    if (board.inBounds(row, col) && !checker[row][col]) {
        checker[row][col] = true;
        prefix += board[row][col];
        for (int i = row - 1; i <= row + 1 ; i++) {
            for (int j = col - 1 ; j <= col + 1 ; j++) {
                if (dictionary.containsPrefix(prefix)) {
                    computerWordSearchHelper(checker, result, prefix, i, j);
                }
            }
        }
        prefix.pop_back();
        checker[row][col] = false;
    }
}
