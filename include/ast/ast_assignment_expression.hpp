#ifndef ast_assignment_expression_hpp
#define ast_assignment_expression_hpp

#include <iostream>
#include <string>

#include "ast_node.hpp"

class Assignment_Expression
    : public Node
{
private:
    NodePtr unary;
    NodePtr assignment_operator;
    NodePtr assignment_expression;
    
protected:
public:
    Assignment_Expression(NodePtr _unary, NodePtr _assignment_operator, NodePtr _assignment_expression)
        : unary(_unary)
        , assignment_operator(_assignment_operator)
        , assignment_expression(_assignment_expression)
    {}    

    virtual ~Assignment_Expression()
    {
        delete unary;
        delete assignment_operator;
        delete assignment_expression;
    }

    virtual void print(std::ostream &dst, std::string indent) const override
    {
        dst << indent << "Assignment_Expression [" << std::endl;
        dst << indent << indent_unit << "Unary:" << std::endl;
        unary->print(dst, indent + indent_unit);
        dst << indent << indent_unit << "Operator:" << std::endl;
        assignment_operator->print(dst, indent + indent_unit);
        dst << indent << indent_unit << "Expression:" << std::endl;
        assignment_expression->print(dst, indent + indent_unit);
        dst << indent << "]" << std::endl;
    }

    virtual ContextPtr genContext(ContextPtr root, std::string type) const override
    {
        return unary->genContext(root, type);
    }
    
    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override
    { 
        // context->searchBindings(unary->getName());
        int l = destReg;    // 8
        int r = destReg + 1; // 9
        unary->codeGen(dst, context, l); // 8
        assignment_expression->codeGen(dst, context, r); // 9
        if (assignment_operator->getName() == "=") {
            dst << "move $" << l << ", $" << r << std::endl; 
        } else if (assignment_operator->getName() == "*=") {
            dst << "mult $" << l <<", $" << r << std::endl;
            dst << "mflo $" << destReg << std::endl;
        } else if (assignment_operator->getName() == "/=") {
            dst << "div $0, $" << l << ", $" << r << std::endl;
            dst << "mflo $" << destReg << std::endl;
        } else if (assignment_operator->getName() == "%=") {
            dst << "div $0, $" << l << ", $" << r << std::endl;
            dst << "mfhi $" << destReg << std::endl;
        }else if (assignment_operator->getName() == "+=") {
            dst << "add $" << destReg << ", $" << l << ", $" << r << std::endl;
        } else if (assignment_operator->getName() == "-=") {
            dst << "sub $" << destReg << ", $" << l <<", $" << r << std::endl;
        } else if (assignment_operator->getName() == "<<=") {
            dst << "sll $" << destReg << ", $"<< l <<", $" << r << std::endl;
        } else if (assignment_operator->getName() == ">>=") {
            dst << "sra $" << destReg << ", $"<< l <<", $" << r << std::endl;
        } else if (assignment_operator->getName() == "&=") {
            dst << "and $" << destReg << ", $"<< l <<", $" << r << std::endl;
        } else if (assignment_operator->getName() == "|=") {
            dst << "or $" << destReg << ", $"<< l << ", $" << r << std::endl;
        } else if (assignment_operator->getName() == "^=") {
            dst << "xor $" << destReg << ", $" << l << ", $" << r << std::endl;
        }
        if (unary->isArray()) {
            dst << "move $9, $" << destReg << std::endl;
            int address = unary->getAddress(context); // get base offset address of array
            int offsetReg = destReg + 1; 
            (unary->getIndex())->codeGen(dst, context, offsetReg); // get index of array
            dst << "sll $" << offsetReg << ", $" << offsetReg << ", 2" << std::endl;
            dst << "addiu $" << offsetReg << ", $" << offsetReg << ", " << address << std::endl;
            dst << "addu $" << offsetReg <<", $" << offsetReg << ", $fp" << std::endl; // get actual address
            dst << "sw $" << destReg << ", 0($" << offsetReg << ")" << std::endl;
            dst << "nop" << std::endl; 
        } else{
            int address = unary->getAddress(context);
            dst << "sw $" << destReg << ", " << address << "($fp)" << std::endl;
            dst << "nop" << std::endl;
        }
        
    }
};

#endif