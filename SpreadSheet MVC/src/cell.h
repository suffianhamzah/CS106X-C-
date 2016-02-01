#ifndef CELL_H
#define CELL_H

#include <string>
#include "strlib.h"
#include "vector.h"
#include "set.h"
class Expression;
class SSModel;

class Cell {
public:
    Cell(std::string _cellname);
    ~Cell();
    void updateSubscribe(double value);
    std::string getVal();
    double getNumVal();
    void setExp(Expression* _exp);
    std::string eval(SSModel& cellsheet);
    void addSubscribe(const std::string& name);
    void addListen(std::string name);
    void removeSubscribe(const std::string& name);
    void removeListener(const std::string& name);
    std::string printSubscribe();
    std::string printListen();
    std::string getName();
    void removeExp();
private:
    std::string cellname;
    std::string strValue;
    Expression *exp;
    double numValue;
    //Vector<Cell*> subscribers;
    Set<std::string> subscribers;
    Set<std::string> listeners;
};

#endif // CELL_H
