#ifndef ast_constant_hpp
#define ast_constant_hpp

#include <iostream>
#include <string>

#include "ast_node.hpp"

class Constant
    : public Node
{
private:

public:
    virtual int getValue() const = 0;

    virtual void print(std::ostream &dst, std::string indent) const override
    {
        dst << indent << getType() << " [" << std::endl;
        dst << indent << indent_unit << "Value: " << getValue() << std::endl;
        dst << indent << "]" << std::endl;
    };
};

class Integer_Constant
    : public Constant
{
private:
    int value;
public:
    Integer_Constant(int _value)
        : value(_value)
    {}
    virtual int getValue() const override
    { return value; }     // convert integer value to string, string to c string

    virtual std::string getType() const override    // helps with printing
    { return "int"; }

    // pass Conte
    //store the constant into a destination memory address; 
    //offset address is the offset from the stack pointer which I use in the layer above
    void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override
    {
        dst<<"li "<< "$" << destReg << ", " << getValue() << std::endl;
    }

};

#endif