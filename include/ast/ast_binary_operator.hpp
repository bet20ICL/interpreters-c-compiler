#ifndef ast_binary_operator_hpp
#define ast_binary_operator_hpp

#include <iostream>
#include <string>

#include "ast_node.hpp"
#include "print.hpp"

class Binary_Operator
    : public Node
{
private:
    NodePtr left;
    NodePtr right;
protected:
    Binary_Operator(NodePtr _left, NodePtr _right)
        : left(_left)
        , right(_right)
    {}
public:
    virtual ~Binary_Operator()
    {
        delete left;
        delete right;
    }

    virtual const char *getOpcode() const = 0;

    NodePtr getLeft () const
    {
        return left;
    }

    NodePtr getRight () const
    {
        return right;
    }

    virtual void print(std::ostream &dst, std::string indent) const override
    {
        dst << indent << getOpcode() << " [" << std::endl;
        dst << indent << indent_unit << "Left:" << std::endl;
        left->print(dst, indent + indent_unit);
        dst << indent << indent_unit << "Right:" << std::endl;
        right->print(dst, indent + indent_unit);
        dst << indent << "]" << std::endl;
    }
};

class Add_Operator
    : public Binary_Operator
{
private:
protected:
    virtual const char *getOpcode() const override
    { return "Add"; }
public:
    Add_Operator(NodePtr _left, NodePtr _right)
        : Binary_Operator(_left, _right)
    {}

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const 
    {
        int l = destReg;
        int r = destReg + 1;
        getLeft()->codeGen(dst, context, l);
        getRight()->codeGen(dst, context, r);
        dst << "add $" << destReg << ", $" << l << ", $" << r << std::endl;
    }
};

class Sub_Operator
    : public Binary_Operator
{
private:
protected:
    virtual const char *getOpcode() const override
    { return "Sub"; }
public:
    Sub_Operator(NodePtr _left, NodePtr _right)
        : Binary_Operator(_left, _right)
    {}

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const 
    {
        int l = destReg;
        int r = destReg + 1;
        getLeft()->codeGen(dst, context, l);
        getRight()->codeGen(dst, context, r);
        dst << "sub $" << destReg << ", $" << l << ", $" << r << std::endl;
    }
};

class bAND_Operator
    : public Binary_Operator
{
private:
protected:
    virtual const char *getOpcode() const override
    { return "bAND"; }
public:
    bAND_Operator(NodePtr _left, NodePtr _right)
        : Binary_Operator(_left, _right)
    {}

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const 
    {
        int l = destReg;
        int r = destReg + 1;
        getLeft()->codeGen(dst, context, l);
        getRight()->codeGen(dst, context, r);
        dst << "and $" << destReg << ", $" << l << ", $" << r << std::endl;
    }
};

class bOR_Operator
    : public Binary_Operator
{
private:
protected:
    virtual const char *getOpcode() const override
    { return "bOR"; }
public:
    bOR_Operator(NodePtr _left, NodePtr _right)
        : Binary_Operator(_left, _right)
    {}

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const 
    {
        int l = destReg;
        int r = destReg + 1;
        getLeft()->codeGen(dst, context, l);
        getRight()->codeGen(dst, context, r);
        dst << "or $" << destReg << ", $" << l << ", $" << r << std::endl;
    }
};

class bXOR_Operator
    : public Binary_Operator
{
private:
protected:
    virtual const char *getOpcode() const override
    { return "bXOR"; }
public:
    bXOR_Operator(NodePtr _left, NodePtr _right)
        : Binary_Operator(_left, _right)
    {}

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const 
    {
        int l = destReg;
        int r = destReg + 1;
        getLeft()->codeGen(dst, context, l);
        getRight()->codeGen(dst, context, r);
        dst << "xor $" << destReg << ", $" << l << ", $" << r << std::endl;
    }
};

class LT_Operator
    : public Binary_Operator
{
private:
protected:
    virtual const char *getOpcode() const override
    { return "<"; }
public:
    LT_Operator(NodePtr _left, NodePtr _right)
        : Binary_Operator(_left, _right)
    {}

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const 
    {
        int l = destReg;
        int r = destReg + 1;
        getLeft()->codeGen(dst, context, l);
        getRight()->codeGen(dst, context, r);
        dst << "slt $" << l << ", $" << l << ", $" << r << std::endl;
        dst << "andi $" << destReg << ", $" << l << " , 0x0ff" << std::endl;
    }
};

class GT_Operator
    : public Binary_Operator
{
private:
protected:
    virtual const char *getOpcode() const override
    { return ">"; }
public:
    GT_Operator(NodePtr _left, NodePtr _right)
        : Binary_Operator(_left, _right)
    {}

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const 
    {
        int l = destReg;
        int r = destReg + 1;
        getLeft()->codeGen(dst, context, l);
        getRight()->codeGen(dst, context, r);
        dst << "slt $" << l << ", $" << r << ", $" << l << std::endl;
        dst << "andi $" << destReg << ", $" << l << " , 0x0ff" << std::endl;
    }
};

class LET_Operator
    : public Binary_Operator
{
private:
protected:
    virtual const char *getOpcode() const override
    { return "<="; }
public:
    LET_Operator(NodePtr _left, NodePtr _right)
        : Binary_Operator(_left, _right)
    {}

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const 
    {
        int l = destReg;
        int r = destReg + 1;
        getLeft()->codeGen(dst, context, l);
        getRight()->codeGen(dst, context, r);
        dst << "slt $" << l << ", $" << r << ", $" << l << std::endl;
        dst << "xori $" << l << ", $" << l << ", 0x1" << std::endl;
        dst << "andi $" << destReg << ", $" << l <<", 0x00ff" << std::endl;
    }
};

class GET_Operator
    : public Binary_Operator
{
private:
protected:
    virtual const char *getOpcode() const override
    { return ">="; }
public:
    GET_Operator(NodePtr _left, NodePtr _right)
        : Binary_Operator(_left, _right)
    {}

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const 
    {
        int l = destReg;
        int r = destReg + 1;
        getLeft()->codeGen(dst, context, l);
        getRight()->codeGen(dst, context, r);
        dst << "slt $" << l << ", $" << l << ", $" << r << std::endl;
        dst << "xori $" << l << ", $" << l << ", 0x1" << std::endl;
        dst << "andi $" << destReg << ", $" << l <<", 0x00ff" << std::endl;
    }
};

class lAND_Operator
    : public Binary_Operator
{
private:
protected:
    virtual const char *getOpcode() const override
    { return "&&"; }
public:
    lAND_Operator(NodePtr _left, NodePtr _right)
        : Binary_Operator(_left, _right)
    {}

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const 
    {
        std::string result0 = "." + makeName("result0");
        std::string result1 = "." + makeName("result1");
        int l = destReg;
        int r = destReg + 1;
        getLeft()->codeGen(dst, context, l);
        getRight()->codeGen(dst, context, r);
        dst << "beq $" << l <<", $0, " << result0 << std::endl;
        dst << "nop" << std::endl;
        dst << "beq $"<< r <<", $0, " << result0 << std::endl;
        dst << "nop" << std::endl;
        dst << "li $" << destReg << ", 1" << std::endl;
        dst << "b " << result1 << std::endl;
        dst << "nop" << std::endl;
        dst << result0 << ":" << std::endl;
        dst << "move $" << destReg << ", $0" << std::endl;
        dst << result1 << ":" << std::endl;
    }
};

class lOR_Operator
    : public Binary_Operator
{
private:
protected:
    virtual const char *getOpcode() const override
    { return "||"; }
public:
    lOR_Operator(NodePtr _left, NodePtr _right)
        : Binary_Operator(_left, _right)
    {}

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const 
    {
        std::string result0 = "." + makeName("result0");
        std::string result1 = "." + makeName("result1");
        std::string end = "." + makeName("end");
        int l = destReg;
        int r = destReg + 1;
        getLeft()->codeGen(dst, context, l);
        getRight()->codeGen(dst, context, r);
        dst << "bne $" << l << ", $0, " << result1 << std::endl;
        dst << "nop" << std::endl;
        dst << "beq $"<< r <<", $0, " << result0 << std::endl;
        dst << "nop" << std::endl;
        dst << result1 << ":" << std::endl;
        dst << "li $" << destReg << ", 1" << std::endl;
        dst << "b " << end << std::endl; 
        dst << "nop" << std::endl;
        dst << result0 << ":" << std::endl;
        dst << "move $" << destReg << ", $0" << std::endl;
        dst << end << ":" << std::endl;
    }
};

class SLL_Operator
    : public Binary_Operator
{
private:
protected:
    virtual const char *getOpcode() const override
    { return "<<"; }
public:
    SLL_Operator(NodePtr _left, NodePtr _right)
        : Binary_Operator(_left, _right)
    {}

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const 
    {
        int l = destReg;
        int r = destReg + 1;
        getLeft()->codeGen(dst, context, l);
        getRight()->codeGen(dst, context, r);
        dst << "sll $" << destReg << ", $"<< l <<", $" << r << std::endl;
    }
};

class SRA_Operator
    : public Binary_Operator
{
private:
protected:
    virtual const char *getOpcode() const override
    { return ">>"; }
public:
    SRA_Operator(NodePtr _left, NodePtr _right)
        : Binary_Operator(_left, _right)
    {}

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const 
    {
        int l = destReg;
        int r = destReg + 1;
        getLeft()->codeGen(dst, context, l);
        getRight()->codeGen(dst, context, r);
        dst << "sra $" << destReg << ", $" << l << ", $" << r << std::endl;
    }
};


class EQ_Operator
    : public Binary_Operator
{
private:
protected:
    virtual const char *getOpcode() const override
    { return "=="; }
public:
    EQ_Operator(NodePtr _left, NodePtr _right)
        : Binary_Operator(_left, _right)
    {}

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const 
    {
        int l = destReg;
        int r = destReg + 1;
        getLeft()->codeGen(dst, context, l);
        getRight()->codeGen(dst, context, r);
        dst << "xor $" << l <<", $" << l <<", $" << r << std::endl;
        dst << "sltu $" << l << ", $" << l <<", 1" << std::endl;
        dst << "andi $" << destReg << ", $" << l << ", 0x00ff" << std::endl;
    }
};


class NE_Operator
    : public Binary_Operator
{
private:
protected:
    virtual const char *getOpcode() const override
    { return "!="; }
public:
    NE_Operator(NodePtr _left, NodePtr _right)
        : Binary_Operator(_left, _right)
    {}

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const 
    {
        int l = destReg;
        int r = destReg + 1;
        getLeft()->codeGen(dst, context, l);
        getRight()->codeGen(dst, context, r);
        dst << "xor $" << l << ", $" << r <<", $" << l << std::endl;
        dst << "sltu $"<< l <<", $0, $" << l << std::endl;
        dst << "andi $" << destReg << ", $" << l <<", 0x00ff" << std::endl;
    }
};

class Mul_Operator
    : public Binary_Operator
{
private:
protected:
    virtual const char *getOpcode() const override
    { return "*"; }
public:
    Mul_Operator(NodePtr _left, NodePtr _right)
        : Binary_Operator(_left, _right)
    {}

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const 
    {
        int l = destReg;
        int r = destReg + 1;
        getLeft()->codeGen(dst, context, l);
        getRight()->codeGen(dst, context, r);
        dst << "mult $" << l << ", $" << r << std::endl;
        dst << "mflo $" << destReg << std::endl;
    }
};

class Div_Operator
    : public Binary_Operator
{
private:
protected:
    virtual const char *getOpcode() const override
    { return "/"; }
public:
    Div_Operator(NodePtr _left, NodePtr _right)
        : Binary_Operator(_left, _right)
    {}

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const 
    {
        int l = destReg;
        int r = destReg + 1;
        getLeft()->codeGen(dst, context, l);
        getRight()->codeGen(dst, context, r);
        dst << "div $" << l << ", $" << r << std::endl;
        dst << "mflo $" << destReg << std::endl;
    }
};

class Mod_Operator
    : public Binary_Operator
{
private:
protected:
    virtual const char *getOpcode() const override
    { return "%"; }
public:
    Mod_Operator(NodePtr _left, NodePtr _right)
        : Binary_Operator(_left, _right)
    {}

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const 
    {
        int l = destReg;
        int r = destReg + 1;
        getLeft()->codeGen(dst, context, l);
        getRight()->codeGen(dst, context, r);
        dst << "div $" << l <<", $" << r << std::endl;
        dst << "mfhi $" << destReg << std::endl;
    }
};

#endif