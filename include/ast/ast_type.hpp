#ifndef ast_type_hpp
#define ast_type_hpp

#include <iostream>
#include <string>
#include "ast_node.hpp"

class Type
    : public Node
{
private:

public:
    virtual void print(std::ostream &dst, std::string indent) const override
    {
        dst << indent << getType() << std::endl;
    };
};

class Integer_Type 
    : public Type 
{
private:
public:
    virtual std::string getType() const override    // helps with printing
    { return "int"; }
    virtual std::string getType(ContextPtr context) const override    // helps with printing
    { return "int"; }
};

class Char_Type 
    : public Type 
{
private:
public:
    virtual std::string getType() const override    // helps with printing
    { return "char"; }
    virtual std::string getType(ContextPtr context) const override    // helps with printing
    { return "char"; }
};

class Float_Type 
    : public Type 
{
private:
public:
    virtual std::string getType() const override    // helps with printing
    { return "float"; }
    virtual std::string getType(ContextPtr context) const override    // helps with printing
    { return "float"; }
};

class Double_Type 
    : public Type 
{
private:
public:
    virtual std::string getType() const override    // helps with printing
    { return "double"; }
    virtual std::string getType(ContextPtr context) const override    // helps with printing
    { return "double"; }
};

#endif