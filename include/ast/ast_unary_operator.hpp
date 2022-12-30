#ifndef ast_unary_operator_hpp
#define ast_unary_operator_hpp

#include <iostream>
#include <string>

#include "ast_node.hpp"
#include "print.hpp"

class Unary_Operator
    : public Node
{
private:
    NodePtr expression;
protected:
    Unary_Operator(NodePtr _expression)
        : expression(_expression)
    {}    
public:
    virtual ~Unary_Operator()
    {
        delete expression;
    }

    virtual const char *getOpcode() const = 0;

    virtual void print(std::ostream &dst, std::string indent) const override
    {
        dst << indent << "Unary_Operator [" << std::endl;
        dst << indent << indent_unit << "Expression:" << std::endl;
        expression->print(dst, indent + indent_unit);
        dst << indent << indent_unit << "Opcode:" << std::endl;
        dst << indent << indent_unit << getOpcode() << std::endl;
        dst << indent << "]" << std::endl;
    }

    virtual ContextPtr genContext(ContextPtr root, std::string type) const override
    {
        root->bindings.insert({expression->getName(), root->stack_size});
        return root;
    }

    NodePtr getExpr () const
    {
        return expression;
    }
};

class Post_Increment
    : public Unary_Operator
{
protected:
    virtual const char *getOpcode() const
    { return "post++"; }
public:
    Post_Increment(NodePtr _expression)
        : Unary_Operator(_expression)
    {}

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override
    {
        int address = getExpr()->getAddress(context);
        int l = destReg;
        int r = destReg + 1;
        getExpr()->codeGen(dst, context, l);
        dst << "addiu $" << r << ", $" << l << ", 1" << std::endl;
        dst << "sw $" << r << ", " << address << "($fp)" << std::endl;
    }
};

class Post_Decrement
    : public Unary_Operator
{
protected:
    virtual const char *getOpcode() const
    { return "post--"; }
public:
    Post_Decrement(NodePtr _expression)
        : Unary_Operator(_expression)
    {}

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override
    {
        int address = getExpr()->getAddress(context);
        int l = destReg;
        int r = destReg + 1;
        getExpr()->codeGen(dst, context, l);
        dst << "addiu $" << r << ", $" << l << ", -1" << std::endl;
        dst << "sw $" << r << ", " << address << "($fp)" << std::endl; 
    }
};

class Pre_Increment
    : public Unary_Operator
{
protected:
    virtual const char *getOpcode() const
    { return "pre++"; }
public:
    Pre_Increment(NodePtr _expression)
        : Unary_Operator(_expression)
    {}

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override
    {
        getExpr()->codeGen(dst, context, destReg);
        int address = getExpr()->getAddress(context);
        dst << "addiu $" << destReg << ", $" << destReg <<", 1" << std::endl;
        dst << "sw $" << destReg << " , " << address << "($fp)" << std::endl;
    }
};

class Pre_Decrement
    : public Unary_Operator
{
protected:
    virtual const char *getOpcode() const
    { return "pre--"; }
public:
    Pre_Decrement(NodePtr _expression)
        : Unary_Operator(_expression)
    {}

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override
    {
        getExpr()->codeGen(dst, context, destReg);
        int address = getExpr()->getAddress(context);
        dst << "addiu $" << destReg << ", $" << destReg <<", -1" << std::endl;
        dst << "sw $" << destReg << " , " << address << "($fp)" << std::endl;
    }
};

class Neg_Operator
    : public Unary_Operator
{
protected:
    virtual const char *getOpcode() const
    { return "-"; }
public:
    Neg_Operator(NodePtr _expression)
        : Unary_Operator(_expression)
    {}

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override
    {
        getExpr()->codeGen(dst, context, destReg);
        dst << "subu $" << destReg << ", $0, $" << destReg << std::endl;
    }
};

class lNOT_Operator
    : public Unary_Operator
{
protected:
    virtual const char *getOpcode() const
    { return "!"; }
public:
    lNOT_Operator(NodePtr _expression)
        : Unary_Operator(_expression)
    {}

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override
    {
        getExpr()->codeGen(dst, context, 8);
        dst << "sltu $" << destReg << ", $" << destReg << ", 1" << std::endl;
        dst << "andi $" << destReg << ", $" << destReg <<", 0x00ff" << std::endl;
    }
};

class bNOT_Operator
    : public Unary_Operator
{
protected:
    virtual const char *getOpcode() const
    { return "~"; }
public:
    bNOT_Operator(NodePtr _expression)
        : Unary_Operator(_expression)
    {}

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override
    {
        getExpr()->codeGen(dst, context, destReg);
        dst << "nor $" << destReg << ", $" << destReg << ", $0" << std::endl;
    }
};

class Size_Of_Operator
    : public Unary_Operator
{
protected:
    virtual const char *getOpcode() const
    { return "Size_Of"; }
public:

    Size_Of_Operator(NodePtr _expression)
        : Unary_Operator(_expression)
    {}

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override
    {
        getExpr()->codeGen(dst, context, destReg);
        std::string type = getExpr()->getType(context);
        int size = 4;
        if (type == "double") {
            size = 8;
        } else if (type == "char") {
            size = 1;
        }
        dst << "li $" << destReg << ", " << size << std::endl;
    }
};

#endif