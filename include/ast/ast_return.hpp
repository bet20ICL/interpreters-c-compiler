#ifndef ast_return_hpp
#define ast_return_hpp

#include <iostream>
#include <string>

#include "ast_node.hpp"

class Return
    : public Node
{
private:
    NodePtr expression;
public:
    Return(NodePtr _expression)
        : expression(_expression)
    {}

    virtual ~Return()
    { delete expression; }

    virtual void print(std::ostream &dst, std::string indent) const override
    {
        dst << indent << "Return" << " [" << std::endl;
        dst << indent << indent_unit << "Expression:" << std::endl;
        expression->print(dst, indent + indent_unit);
        dst << indent << "]" << std::endl;
    }

    void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override
    {
        expression -> codeGen(dst, context, 2);
        dst<<"j "<< context->parent->return_label<<std::endl;
    }
    /*
    return offset
    return label
    bindings //later
    BINDINGS IS A MAPPING FROM VARIABLE NAME TO STACK LOCATION
    CONTEXT
    */

    //void getContext(){
    // pass address
    // return 
    //
};

#endif