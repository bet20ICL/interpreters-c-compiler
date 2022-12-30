#ifndef ast_iteration_statement_hpp
#define ast_iteration_statement_hpp

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "ast_node.hpp"
#include "print.hpp"

class While_Statement
    : public Node
{
    private:
        NodePtr condition;
        NodePtr while_body;
    public:
        While_Statement(NodePtr _condition, NodePtr _while_body)
        : condition(_condition)
        , while_body(_while_body)
        {}

        virtual ~While_Statement()
        { 
            delete condition; 
            delete while_body;
        }

        virtual void print(std::ostream &dst, std::string indent) const override
        {
            dst << indent << "While Statement [" << std::endl;
            dst << indent << indent_unit << "Condition:" << std::endl;
            condition->print(dst, indent + indent_unit + indent_unit);
            dst << indent << indent_unit << "While Body:" <<std::endl;
            while_body -> print(dst, indent + indent_unit + indent_unit);
            dst << indent << "]" << std::endl;
        }

        virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override
        {
            std::string start_while_label = makeName("StartWhile");
            std::string end_while_label = makeName("EndWhile");
            dst<<start_while_label<<":"<<std::endl;
            condition -> codeGen(dst, context, destReg);
            dst<<"beq $"<<destReg<<", $0,"<<end_while_label<<std::endl;
            while_body -> codeGen(dst, context, destReg);
            dst<<"b "<<start_while_label<<std::endl;
            dst<<end_while_label<<":"<<std::endl;
        }
};

class For_Loop
    : public Node
{
    private:
        NodePtr initializer;
        NodePtr test_expression;
        NodePtr increment;
        NodePtr loop_body;
    public:
        For_Loop(NodePtr _initializer, NodePtr _test_expression, NodePtr _increment, NodePtr _loop_body)
        : initializer(_initializer)
        , test_expression(_test_expression)
        , increment(_increment)
        , loop_body(_loop_body)
        {}

        ~For_Loop()
        {
            delete initializer;
            delete test_expression;
            delete increment;
            delete loop_body;
        }

        virtual void print(std::ostream &dst, std::string indent) const override
        {
            dst << indent << "For Loop [" << std::endl;
            dst << indent << indent_unit << "Initializer:" << std::endl;
            initializer->print(dst, indent + indent_unit + indent_unit);
            dst << indent << indent_unit << "Test Expression:" <<std::endl;
            test_expression -> print(dst, indent + indent_unit + indent_unit);
            dst << indent << indent_unit << "Increment:" <<std::endl;
            increment -> print(dst, indent + indent_unit + indent_unit);
            dst << indent << indent_unit << "Loop Body:" <<std::endl;
            loop_body -> print(dst, indent + indent_unit + indent_unit);
            dst << indent << "]" << std::endl;
        }

        virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override
        {
            initializer -> codeGen(dst, context, destReg);
            std::string start_for_label = makeName("StartFor");
            std::string end_for_label = makeName("EndFor");
            dst << start_for_label << ":" << std::endl;
            test_expression -> codeGen(dst, context, destReg);
            dst<<"beq $"<<destReg<<", $0, "<<end_for_label<<std::endl;
            loop_body -> codeGen(dst, context, destReg);
            increment -> codeGen(dst, context, destReg);
            dst<<"b "<<start_for_label<<std::endl;
            dst<<end_for_label<<":"<<std::endl;
        }
};

class For_Loop_Empty
    : public Node
{
    private:
        NodePtr initializer;
        NodePtr test_expression;
        NodePtr loop_body;
    public:
        For_Loop_Empty(NodePtr _initializer, NodePtr _test_expression, NodePtr _loop_body)
        : initializer(_initializer)
        , test_expression(_test_expression)
        , loop_body(_loop_body)
        {}

        ~For_Loop_Empty()
        {
            delete initializer;
            delete test_expression;
            delete loop_body;
        }

        virtual void print(std::ostream &dst, std::string indent) const override
        {
            dst << indent << "For Loop [" << std::endl;
            dst << indent << indent_unit << "Initializer:" << std::endl;
            initializer->print(dst, indent + indent_unit + indent_unit);
            dst << indent << indent_unit << "Test Expression:" <<std::endl;
            test_expression -> print(dst, indent + indent_unit + indent_unit);
            dst << indent << indent_unit << "Loop Body:" <<std::endl;
            loop_body -> print(dst, indent + indent_unit + indent_unit);
            dst << indent << "]" << std::endl;
        }

        virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override
        {
            initializer -> codeGen(dst, context, destReg);
            std::string start_for_label = makeName("StartFor");
            std::string end_for_label = makeName("EndFor");
            dst << start_for_label << ":" << std::endl;
            test_expression -> codeGen(dst, context, destReg);
            dst<<"beq $"<<destReg<<", $0, "<<end_for_label<<std::endl;
            loop_body -> codeGen(dst, context, destReg);
            dst<<"b "<<start_for_label<<std::endl;
            dst<<end_for_label<<":"<<std::endl;
        }
};

#endif