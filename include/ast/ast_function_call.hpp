#ifndef ast_function_call_hpp
#define ast_function_call_hpp

#include <iostream>
#include <string>
#include "ast_node.hpp"
#include "print.hpp"

class Function_Call
    : public Node
{
private:
    NodePtr identifier;
    NodePtr params;
public:
    Function_Call(NodePtr _identifier, NodePtr _params)
        : identifier(_identifier)
        , params(_params)
    {}

    virtual ~Function_Call()
    {
        delete identifier;
        delete params;
    }

    virtual void print(std::ostream &dst, std::string indent) const override 
    {
        dst << indent << "Function_Call" << " [" << "\n";
        dst << indent << indent_unit << "Identifier:" << "\n";
        identifier->print(dst, indent + indent_unit);
        dst << indent << indent_unit << "Parameters:" << "\n";
        if (params != NULL) {
            params->print(dst, indent + indent_unit);
        }
        dst << indent << "]" << "\n";
    }

    virtual ContextPtr genContext(ContextPtr root, std::string type) const override
    {
        return root;
    }

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override
    {
        // saving working registers to stack
        // $8 -> 16($fp)
        // $9 -> 20($fp)
        // $10 -> 24($fp)
        // $11 -> 28($fp)
        for (int i = 0; i <= 3; i++) {
            dst << "sw $" << i + 8 << ", " << i * 4 + 16 << "($fp)" << std::endl;
        }
        // load function parameters to registers 4 - 7
        if (params != NULL) {
            context->argCount = 0;
            params->codeGen(dst, context, destReg + 1);
            context->argCount = 0;
        }
        dst << "jal " << identifier->getName() << std::endl;
        dst << "nop" << std::endl;
        // recovering working registers from stack

        for (int i = 0; i <= 3; i++) {
            dst << "lw $" << i + 8 << ", " << i * 4 + 16 << "($fp)" << std::endl;
        }

        dst << "move $" << destReg << ", $2" << std::endl;
    }
};

#endif