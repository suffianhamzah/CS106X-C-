/*
 * CS 106X Recursion Problems
 * This file declares necessary function prototypes, so that other files
 * are able to call the recursive functions you will write.
 * You should not modify this file.
 * 
 * (If you want to declare your own helper function prototypes,
 *  do that near the top of your .cpp file, not here.)
 */

#ifndef _recursionproblems_h
#define _recursionproblems_h

#include <iostream>
#include <string>
#include "gbufferedimage.h"
#include "gwindow.h"
#include "vector.h"

// function prototype declarations
// (If you want to declare your own helper function prototypes, do that near
//  the top of your .cpp file, not here.  You should NOT modify this file.)
double weightOnKnees(int row, int col, const Vector<Vector<double> >& weights);
double weightOnKneesFaster(int row, int col, const Vector<Vector<double> >& weights);
void drawSierpinskiTriangle(GWindow& gw, double x, double y, int size, int order);

#endif
