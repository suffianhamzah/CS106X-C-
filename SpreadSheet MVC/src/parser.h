/**
 * File: parser.h
 * --------------
 * This file acts as the interface to the parser module.
 */

#ifndef _parser_
#define _parser_

#include <string>
#include "exp.h"
#include "map.h"

/**
 * Function: parseExp
 * Usage: Expression *exp = parseExp(scanner);
 * -------------------------------------------
 * Parses a complete expression from the specified TokenScanner object,
 * making sure that there are no tokens left in the scanner at the end.
 */
class SSModel;
Expression *parseExp(TokenScanner& scanner, SSModel& cellsheet, const std::string& parentCell);

#endif
