#ifndef ast_function_definition
#define ast_function_definition

#include <iostream>
#include <string>
#include <unordered_map>
#include "ast_node.hpp"

class Standard_Function
    : public Node
{
private:
    NodePtr declaration_specifier;
    NodePtr declarator;
    NodePtr compound_statement;
    int frame_size;
public:
    Standard_Function(NodePtr _declaration_specifier, NodePtr _declarator, NodePtr _compound_statement)
        : declaration_specifier(_declaration_specifier), declarator(_declarator), compound_statement(_compound_statement)
    {}

    virtual ~Standard_Function()
    {
        delete declaration_specifier;
        delete declarator;
        delete compound_statement;
    }

    virtual void print(std::ostream &dst, std::string indent) const override 
    {
        dst << indent << "Standard_Function_Def" << " [" << "\n";
        dst << indent << indent_unit << "Declaration_Specifier:" << "\n";
        declaration_specifier->print(dst, indent + indent_unit);
        dst << indent << indent_unit << "Declarator:" << "\n";
        declarator->print(dst, indent + indent_unit);
        dst << indent << indent_unit << "Compound_Statement:" << "\n";
        compound_statement->print(dst, indent + indent_unit);
        dst << indent << "]" << "\n";
    }

    virtual ContextPtr genContext(ContextPtr root, std::string type) const override
    {
        ContextPtr c_dec;
        c_dec = declarator->genContext(root, type);
        ContextPtr c_body;
        c_body = new Context();
        c_body->parent = c_dec;
        c_body = compound_statement->genContext(c_body, type);
        c_dec->children.push_back(c_body);
        return c_dec;
    }

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override
    {
        /* ------------------------ */
        /* start of function */
        /* ------------------------ */

        // function name etc.
        int stack_size = context->stack_size + (context->children[0])->stack_size + 12 + 32;
        declarator->codeGen(dst, context, 8); 
        
        context->param_offset = stack_size;
        // stack and frame pointer stuff
        std::string _push_label = makeName("PUSH");
        dst << _push_label << ":" << std::endl;
        dst << "addiu $sp, $sp, -"<< stack_size << std::endl;
        dst << "sw $ra, "<< stack_size - 4 << "($sp)" << std::endl;
        dst << "nop" << std::endl;
        dst << "sw $fp, "<< stack_size - 8 << "($sp)" << std::endl;
        dst << "nop" << std::endl;

        for (int i = 0; i < context->stack_size / 4; i++)
        {
            dst << "sw " << "$" << i + 4 << ", " << stack_size + i * 4 << "($sp)" << std::endl;
            dst << "nop" << std::endl;
        }

        // store saved registers to stack
        /*
        dst << "sw $s0, 4($sp)" << std::endl;
        dst << "nop" << std::endl;
        dst << "sw $s1, 8($sp)" << std::endl;
        dst << "nop" << std::endl;
        dst << "sw $s2, 12($sp)" << std::endl;
        dst << "nop" << std::endl;
        dst << "sw $s3, 16($sp)" << std::endl;
        dst << "nop" << std::endl;
        dst << "sw $s4, 20($sp)" << std::endl;
        dst << "nop" << std::endl;
        dst << "sw $s5, 24($sp)" << std::endl;
        dst << "nop" << std::endl;
        dst << "sw $s6, 28($sp)" << std::endl;
        dst << "nop" << std::endl;
        dst << "sw $s7, 32($sp)" << std::endl;
        dst << "nop" << std::endl;
        */
        dst << "move $fp, $sp" << std::endl;

        // dst << "sw $4, " << stack_size + 0 << "($fp)" << std::endl;
        // dst << "sw $5, " << stack_size + 4 << "($fp)" << std::endl;
        // dst << "sw $6, " << stack_size + 8 << "($fp)" << std::endl;
        // dst << "sw $7, " << stack_size + 12 << "($fp)" << std::endl;

        std::string _return_label = makeName("POP");
        context->return_label = _return_label;
        /* ------------------------ */
        /* function execution */
        /* ------------------------ */

        compound_statement->codeGen(dst, context->children[0], 8);

        /* ------------------------ */
        /* end of function */
        /* ------------------------ */

        // move saved values back into registers
        dst << _return_label << ":" << std::endl; // create new pops
        /*
        dst << "lw $s0, 4($sp)" << std::endl;
        dst << "nop" << std::endl;
        dst << "lw $s1, 8($sp)" << std::endl;
        dst << "nop" << std::endl;
        dst << "lw $s2, 12($sp)" << std::endl;
        dst << "nop" << std::endl;
        dst << "lw $s3, 16($sp)" << std::endl;
        dst << "nop" << std::endl;
        dst << "lw $s4, 20($sp)" << std::endl;
        dst << "nop" << std::endl;
        dst << "lw $s5, 24($sp)" << std::endl;
        dst << "nop" << std::endl;
        dst << "lw $s6, 28($sp)" << std::endl;
        dst << "nop" << std::endl;
        dst << "lw $s7, 32($sp)" << std::endl;
        dst << "nop" << std::endl;
        */

        // stack and frame pointer stuff
        dst << "lw $ra, "<< stack_size - 4 <<"($sp)" << std::endl;
        dst << "nop" << std::endl;
        dst << "lw $fp, "<< stack_size - 8 <<"($sp)" << std::endl;
        dst << "nop" << std::endl;
        dst << "move $sp, $fp" << std::endl;
        dst << "jr $ra" << std::endl;
        dst << "nop" << std::endl;
    }
};

#endif