// This is the CPP file you will edit and turn in.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "stack.h"
#include "queue.h"
#include "set.h"
#include "filelib.h"
#include "simpio.h"
#include "strlib.h"
#include "vector.h"

using namespace std;

void   makeDictSet(ifstream& myfile, Set<string>& dict);
string getWord(string prompt, bool& isValid);
bool   checkValid(Set<string> &dict, string word1, string word2, bool isValid);
void   makeWordLadder(Set<string> &dict, string word1, string word2, bool& isTrue);

int main() {
    // TODO: Finish the program!
    Set<string> dict;
    ifstream myfile;
    cout << "Welcome to CS106B Word Ladder" << endl << "Please give me two English words, and I will change the" << endl;
    cout << "first into the second by changing one letter at a time" << endl << endl;
    makeDictSet(myfile, dict);
    string word1;
    string word2;
    bool isValid = true;
    bool isWordLadder = false;
    // cout << endl << dict;
    while (isValid)
    {
        cout << endl;
        word1 = getWord("Word #1: (or Enter to quit): ",isValid);
        if (isValid) {
            word2 = getWord("Word #2: (or Enter to quit): ",isValid);
            isWordLadder = checkValid(dict, word1, word2, isValid);
            makeWordLadder(dict, word1, word2, isWordLadder);
        }
    }
    cout << "Have a nice day." << endl;
    return 0;
}

// creates a set of the words in the dictionary.
// Will check if filename exists. Returns true if exist and dictionary is created.
void makeDictSet(ifstream& myfile, Set<string>& dict)
{
    Vector<string> lines;
    string line;
    string dictName = promptUserForFile(myfile, "Dictionary file name?");
    while (myfile >> line)
    {
        dict.add(line);
    }
}

string getWord(string prompt, bool &isValid)
{
    string word;
    word = getLine(prompt);
    if (word == "") {
        isValid = false;
    }
    word = toLowerCase(word);
    return word;
}

bool checkValid(Set<string>& dict, string word1, string word2, bool isValid)
{
    if (!isValid) {
        return false;
    }

    if (word1.length() != word2.length()) {
        cout << "The two words must be the same length." << endl;
        return false;
    } else if (word1 == word2) {
        cout << "The two words must be different." << endl;
        return false;
    } else if (!dict.contains(word1) && !dict.contains(word2)) {
        cout << "The two words must be found in the dictionary." << endl;
        return false;
    }
    return true;
}

void   makeWordLadder(Set<string> &dict, string word1, string word2, bool& isTrue)
{
    if (!isTrue) {
        return;
    }
    Queue<Stack<string> > wordLadder;
    Set<string> dups;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    dups.add(word1);
    Stack<string> tempstack;
    tempstack.add(word1);
    wordLadder.enqueue(tempstack);
    while (!wordLadder.isEmpty())
    {
        Stack<string> tempStack = wordLadder.peek();
        wordLadder.dequeue();
        string tempWord = tempStack.peek();
        for (int i = 0; i < tempWord.length(); i++)
        {
            string tempWord2 = tempWord;
            for (char tempChar: alphabet)
            {
                tempWord2[i] = tempChar;
                if (dict.contains(tempWord2)) {
                    if(!dups.contains(tempWord2)) {
                        dups.add(tempWord2);
                        if (tempWord2 == word2) {
                            tempStack.add(tempWord2);
                            cout << "A ladder from " << word2 << " back to " << word1 << ":" << endl;
                            while (!tempStack.isEmpty())
                            {
                                cout << tempStack.peek() << " ";
                                tempStack.pop();
                            }
                            cout << endl;
                            return;
                        } else {
                            Stack<string> copy = tempStack;
                            copy.add(tempWord2);
                            wordLadder.add(copy);
                        }
                    }
                }
            }
        }
    }
}
