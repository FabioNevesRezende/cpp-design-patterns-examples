//
//  main.cpp
//  interpreter-pattern
//

#include <iostream>
#include <memory>

using std::string, std::cout, std::stoi, std::unique_ptr, std::move;

class Expression {
public:
    virtual int evaluate() = 0;
};
typedef unique_ptr<Expression> expression_ptr;

// 5 + (10 + 1)
class OperationExpression : public Expression {
    string operatorSymbol;
    expression_ptr leftHandSide;
    expression_ptr rightHandSide;
public:
    OperationExpression(const string& operatorSymbol, expression_ptr& lhs, expression_ptr& rhs) : operatorSymbol(operatorSymbol), leftHandSide(move(lhs)), rightHandSide(move(rhs)) {};
    int evaluate() override {
        if (operatorSymbol == "+") {
            return leftHandSide->evaluate() + rightHandSide->evaluate();
        } else if (operatorSymbol == "-") {
            return leftHandSide->evaluate() - rightHandSide->evaluate();
        } else {
            cout << "Unrecognized operator: " << operatorSymbol;
            return 0;
        }
    }
};
typedef unique_ptr<OperationExpression> operation_expression_ptr;

class NumberExpression : public Expression {
    string numberString;
public:
    NumberExpression(const string& numberString) : numberString(numberString) {};
    int evaluate() override {
        return stoi(numberString);
    }
};
typedef unique_ptr<NumberExpression> number_expression_ptr;

int main(int argc, const char * argv[]) {
    expression_ptr five = number_expression_ptr(new NumberExpression("5"));
    expression_ptr seven = number_expression_ptr(new NumberExpression("7"));
    expression_ptr fivePlusSeven = operation_expression_ptr(new OperationExpression("+", five, seven));

    cout << "5 + 7 = " << fivePlusSeven->evaluate() << "\n";
    
    expression_ptr thirteen = number_expression_ptr(new NumberExpression("13"));
    expression_ptr complexOp = operation_expression_ptr(new OperationExpression("-", thirteen, fivePlusSeven));
    
    cout << "13 - (5 + 7) = " << complexOp->evaluate() << "\n";
        
    return 0;
}

