#ifndef ast_selection_statement_hpp
#define ast_selection_statement_hpp

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "ast_node.hpp"
#include "print.hpp"

class If_Statement
    : public Node
{
private:
    NodePtr condition;
    NodePtr statement_if;
public:
    If_Statement(NodePtr _condition, NodePtr _statement_if, NodePtr _statement_else)
        : condition(_condition)
        , statement_if(_statement_if)
    {
    }

    If_Statement(NodePtr _condition, NodePtr _statement_if)
        : condition(_condition)
        , statement_if(_statement_if)
    {
    }

    virtual ~If_Statement()
    { 
        delete condition; 
        delete statement_if;
    }

    virtual void print(std::ostream &dst, std::string indent) const override
    {
        dst << indent << "If Statement [" << std::endl;
        dst << indent << indent_unit << "Condition:" << std::endl;
        condition->print(dst, indent + indent_unit + indent_unit);
        dst << indent << indent_unit << "If Body:" <<std::endl;
        statement_if -> print(dst, indent + indent_unit + indent_unit);
        dst << indent << "]" << std::endl;

    }

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override
    {
        condition -> codeGen(dst, context, destReg);
        std::string end_if_label = makeName("EndIF");
        dst<<"beq $"<<destReg<<", $0,"<<end_if_label<<std::endl;
        statement_if -> codeGen(dst, context, destReg);
        dst<<end_if_label<<":"<<std::endl;
    }

};

class If_Else_Statement
    : public Node
{
private:
    NodePtr condition;
    NodePtr statement_if;
    NodePtr statement_else;
public:
    If_Else_Statement(NodePtr _condition, NodePtr _statement_if, NodePtr _statement_else)
        : condition(_condition)
        , statement_if(_statement_if)
        , statement_else(_statement_else)
    {
    }

    virtual ~If_Else_Statement()
    { 
        delete condition; 
        delete statement_if;
        delete statement_else;
    }

    virtual void print(std::ostream &dst, std::string indent) const override
    {
        dst << indent << "If Statement [" << std::endl;
        dst << indent << indent_unit << "Condition:" << std::endl;
        condition->print(dst, indent + indent_unit + indent_unit);
        dst << indent << indent_unit << "If Body:" <<std::endl;
        statement_if -> print(dst, indent + indent_unit + indent_unit);
        dst << indent << indent_unit << "Else Body:" <<std::endl;
        statement_else -> print(dst, indent + indent_unit + indent_unit);
        dst << indent << "]" << std::endl;

    }

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override
    {
        condition -> codeGen(dst, context, destReg);
        std::string else_label = makeName("Else");
        std::string end_if_label = makeName("EndIF");
        dst<<"beq $"<<destReg<<", $0,"<<else_label<<std::endl;
        statement_if -> codeGen(dst, context, destReg);
        dst<<"b "<<end_if_label<<std::endl;
        dst<<else_label<<":"<<std::endl;
        statement_else -> codeGen(dst, context, destReg);
        dst<<end_if_label<<":"<<std::endl;
    }

};

class Switch_Statement
    : public Node
{
    private:
        NodePtr expression;
        NodePtr statement;
    public:
        Switch_Statement(NodePtr _expression, NodePtr _statement)
        : expression(_expression)
        , statement(_statement)
        {}
        
        virtual ~Switch_Statement()
        { 
            delete expression; 
            delete statement;
        }

        virtual void print(std::ostream &dst, std::string indent) const override
        {
            dst << indent << "Switch Statement [" << std::endl;
            dst << indent << indent_unit << "Condition:" << std::endl;
            expression->print(dst, indent + indent_unit + indent_unit);
            dst << indent << indent_unit << "Switch Body:" <<std::endl;
            statement -> print(dst, indent + indent_unit + indent_unit);
            dst << indent << "]" << std::endl;
        }

        virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override
        {
        }

};

#endif