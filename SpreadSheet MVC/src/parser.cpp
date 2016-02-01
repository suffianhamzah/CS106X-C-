/*
 * File: parser.cpp
 * ----------------
 * This file implements the parser.h interface.
 */

#include <iostream>
#include <string>

#include "error.h"
#include "exp.h"
#include "parser.h"
#include "strlib.h"
#include "tokenscanner.h"
#include "ssmodel.h"
#include "ssutil.h"


using namespace std;

static Expression *readE(TokenScanner& scanner, int prec, SSModel& cellsheet, const std::string& parentCell);
static Expression *readT(TokenScanner& scanner,  SSModel& cellsheet, const std::string& parentCell);
static int precedence(const std::string& token);
static bool isFormula(string& mainFormula, string& formula, string& cellname1, string& cellname2, TokenScanner& scanner, SSModel& cellsheet);
static bool checkRange(string& cellname1, string& cellname2, SSModel& cellsheet);
static bool checkCircularFormula(const string &parentCell, const string &cellname1, const string &cellname2, SSModel &cellsheet);



/**
 * Implementation notes: parseExp
 * ------------------------------
 * This code just reads an expression and then checks for extra tokens.
 */

Expression *parseExp(TokenScanner& scanner, SSModel& cellsheet, const std::string& parentCell) {
    Expression *exp = readE(scanner, 0,cellsheet, parentCell);
    if (scanner.hasMoreTokens()) {
        error("Unexpected token \"" + scanner.nextToken() + "\"");
    }
    return exp;
}

/**
 * Implementation notes: readE
 * Usage: exp = readE(scanner, prec);
 * ----------------------------------
 * The implementation of readE uses precedence to resolve the ambiguity in
 * the grammar.  At each level, the parser reads operators and subexpressions
 * until it finds anmonit operator whose precedence is greater than the prevailing
 * one.  When a higher-precedence operator is found, readE calls itself
 * recursively to read that subexpression as a unit.
 */

Expression *readE(TokenScanner& scanner, int prec,  SSModel& cellsheet, const std::string& parentCell) {
    Expression *exp = readT(scanner, cellsheet, parentCell);
    string token;

    while (true) {
        token = scanner.nextToken();
        int tprec = precedence(token);
        if (tprec <= prec) break;
        Expression *rhs = readE(scanner, tprec, cellsheet, parentCell);
        exp = new CompoundExp(token, exp, rhs);
    }
    scanner.saveToken(token);
    return exp;
}

/**
 * Implementation notes: readT
 * ---------------------------
 * This function scans a term, which is either an integer, an identifier,
 * or a parenthesized subexpression.
 */
Expression *readT(TokenScanner& scanner,  SSModel& cellsheet, const std::string& parentCell) {

    string token = scanner.nextToken();
    cout << token << endl;
    TokenType type = scanner.getTokenType(token);
    if (type == WORD) {
        string errorMsg;
        token = toLowerCase(token);
        string bracket = scanner.nextToken();
        if (bracket == "(") {
            string mainFormula = token + bracket;
            string cellname1, cellname2;
            if (isFormula(mainFormula,token,cellname1,cellname2,scanner,cellsheet)
                && checkCircularFormula(parentCell, cellname1, cellname2, cellsheet)) {
                return new FunctionExp(mainFormula,token,cellname1,cellname2);
            }
            errorMsg = "Invalid Formula";
        } else {
            //check if its a cellname or not
            scanner.saveToken(bracket);
            token = toUpperCase(token);
            if (cellsheet.nameIsValid(token)) {//(isalpha(token[0]) && isdigit(token[1]) && token[1] > 0) {
                if (cellsheet.checkCircular(parentCell, token)) {
                    return new IdentifierExp(token);
                } else {
                    errorMsg = "Invalid reference. Circular Dependency detected";
                }
            } else {
                errorMsg = "Invalid CellName. Must be A-Z + 1-35";
            }
        }
        error(errorMsg);
    }
    if (type == NUMBER) return new DoubleExp(stringToReal(token));
    if (type == STRING) return new TextStringExp(token.substr(1, token.length() - 2));
    if (token != "(") error("Unexpected token \"" + token + "\"");
    Expression *exp = readE(scanner, 0, cellsheet, parentCell);
    if (scanner.nextToken() != ")") {
        error("Unbalanced parentheses");
    }
    return exp;
}

/**
 * Implementation notes: precedence
 * --------------------------------
 * This function checks the token against each of the defined operators
 * and returns the appropriate precedence value.
 */
int precedence(const string& token) {
    if (token == "+" || token == "-") return 1;
    if (token == "*" || token == "/") return 2;
    return 0;
}

static bool isFormula(string& mainFormula, string& formula, string& cellname1, string& cellname2, TokenScanner& scanner, SSModel& cellsheet) {
    if (cellsheet.isFormula(formula)) {
        cellname1 = toUpperCase(scanner.nextToken());
        mainFormula += cellname1 + scanner.nextToken();
        cellname2 = toUpperCase(scanner.nextToken());
        if (checkRange(cellname1,cellname2, cellsheet)) {
            string bracket = scanner.nextToken();
            if (bracket == ")") {
                mainFormula += cellname2 + bracket;
                return true;
            }
        }
    }
    return false;
}

static bool checkRange(string& cellname1, string& cellname2, SSModel& cellsheet) {
    location cell1, cell2;
    return (stringToLocation(cellname1,cell1) && stringToLocation(cellname2, cell2) &&
            cellsheet.nameIsValid(cellname1) && cellsheet.nameIsValid(cellname2) &&
            (cell2.row > cell1.row || cell2.col > cell1.col));
}



static bool checkCircularFormula(const string& parentCell, const string& cellname1, const string& cellname2, SSModel& cellsheet) {
    Vector<std::string> cells = cellsheet.cellRange(cellname1,cellname2);
    for (string cell : cells) {
        if (!cellsheet.checkCircular(parentCell, cell)) {
            return false;
        }
    }
    return true;
}

