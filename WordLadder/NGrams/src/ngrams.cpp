// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "simpio.h"
#include "map.h"
#include "vector.h"
#include "random.h"

using namespace std;

int     getNum(string prompt, int limit);
void    genRandom(Map<Vector<string>, Vector<string> >& nGramMap, int numWord, int ngram);
void    buildNGramMap(ifstream& myfile, Map<Vector<string>, Vector<string> >& nGramMap, int ngram);
void    putMap(Map<Vector<string>, Vector<string> >& nGramMap, Vector<string>& inputVect, const string &inputWord);

int main() {
    // TODO: Finish the program!
    cout << "Welcome to CS 106B Random Writer ('N-Grams')." << endl;
    cout << "This program makes a random text based on a document." << endl;
    cout << "Give an input file and an 'N' value for groups of words, and I'll";
    cout << " create" << endl << "random text for you." << endl;
    ifstream myfile;
    int numWord;
    Map<Vector<string>, Vector<string> > nGramMap;
    string filename = promptUserForFile(myfile,"Input file? ");
    int ngram = getNum("Value of N? ", 2);
    buildNGramMap(myfile, nGramMap, ngram);
    while (numWord != 0)
    {
        cout << endl;
        numWord = getNum("# of random words to generate (0 to quit)? ", 0);
        if (numWord != 0) {
            genRandom(nGramMap,numWord, ngram);
        }
    }

    cout << "Exiting." << endl;
    return 0;
}

int getNum(string prompt, int limit)
{
    int num = -1;
    while (num < limit)
    {
        num = getInteger(prompt);
    }
    return num;
}

void genRandom(Map<Vector<string>, Vector<string> >& nGramMap, int numWord, int ngram)
{
    Vector<Vector<string> > kunci = nGramMap.keys();
    //select random key
    int rand = randomInteger(0, kunci.size()-1);
    Vector<string> tempVect = kunci[rand];
    Vector<string> randKey = kunci[rand];
    for (int i = ngram; i < numWord; i++)
    {
        int randSuffix = randomInteger(0, nGramMap[randKey].size() - 1);
        tempVect.add(nGramMap[randKey][randSuffix]);
        Vector<string> window =randKey;
        window.add(nGramMap[randKey][randSuffix]);
        window.remove(0);
        randKey = window;
    }
    cout << "... ";
    for (string word:tempVect)
    {
        cout << word << " ";
    }
    cout << " ..." << endl;
}

void buildNGramMap(ifstream &myfile, Map<Vector<string>, Vector<string> >& nGramMap, int ngram)
{
    string inputWord;
    Vector<string> inputVect;
    for (int i = 0; i < ngram; i++)
    {
        myfile >> inputWord;
        inputVect.add(inputWord);
    }
    Vector<string> lastVect = inputVect;
    while (myfile >> inputWord)
    {
        putMap(nGramMap, inputVect, inputWord);
    }

    for (int j = 0; j < ngram; j++)
    {
        inputWord = lastVect[j];
        putMap(nGramMap, inputVect, inputWord);
    }
}

void putMap(Map<Vector<string>, Vector<string> >& nGramMap, Vector<string> & inputVect, const string &inputWord)
{
    if(!nGramMap.containsKey(inputVect)) {
        nGramMap.add(inputVect, Vector<string>());
    }
        nGramMap[inputVect].add(inputWord);
    inputVect.remove(0);
    inputVect.add(inputWord);
}
