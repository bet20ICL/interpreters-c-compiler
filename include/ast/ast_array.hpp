#ifndef ast_array_hpp
#define ast_array_hpp

#include <iostream>
#include <string>

#include "ast_node.hpp"
#include "print.hpp"

class Array_Declarator
    : public Node
{
private:
    NodePtr Identifier;
    NodePtr Index;
public:
    Array_Declarator(NodePtr &_identifier, NodePtr _index)
        : Identifier(_identifier)
        , Index(_index)
    {}

    virtual ContextPtr genContext(ContextPtr root, std::string type) const override
    {

        for (int i = 0; i < Index->getValue(); i++) {
            root->bindings.insert({ std::to_string(i) + Identifier->getName() , root->stack_size});
            root->stack_size += 4;
        }
        return root;
    }

    virtual void print(std::ostream &dst, std::string indent) const override
    {
        dst << indent << "Array_Declarator " << "[" << std::endl;
        dst << indent << indent_unit << "Name: " << Identifier->getName() << std::endl;
        dst << indent << indent_unit << "Index: " << std::endl;
        Index->print(dst, indent + indent_unit);
        dst << indent << "]" << std::endl;
    }

    virtual bool isArray() const override
    {
        return 1;
    }

};

class Array_Identifier
    : public Node
{
private:
    NodePtr Identifier;
    NodePtr Index;
public:
    Array_Identifier(NodePtr &_identifier, NodePtr _index)
        : Identifier(_identifier)
        , Index(_index)
    {}

    virtual void print(std::ostream &dst, std::string indent) const override
    {
        dst << indent << "Array_Identifier " << "[" << std::endl;
        dst << indent << indent_unit << "Name: " << Identifier->getName() << std::endl;
        dst << indent << indent_unit << "Index: " << std::endl;
        Index->print(dst, indent + indent_unit);
        dst << indent << "]" << std::endl;
    }

    virtual int getAddress(ContextPtr context) const override
    {
        return context->searchBindings(std::to_string(0) + Identifier->getName());
    }

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override 
    {
        int address = getAddress(context); // base address of array
        int offsetReg = destReg + 1;
        Index->codeGen(dst, context, offsetReg); // offsetReg now contains 
        dst << "sll $" << offsetReg << ", $" << offsetReg << ", 2" << std::endl; 
        dst << "addiu $" << offsetReg << ", $" << offsetReg << ", " << address << std::endl;
        dst << "addu $" << offsetReg <<", $" << offsetReg << ", $fp" << std::endl;
        dst << "lw $" << destReg << ", 0($" << offsetReg << ")" << std::endl;
        dst << "nop" << std::endl;
    }

    virtual bool isArray() const override
    {
        return 1;
    }

    virtual NodePtr getIndex() const
    {
        return Index;
    }
};

#endif