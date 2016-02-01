// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

// Please feel free to add any other #includes you need!
#include "recursionproblems.h"
#include <cmath>
#include <iostream>
#include "hashmap.h"
#include "map.h"
#include "random.h"
#include "error.h"
#include "math.h"

using namespace std;


double weightOnKnees(int row, int col, const Vector<Vector<double> >& weights) {
    // TODO: write this function
    if (col < 0 || row < 0 || col >= weights[row].size()) {
        return 0.0;
    } else {
        return weights[row][col] + 0.5*weightOnKnees(row-1, col, weights) + 0.5*weightOnKnees(row-1, col-1, weights);
    }
}

double weightOnKneesFaster(int row, int col, const Vector<Vector<double> >& weights,
                           Vector<Vector<double> >& memos) {
    // TODO: write tohis function
    if (col < 0 || row < 0 || col >= weights[row].size()) {
        return 0.0;
    }

    if (memos[row][col] == 0.0) {
        memos[row][col] = weights[row][col] + 0.5*weightOnKneesFaster(row-1, col, weights, memos) + 0.5*weightOnKneesFaster(row-1, col-1, weights, memos);
    }
    return memos[row][col];
    }

double weightOnKneesFaster(int row, int col, const Vector<Vector<double> >& weights) {
    // TODO: write this function
    Vector<Vector<double> > memos = weights;
    for (int i = 0 ; i < memos.size() ; i++) {
        for (int j = 0 ; j < memos[i].size(); j++) {
            memos[i][j] = 0.0;
        }
    }
    return weights[row][col] + 0.5*weightOnKneesFaster(row-1, col, weights,memos) + 0.5*weightOnKneesFaster(row-1, col-1, weights,memos);
}

void drawSierpinskiTriangle(GWindow& gw, double x, double y, int size, int order) {
    // TODO: write this function

    if (order == 0) {
        return;
    }

    if (x < 0 || y < 0 || order < 0 || size < 0) {
        error("sorry bero problem :/");
    }
    int height = sqrt(3) / 2 * size;

    if (order == 1) {
        gw.drawLine(x,y, x + size, y);    //right
        gw.drawLine(x,y, x + size/2, y + height); //middle
        gw.drawLine(x + size/2, y + height, x + size, y);
    } else {
        drawSierpinskiTriangle(gw ,x, y, size/2, order -1);
        drawSierpinskiTriangle(gw ,x + size/2,y, size/2,order -1);
        drawSierpinskiTriangle(gw ,x + size/4,y + height/2, size/2,order -1);
    }
}

