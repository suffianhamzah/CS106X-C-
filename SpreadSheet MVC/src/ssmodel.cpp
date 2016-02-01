/**
 * File: ssmodel.cpp
 * ------------------
 * This file will contain the implementation of the SSModel class (once you
 * have finished it!
 */

#include "ssmodel.h"
#include "exp.h"

using namespace std;

SSModel::SSModel(int nRows, int nCols, SSView *view_) : celldata(nRows, nCols) , view(view_) {
    setUpFTable(fTable);
}

SSModel::~SSModel() {
    clearAll();
}

bool SSModel::nameIsValid(const string& cellname) const {
    xy rowCol = getRowCol(cellname);
    return celldata.inBounds(rowCol.row, rowCol.col);
}

void SSModel::setCellFromScanner(const string& cellname, TokenScanner& scanner) {
    Cell *cellinfo = getCell(cellname);
    Expression* tempexp = parseExp(scanner, *this, cellname);
    if (!cellinfo) {
        createCell(cellname);
        cellinfo = getCell(cellname);
    }
    removeDependencies(cellname);
    addDependencies(cellname, tempexp);
    cellinfo->removeExp();
    cellinfo->setExp(tempexp);
    //string cellVal = cellinfo->eval(*this);
    evalCell(cellname, cellinfo);
    updateCells(cellname);
    //view->displayCell(cellname,cellVal);
}

void SSModel::createCell(const std::string& cellname) {
    xy rowCol = getRowCol(cellname);
    celldata[rowCol.row][rowCol.col] = new Cell(cellname);
    addNode(cellname);
}

void SSModel::printCellInformation(const string& cellname) const {
    xy rowCol = getRowCol(cellname);
    Cell* cellinfo = celldata.get(rowCol.row,rowCol.col);
    if (cellinfo) {
        cout << "CellContent: " << cellinfo->getVal() << " " << cellinfo->getNumVal() << endl;
        cout << "Cell Dependencies: " << endl;
        cout << "Depend on me: " << cellinfo->printSubscribe() << endl;
        cout << "I depend on: " << cellinfo->printListen() << endl;
    } else {
        cout << "Cell does not contain any content" << endl;
    }
}

void SSModel::writeToStream(ostream& outfile) const {
    for (Cell * cell : celldata) {
        if (cell) {
        string outString = cell->getName() + " : " + cell->getVal();
        outfile << outString << endl;
        }
    }
}

void SSModel::readFromStream(istream& infile) {
    clearAll();
    string cellName;
}

void SSModel::clearAll() {
    for (int i = 0 ; i < celldata.numRows(); i++) {
        for (int j = 0; j < celldata.numCols() ; j++) {
            delete celldata[i][j];
            celldata[i][j] = nullptr;
        }
    }

    for (Arc* _arcs : dGraph.arcs) {
        delete _arcs;
        _arcs = nullptr;
    }

    for (Node* node : dGraph.nodes) {
        delete node;
        node = nullptr;
    }

    dGraph.arcs.clear();
    dGraph.nodes.clear();
    dGraph.nodeMap.clear();
    view->displayEmptySpreadsheet();
}

xy SSModel::getRowCol(const string& cellname) const {
    xy rowcol(atoi(cellname.substr(1).c_str()) - 1, cellname[0] - 'A');
    return rowcol;
}

bool SSModel::isDefined(const string& cellname) {
    xy rowCol = getRowCol(cellname);
    return celldata.get(rowCol.row,rowCol.col);
}

Cell* SSModel::getCell(const std::string& cellname) {
    xy rowCol = getRowCol(cellname);
    return celldata.get(rowCol.row,rowCol.col);

}

bool SSModel::isFormula(const std::string& formula) {
    return fTable.containsKey(formula);
}

double SSModel::getRangeVal(const std::string& cellname1, const std::string& cellname2, const std::string& formula) {
    Vector<double> arr;
    xy start = getRowCol(cellname1);
    xy end = getRowCol(cellname2);
    for (int i = start.row; i <= end.row; i++) {
        for (int j = start.col; j <= end.col; j++) {
            if (celldata.get(i,j)) {
                arr.push_back(celldata.get(i,j)->getNumVal());
            } else {
                arr.push_back(0.0);
            }
        }
    }
    return fTable[formula](arr);
}

void SSModel::addNode(const string& cellname) {
    if (dGraph.nodeMap.containsKey(cellname)) {
        return;
    }
    Node* temp = new Node(cellname);
    dGraph.nodeMap.add(cellname, temp);
    dGraph.nodes.add(temp);
}

void SSModel::connectNode(const string& parentCell, const string& cellname) {
    if (!isDefined(cellname)) {
        createCell(cellname);
    }

    Node* curr = dGraph.nodeMap.get(cellname);
    Node* parent = dGraph.nodeMap.get(parentCell);
    addArc(curr,parent); //dependOnMe;
}

void SSModel::addArc(Node* first, Node* second) {
    Arc* arc = new Arc(first, second);
    string firstName = first->name;
    string secondName = second->name;
    addSublist(firstName, secondName,1);
    addSublist(secondName, firstName, 0);
    first->arcs.add(arc); //dependOnMe
    second->arcs.add(arc); //iDependOn
    dGraph.arcs.add(arc);
}

bool SSModel::checkCircular(const string& parentCell, const string& cellname) {
    if (parentCell == cellname) {
        return false;
    }
    addNode(cellname);
    // takes in the node itself;
    Set<string> visited;
    return checkCircularHelper(dGraph.nodeMap.get(parentCell),dGraph.nodeMap.get(cellname), visited);
}

bool SSModel::checkCircularHelper(Node* parent, Node* curr, Set<string>& visited) {
    if (!visited.contains(curr->name)) {
        if (parent == curr) {
            return false;
        }
        visited.add(curr->name);
        for (Arc* currArc :  curr->arcs) {
            if (currArc->finish == curr &&
                !checkCircularHelper(parent, currArc->start, visited)) {
                return false;
            }
        }
    }
    return true;
}

void SSModel::removeDependencies(const string &cellname) {
    Node * parent = dGraph.nodeMap.get(cellname);
    for (Arc* currArc : parent->arcs) {
        if (currArc->finish == parent) {
            Arc *friendArc = findArc(currArc->finish->name, currArc->start->name);
            removeArc(currArc->start, friendArc);
            removeSubList(currArc->start->name, parent->name, 1);
            removeArc(parent, currArc);
            removeSubList(parent->name, currArc->start->name, 0);
        }
    }
}

void SSModel::removeArc(Node* node, Arc* arc) {
    node->arcs.remove(arc);
    dGraph.arcs.remove(arc);
}

void SSModel::addDependencies(const std::string& cellname, const Expression* exp) {
    if (exp->getType() == COMPOUND) {
        CompoundExp* cexp = (CompoundExp*) exp;
        addDependencies(cellname, cexp->getLHS());
        addDependencies(cellname, cexp->getRHS());
    } else if (exp->getType() == IDENTIFIER) {
        connectNode(cellname, exp->toString());
    } else if (exp->getType() == FUNCTION) {
        FunctionExp* rexp = (FunctionExp*) exp;
        range cRange = rexp->getRange();
        Vector<string> cells = cellRange(cRange.startCell, cRange.stopCell);
        for (string cell : cells) {
            connectNode(cellname, cell);
        }
    }
}

void SSModel::updateCells(const std::string& cellname) {
    Set<string> isVisited;
    for (Arc* currArc : dGraph.nodeMap.get(cellname)->arcs) {
        if (currArc->start->name == cellname) {
            updateCellsHelper(currArc->finish->name, isVisited);
        }
    }

}

void SSModel::updateCellsHelper(const string& cellname, Set<string>& isVisited) {
    //if (!isVisited.contains(cellname)) {
        isVisited.add(cellname);
        Cell *cellinfo = getCell(cellname);
        evalCell(cellname, cellinfo);
        for (Arc* currArc : dGraph.nodeMap.get(cellname)->arcs) {
            if (currArc->start->name == cellname) {
                updateCellsHelper(currArc->finish->name, isVisited);
            }
        }
    //}
}

void SSModel::evalCell(const string& cellname, Cell *cellinfo) {
    view->displayCell(cellname, cellinfo->eval(*this));
}

void SSModel::addSublist(const std::string& cellname, const std::string& cellname2, int mode) {
    Cell* temp = getCell(cellname);
    if (mode == 1) {
        temp->addSubscribe(cellname2);
    } else {
        temp->addListen(cellname2);
    }
}
void SSModel::removeSubList(const string &cellname, const string &cellname2, int mode) {
    Cell* temp = getCell(cellname);
    if (mode == 1) {
        temp->removeSubscribe(cellname2);
    } else {
        temp->removeListener(cellname2);
    }
}

Arc* SSModel::findArc(const std::string& start, const std::string& finish) {
    for (Arc* currArc : dGraph.arcs) {
        if (currArc->start->name == start && currArc->finish->name == finish) {
            return currArc;
        }
    }
    return nullptr;
}

Vector <std::string> SSModel::cellRange(const string& cellname1, const string& cellname2) {
    location cell1, cell2;
    bool test = (stringToLocation(cellname1, cell1) && stringToLocation(cellname2, cell2));
    Vector<string> cellRange;
    location tempcell = cell1;
    for (int i = cell1.col - 'A'; i <= cell2.col - 'A'; i++) {
        tempcell.col = char(i + 'A');
        for (int j = cell1.row; j <= cell2.row; j++) {
            tempcell.row = j;
            string cellname = locationToString(tempcell);
            cellRange.push_back(cellname);
        }
    }
    return cellRange;
}
