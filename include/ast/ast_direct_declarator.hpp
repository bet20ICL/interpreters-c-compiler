#ifndef ast_direct_declarator_hpp
#define ast_direct_declarator_hpp

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "ast_node.hpp"

class Declarator
    : public Node
{
private:

public:
};

class Function_Declarator_Empty
    : public Declarator
{
private:
    NodePtr identifier;
public:
    Function_Declarator_Empty(NodePtr _identifier)
        : identifier(_identifier)
    {}

    virtual ~Function_Declarator_Empty()
    { 
        delete identifier; 
    }

    virtual void print(std::ostream &dst, std::string indent) const override
    {
        dst << indent << "Function Declarator" << " [" << std::endl;
        dst << indent << indent_unit << "Direct Declarator:" << std::endl;
        identifier->print(dst, indent + indent_unit);
        dst << indent << "]" << std::endl;
    }

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override
    {
        dst << ".globl " << identifier->getName() << std::endl;
        dst << identifier->getName() << ":" << std::endl;
    }

};

class Function_Declarator_Inputs
    : public Declarator
{
private:
    NodePtr identifier;
    NodePtr parameter_list;
    ContextPtr context;
public:
    Function_Declarator_Inputs(NodePtr _identifier, NodePtr _parameter_list)
        : identifier(_identifier)
        , parameter_list(_parameter_list)
    {}

    virtual ~Function_Declarator_Inputs()
    { 
        delete identifier; 
        delete parameter_list;
    }

    virtual void print(std::ostream &dst, std::string indent) const override
    {
        dst << indent << "Function Declarator" << " [" << std::endl;
        dst << indent << indent_unit << "Direct Declarator:" << std::endl;
        identifier->print(dst, indent + indent_unit);
        dst << indent << indent_unit << "Parameter List:" << std::endl;
        parameter_list->print(dst, indent + indent_unit);
        dst << indent << "]" << std::endl;
    }

    virtual ContextPtr genContext(ContextPtr root, std::string type) const override
    {
        return parameter_list->genContext(root, type);
    }

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override
    {
        dst << ".globl " << identifier->getName() << std::endl;
        dst << identifier->getName() << ":" << std::endl;
    }
};



#endif