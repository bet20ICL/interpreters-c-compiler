#ifndef ast_argument_hpp
#define ast_argument_hpp

#include <iostream>
#include <string>

#include "ast_node.hpp"
#include "print.hpp"

class Argument
    : public Node
{
private:
    NodePtr expr;
public:
    Argument(NodePtr _expr)
        : expr(_expr)
    {}

    virtual void print(std::ostream &dst, std::string indent) const override
    {
        dst << indent << "Argument " << "[" << std::endl;
        expr->print(dst, indent + indent_unit);
        dst << indent << "]" << std::endl;
    }

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override 
    {
        expr->codeGen(dst, context, destReg);
        dst << "move $" << 4 + context->argCount << ", $" << destReg << std::endl;
        dst << "nop" << std::endl;
        (context->argCount) += 1;
    }

};

#endif