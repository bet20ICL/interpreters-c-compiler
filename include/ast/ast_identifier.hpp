#ifndef ast_identifier_hpp
#define ast_identifier_hpp

#include <iostream>
#include <string>

#include "ast_node.hpp"

class Identifier
    : public Node
{
private:
    std::string Name;
public:
    Identifier(const std::string &_name)
        : Name(_name)
    {}

    virtual std::string getName() const override
    {
        return Name;
    }

    virtual ContextPtr genContext(ContextPtr root, std::string type) const override
    {
        root->bindings.insert({getName(), root->stack_size});
        root->stack_size += 4;
        root->types.insert({getName(), type});
        return root;
    }

    virtual void print(std::ostream &dst, std::string indent) const override
    {
        dst << indent << "Identifier " << "[" << std::endl;
        dst << indent << indent_unit << "Name: " << getName() << std::endl;
        dst << indent << "]" << std::endl;
    }

    virtual int getAddress(ContextPtr context) const override
    {
        return context->searchBindings(getName());
    }

    virtual std::string getType(ContextPtr context) const override
    {
        return context->searchTypes(getName());
    }


    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override 
    {
        int address = getAddress(context);
        dst << "lw $" << destReg << ", " << address << "($fp)" << std::endl;
        dst << "nop" << std::endl;
    }
};

#endif