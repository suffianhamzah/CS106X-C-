/*
 * CS 106X Huffman Encoding
 * This file declares the functions that you will need to write in this
 * assignment for your Huffman Encoder in huffmanencoding.cpp.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * Author : Marty Stepp
 * Edit for 106X: Cynthia Lee
 * Version: 2015/11/04
 * - updated for X
 */

#ifndef _encoding_h
#define _encoding_h

#include <iostream>
#include <string>
#include "bitstream.h"
#include "HuffmanNode.h"
#include "map.h"
#include "pqueue.h"
#include "vector.h"
#include "filelib.h"

using namespace std;

/*
 * See huffmanencoding.cpp for documentation of these functions
 * (which you are supposed to write, based on the spec).
 */
Map<int, int> buildFrequencyTable(istream& input);
HuffmanNode* buildEncodingTree(const Map<int, int>& freqTable);
Map<int, string> buildEncodingMap(HuffmanNode* encodingTree);
void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output);
void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output);
void compress(istream& input, obitstream& output);
void decompress(ibitstream& input, ostream& output);
void freeTree(HuffmanNode* node);
void buildEncodingMapHelper(Map<int, string>& encodingMap, HuffmanNode* node, string bitString);
void encodeDataHelper(const Map<int, string>& encodingMap, obitstream& output, int currChar);
int decodeDataHelper(ibitstream& input, HuffmanNode* encodingTree);
#endif
