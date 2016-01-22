// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"
// TODO: include any other headers you need

//This function will count the frequency of characters that appear in the text file passed in.
Map<int, int> buildFrequencyTable(istream& input) {

    Map<int, int> freqTable;
    int currChar = input.get();
    while (currChar >=0) {
        if (freqTable.containsKey(currChar)) {
            freqTable[currChar]++;
        } else {
            freqTable.put(currChar, 1);
        }
        currChar = input.get();
    }
    freqTable.put(PSEUDO_EOF, 1);
    return freqTable;          // this is just a placeholder so it will compile
}

HuffmanNode* buildEncodingTree(const Map<int, int>& freqTable) {
    PriorityQueue<HuffmanNode*> pq;
    Vector<int> keys = freqTable.keys();
    for (auto i:keys) {
        int count = freqTable.get(i);
        pq.enqueue(new HuffmanNode(i, count, NULL, NULL), count);
    }

    while (pq.size() >1) {
        HuffmanNode* left = pq.dequeue();
        HuffmanNode* right = pq.dequeue();
        int count = left->count + right->count;
        pq.enqueue(new HuffmanNode(NOT_A_CHAR,count,left,right), count);
    }

    return pq.dequeue();   // this is just a placeholder so it will compile
}

Map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    Map<int, string> encodingMap;   // this is just a placeholder so it will compile
    string bitString = "";
    buildEncodingMapHelper(encodingMap, encodingTree, bitString);
    return encodingMap;             // this is just a placeholder so it will compile
}

void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output) {
    rewindStream(input);
    int currChar = input.get();
    while (currChar >= 0) {
        encodeDataHelper(encodingMap, output, currChar);
        currChar = input.get();
    }

    encodeDataHelper(encodingMap, output, PSEUDO_EOF);
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    int currChar;
    while (currChar != PSEUDO_EOF) {
        currChar = decodeDataHelper(input, encodingTree);
        output << char(currChar);
    }
}

void compress(istream& input, obitstream& output) {
    Map<int, int> frequencyTable = buildFrequencyTable(input);
    HuffmanNode* encodingTree = buildEncodingTree(frequencyTable);
    Map<int, string> encodingMap = buildEncodingMap(encodingTree);
    output << frequencyTable;
    encodeData(input, encodingMap, output);
    freeTree(encodingTree);

}

void decompress(ibitstream& input, ostream& output) {
    Map<int, int> frequencyTable;
    input >> frequencyTable;
    HuffmanNode* encodingTree = buildEncodingTree(frequencyTable);
    decodeData(input, encodingTree, output);
    freeTree(encodingTree);
}

void freeTree(HuffmanNode* node) {
    if (!node) {
        return;
    }
    freeTree(node->zero);
    freeTree(node->one);
    delete node;
}

void buildEncodingMapHelper(Map<int, string>& encodingMap, HuffmanNode* node, string bitString) {
    if (node->isLeaf()) {
        encodingMap.put(node->character, bitString);
        return;
    }
    buildEncodingMapHelper(encodingMap,node->zero, bitString + "0");
    buildEncodingMapHelper(encodingMap,node->one, bitString + "1");
}

void encodeDataHelper(const Map<int, string>& encodingMap, obitstream& output, int currChar) {
    string bitString = encodingMap.get(currChar);
    for (auto i:bitString) {
        cout << i;
        output.writeBit(i - 48);
    }
}

int decodeDataHelper(ibitstream& input, HuffmanNode* encodingTree) {
    if (encodingTree->isLeaf()) {
        return encodingTree->character;
    } else {
        int currBit = input.readBit();
        if (currBit == 0) {
            return decodeDataHelper(input, encodingTree->zero);
        } else {
            return decodeDataHelper(input, encodingTree->one);
        }
    }
}
