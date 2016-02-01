#include "cell.h"
#include "exp.h"
#include "ssmodel.h"
Cell::Cell(std::string _cellname) : cellname(_cellname), numValue(0.0), exp(nullptr) {}

Cell::~Cell() {
    removeExp();
}

std::string Cell::getVal() {
    if (!exp) {
        return "0";
    }
    return exp->toString();
}

std::string Cell::eval(SSModel& cellsheet) {
    std::string strVal = "";
    if (exp->getType() == TEXTSTRING) {
        strValue = exp->toString();
    } else {
        numValue = exp->eval(cellsheet);
        strValue = realToString(numValue);
    }

    return strValue;
}
std::string Cell::getName() {
    return cellname;
}

std::string Cell::printSubscribe() {
    return subscribers.toString();
}

std::string Cell::printListen() {
    return listeners.toString();
}

void Cell::setExp(Expression *_exp) {
    exp = _exp;
}

double Cell::getNumVal() {
    return numValue;
}

void Cell::removeExp() {
    if(exp == nullptr) {
        return;
    }
    if (exp->getType() == COMPOUND) {
        exp->~Expression();
    } else {
        delete exp;
    }
}

void Cell::addSubscribe(const std::string& name) {
    subscribers.add(name);
}

void Cell::addListen(std::string name) {
    listeners.add(name);
}

void Cell::removeSubscribe(const std::string& name) {
    subscribers.remove(name);
}

void Cell::removeListener(const std::string& name) {
    listeners.remove(name);
}
