#ifndef ast_ternary_hpp
#define ast_ternary_hpp

#include <iostream>
#include <string>
#include "ast_node.hpp"
#include "print.hpp"

class Ternary_Operator
    : public Node
{
private:
    NodePtr condition;
    NodePtr true_node;
    NodePtr false_node;

public:
    Ternary_Operator(NodePtr _condition, NodePtr _true_node, NodePtr _false_node)
        : condition(_condition)
        , true_node(_true_node)
        , false_node(_false_node)
    {}

    virtual void print(std::ostream &dst, std::string indent) const override
    {
        dst << indent << "Ternary" << " [" << std::endl;
        dst << indent << indent_unit << "Condition:" << std::endl;
        condition->print(dst, indent + indent_unit);
        dst << indent << indent_unit << "True_Branch:" << std::endl;
        true_node->print(dst, indent + indent_unit);
        dst << indent << indent_unit << "False_Branch:" << std::endl;
        false_node->print(dst, indent + indent_unit);
        dst << indent << "]" << std::endl;
    }

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const 
    {
        std::string false_label = "." + makeName("false_label");
        std::string end_label = "." + makeName("end_label");
        
        condition->codeGen(dst, context, destReg);
        dst << "beq $"<< destReg <<", $0, "<< false_label << std::endl;
        dst << "nop" << std::endl;
        true_node->codeGen(dst, context, destReg);
        dst << "b " << end_label << std::endl;
        dst << "nop" << std::endl;
        dst << false_label << ":" << std::endl;
        false_node->codeGen(dst, context, destReg);
        dst << end_label << ":" << std::endl;
    }
};


#endif