/**
 * File: exp.h
 * -----------
 * This interface defines a class hierarchy for arithmetic expressions.
 */

#ifndef _exp_
#define _exp_

#include <string>
#include <cctype>
#include "map.h"
#include "tokenscanner.h"
#include "ssmodel.h"
#include "ssutil.h"


/* Forward reference */

//class EvaluationContext;

/*
 * Type: ExpressionType
 * --------------------
 * This enumerated type is used to differentiate the four different
 * expression types: DOUBLE, TEXTSTRING, IDENTIFIER, and COMPOUND.
 */

enum ExpressionType { DOUBLE, TEXTSTRING, IDENTIFIER, COMPOUND, FUNCTION };

/**
 * Class: Expression
 * -----------------
 * This class is used to represent a node in an expression tree.
 * Expression itself is an abstract class, which means that there are
 * never any objects whose primary type is Expression.  All objects are
 * instead created using one of the four concrete subclasses:
 *
 *  1. DoubleExp     -- a numeric constant
 *  2. TextStringExp -- a text string constant
 *  3. IdentifierExp -- a string representing an identifier
 *  4. CompoundExp   -- two expressions combined by an operator
 *  5. FunctionExp   -- a formula applied to a range of cells
 *
 * The Expression class defines the interface common to all expressions;
 * each subclass provides its own implementation of the common interface.
 */

class Expression {

public:

    /**
 * Constructor: Expression
 * -----------------------
 * Specifies the constructor for the base Expression class.  Each subclass
 * constructor will define its own constructor.
 */

    Expression();

    /**
 * Destructor: ~Expression
 * Usage: delete exp;
 * ------------------
 * The destructor deallocates the storage for this expression.  This method
 * must be declared virtual to ensure that the correct subclass destructor
 * is called when deleting an expression.
 */

    virtual ~Expression();

    /**
 * Method: eval
 * Usage: int value = exp->eval(context);
 * --------------------------------------
 * Evaluates this expression and returns its value in the context of
 * the specified EvaluationContext object.
 */

    virtual double eval(SSModel& cellsheet) const = 0;

    /**
 * Method: toString
 * Usage: string str = exp->toString();
 * ------------------------------------
 * Returns a string representation of this expression.
 */

    virtual std::string toString() const = 0;

    /**
 * Method: type
 * Usage: ExpressionType type = exp->getType();
 * --------------------------------------------
 * Returns the type of the expression, which must be one of the constants
 * DOUBLE, TEXTSTRING, IDENTIFIER, FUNCTION and COMPOUND.
 */

    virtual ExpressionType getType() const = 0;
    /**
 * Method: delete
 * Usage: void clear = exp->clear();
 * --------------------------------------------
 * Clears self of data;
 */

    //virtual void clear();
};

/**
 * Subclass: FunctionExp
 * -------------------
 * This subclass represents a formula( eg. median, stddev) applied to a range of cells
 */

class FunctionExp : public Expression {

public:

    /**
 * Constructor: FunctionExp
 * Usage: Expression *exp = new FunctionExp(str);
 * -------------------------------------------------
 * The constructor creates a new double constant expression.
 */

    FunctionExp(std::string name, std::string formula, std::string cell1, std::string cell2);

    /* Prototypes for the virtual methods overridden by this class */

    double eval(SSModel& cellsheet) const;
    std::string toString() const;
    ExpressionType getType() const;

    /* Prototypes of methods specific to this class */
    //double getDoubleValue() const;
    range getRange() const;

private:
    std::string name;
    std::string formula;
    range cRange;/* The value of the double constant */
};
/**
 * Subclass: DoubleExp
 * -------------------
 * This subclass represents a numeric constant.
 */

class DoubleExp : public Expression {

public:

    /**
 * Constructor: DoubleExp
 * Usage: Expression *exp = new DoubleExp(value);
 * -------------------------------------------------
 * The constructor creates a new double constant expression.
 */

    DoubleExp(double value);

    /* Prototypes for the virtual methods overridden by this class */

    double eval(SSModel& cellsheet) const;
    std::string toString() const;
    ExpressionType getType() const;
    
    /* Prototypes of methods specific to this class */
    double getDoubleValue() const;

private:
    double value;                   /* The value of the double constant */
};

/**
 * Subclass: TextStringExp
 * -----------------------
 * This subclass represents a text string constant.
 */

class TextStringExp : public Expression {
    
public:
    
    /**
 * Constructor: TextStringExp
 * Usage: Expression *exp = new TextStringExp(str);
 * ------------------------------------------------
 * The constructor creates a new text string constant expression.
 */
    
    TextStringExp(const std::string& str);
    
    /* Prototypes for the virtual methods overridden by this class */
    
    double eval(SSModel& cellsheet) const;
    std::string toString() const;
    ExpressionType getType() const;

    /* Prototypes of methods specific to this class */
    std::string getTextStringValue() const;
    
private:
    std::string str;              /* The value of the text string constant */
};

/**
 * Subclass: IdentifierExp
 * -----------------------
 * This subclass represents an identifier used as a variable name.
 */

class IdentifierExp : public Expression {

public:

    /**
 * Constructor: IdentifierExp
 * Usage: Expression *exp = new IdentifierExp(name);
 * -------------------------------------------------
 * The constructor creates an identifier expression with the specified name.
 */

    IdentifierExp(const std::string& name);

    /* Prototypes for the virtual methods overridden by this class */

    double eval(SSModel& cellsheet) const;
    std::string toString() const;
    ExpressionType getType() const;

    /* Prototypes of methods specific to this class */
    std::string getIdentifierName() const;

private:
    std::string name;            /* The name of the identifier */
};

/**
 * Subclass: CompoundExp
 * ---------------------
 * This subclass represents a compound expression consisting of
 * two subexpressions joined by an operator.
 */

class CompoundExp : public Expression {

public:

    /**
 * Constructor: CompoundExp
 * Usage: Expression *exp = new CompoundExp(op, lhs, rhs);
 * -------------------------------------------------------
 * The constructor initializes a new compound expression composed of
 * the operator (op) and the left and right subexpression (lhs and rhs).
 */

    CompoundExp(const std::string& op, const Expression *lhs, const Expression *rhs);

    /* Prototypes for the virtual methods overridden by this class */

    virtual ~CompoundExp();
    virtual double eval(SSModel& cellsheet) const;
    virtual std::string toString() const;
    virtual ExpressionType getType() const;
    //virtual void clear();
    /* Prototypes of methods specific to this class */
    std::string getOperator() const;
    const Expression *getLHS() const;
    const Expression *getRHS() const;

private:
    std::string op;              /* The operator string (+, -, *, /)  */
    const Expression *lhs, *rhs; /* The left and right subexpression  */
};

/**
 * Class: EvaluationContext
 * ------------------------
 * This class encapsulates the information that the evaluator needs to
 * know in order to evaluate an expression.
 */

/*class EvaluationContext {

public:
  EvaluationContext(Grid<Cell*>& cellsheet_) : cellsheet(cellsheet_) {}
**
 * Method: setValue
 * Usage: context.setValue(var, value);
 * ------------------------------------
 * Sets the value associated with the specified var.

   void setValue(const std::string& var, double value);

**
 * Method: getValue
 * Usage: int value = context.getValue(var);
 * -----------------------------------------
 * Returns the value associated with the specified variable.
 *

   double getValue(const std::string& var) const;

**
 * Method: isDefined
 * Usage: if (context.isDefined(var)) . . .
 * ----------------------------------------
 * Returns true if the specified variable is defined.


   bool isDefined(const std::string& var) const;
   bool isNameValid(const std::string& var) const;
private:
   Map<std::string, double> symbolTable;
   Grid<Cell*> cellsheet;
};
*/

#endif
