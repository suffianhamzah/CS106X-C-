/**
 * File: exp.cpp
 * -------------
 * This file implements the exp.h interface.
 */

#include <string>
#include "exp.h"
#include "strlib.h"
#include "error.h"

using namespace std;

/**
 * Implementation notes: Expression
 * --------------------------------
 * The Expression class itself implements only those methods that
 * are not designated as pure virtual.
 */

Expression::Expression() {
    /* Empty */
}

Expression::~Expression() {
    /* Empty */
}

/**
 * Implementation notes: FunctionExp
 * -------------------------------
 * The FunctionExp subclass represents a numeric constant.  The eval
 * method simply returns that value.
 */
FunctionExp::FunctionExp(std::string name, std::string formula, std::string cell1, std::string cell2) {
    this->name = name;
    this->formula = formula;
    range temp;
    temp.startCell = cell1;
    temp.stopCell = cell2;
    this->cRange = temp;
}

double FunctionExp::eval(SSModel& cellsheet) const {
    return cellsheet.getRangeVal(cRange.startCell, cRange.stopCell, formula);
}

string FunctionExp::toString() const {
    return name;
}

ExpressionType FunctionExp::getType() const {
    return FUNCTION;
}

range FunctionExp::getRange() const {
    return cRange;
}

/**
 * Implementation notes: DoubleExp
 * -------------------------------
 * The ConstantExp subclass represents a numeric constant.  The eval
 * method simply returns that value.
 */

DoubleExp::DoubleExp(double value) {
    this->value = value;
}

double DoubleExp::eval(SSModel& cellsheet) const {
    return value;
}

string DoubleExp::toString() const {
    return realToString(value);
}

ExpressionType DoubleExp::getType() const {
    return DOUBLE;
}

double DoubleExp::getDoubleValue() const {
    return value;
}

/**
 * Implementation notes: TextStringExp
 * -----------------------------------
 * The IdentifierExp subclass represents a text string constant.  The
 * implementation of eval simply returns 0.0.
 */

TextStringExp::TextStringExp(const string& str) {
    this->str = str;
}

double TextStringExp::eval(SSModel& cellsheet) const {
    return 0.0;
}

string TextStringExp::toString() const {
    return str;
}

ExpressionType TextStringExp::getType() const {
    return TEXTSTRING;
}

string TextStringExp::getTextStringValue() const {
    return '"' + str + '"';
}

/**
 * Implementation notes: IdentifierExp
 * -----------------------------------
 * The IdentifierExp subclass represents a variable name.  The
 * implementation of eval looks up that name in the evaluation context.
 */

IdentifierExp::IdentifierExp(const string& name) {
    this->name = name;
}

double IdentifierExp::eval(SSModel& cellsheet) const {
    // all references are valid
    //if (!cellsheet.nameIsValid(name)) error(name + " is not a valid cell reference");
    if (cellsheet.isDefined(name)) {
        return cellsheet.getCell(name)->getNumVal();
    }
    return 0.0;
}

string IdentifierExp::toString() const {
    return name;
}

ExpressionType IdentifierExp::getType() const {
    return IDENTIFIER;
}

string IdentifierExp::getIdentifierName() const {
    return name;
}

/**
 * Implementation notes: CompoundExp
 * ---------------------------------
 * The implementation of eval for CompoundExp evaluates the left and right
 * subexpressions recursively and then applies the operator.  Assignment is
 * treated as a special case because it does not evaluate the left operand.
 */

CompoundExp::CompoundExp(const string& op, const Expression *lhs, const Expression *rhs) {
    this->op = op;
    this->lhs = lhs;
    this->rhs = rhs;
}

CompoundExp::~CompoundExp() {
    delete lhs;
    delete rhs;
}

double CompoundExp::eval(SSModel& cellsheet) const {
    double right = rhs->eval(cellsheet);
    double left = lhs->eval(cellsheet);
    if (op == "+") return left + right;
    if (op == "-") return left - right;
    if (op == "*") return left * right;
    if (op == "/") return left / right; // divide by 0.0 gives ±INF
    
    error("Illegal operator in expression.");
    return 0.0;
}

string CompoundExp::toString() const {
    return '(' + lhs->toString() + ' ' + op + ' ' + rhs->toString() + ')';
}

ExpressionType CompoundExp::getType() const {
    return COMPOUND;
}

/*void CompoundExp::clear() {
    delete rhs;
    delete lhs;
}*/

string CompoundExp::getOperator() const {
    return op;
}

const Expression *CompoundExp::getLHS() const {
    return lhs;
}

const Expression *CompoundExp::getRHS() const {
    return rhs;
}

/**
 * Implementation notes: EvaluationContext
 * ---------------------------------------
 * The methods in the EvaluationContext class simply call the appropriate
 * method on the map used to represent the symbol table.
 */

/*void EvaluationContext::setValue(const string& var, double value) {
   symbolTable.put(var, value);
}

double EvaluationContext::getValue(const string& var) const {
   return 0.0;
}

bool EvaluationContext::isDefined(const string& var) const {
   return cellsheet->isDefined(var);
}

bool EvaluationContext::isNameValid(const std::string& var) const {
   return cellsheet->nameIsValid(var);
}*/
