#ifndef ast_expression_hpp
#define ast_expression_hpp

#include <string>
#include <iostream>

#include "ast_node.hpp"

class Expression
    : public Node
{
private:

protected:
    virtual const char *getExpressionType() const = 0;
};

class Empty_Expression
    : public Node
{
public:
    Empty_Expression()
    {}

    void print(std::ostream &dst, std::string indent) const override
    {
        dst << indent << "Empty_Expression " << std::endl;
    }
};

#endif