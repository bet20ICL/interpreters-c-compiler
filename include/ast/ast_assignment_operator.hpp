#ifndef ast_assignment_operator_hpp
#define ast_assignment_operator_hpp

#include <iostream>
#include <string>

#include "ast_node.hpp"

class Assignment_Operator
    : public Node
{
private:

protected:
public:
    virtual ~Assignment_Operator()
    {}

    void print(std::ostream &dst, std::string indent) const override
    {
        dst << indent << getName() << std::endl;
    }
};

class Equals_Operator
    : public Assignment_Operator
{
private:
protected:
public:
    virtual std::string getName() const override
    { return "="; }
};

class Mul_A_Operator
    : public Assignment_Operator
{
private:
protected:
public:
    virtual std::string getName() const override
    { return "*="; }
};

class Div_A_Operator
    : public Assignment_Operator
{
private:
protected:
public:
    virtual std::string getName() const override
    { return "/="; }
};

class Mod_A_Operator
    : public Assignment_Operator
{
private:
protected:
public:
    virtual std::string getName() const override
    { return "%="; }
};

class Add_A_Operator
    : public Assignment_Operator
{
private:
protected:
public:
    virtual std::string getName() const override
    { return "+="; }
};

class Sub_A_Operator
    : public Assignment_Operator
{
private:
protected:
public:
    virtual std::string getName() const override
    { return "-="; }
};

class Left_A_Operator
    : public Assignment_Operator
{
private:
protected:
public:
    virtual std::string getName() const override
    { return "<<="; }
};

class Right_A_Operator
    : public Assignment_Operator
{
private:
protected:
public:
    virtual std::string getName() const override
    { return ">>="; }
};

class And_A_Operator
    : public Assignment_Operator
{
private:
protected:
public:
    virtual std::string getName() const override
    { return "&="; }
};

class Or_A_Operator
    : public Assignment_Operator
{
private:
protected:
public:
    virtual std::string getName() const override
    { return "|="; }
};

class Xor_A_Operator
    : public Assignment_Operator
{
private:
protected:
public:
    virtual std::string getName() const override
    { return "^="; }
};

#endif