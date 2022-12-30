#ifndef ast_block_hpp
#define ast_block_hpp

#include <string>
#include <iostream>

#include "ast_node.hpp"

class Empty_Block
    : public Node
{
public:
    virtual void print(std::ostream &dst, std::string indent) const override 
    {
        dst << indent << "Empty_Block" << " [" << std::endl;
        dst << indent << "]" << std::endl;
    }
    void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override
    { }
};

// class Statement_Block
//     : public Node
// {
// private:
//     NodePtr tree;
//     NodePtr single;
// public:
//     Statement_Block(NodePtr _tree, NodePtr _single)
//         : tree(_tree)
//         , single(_single)
//     {}

//     virtual void print(std::ostream &dst, std::string indent) const override 
//     {
//         dst << indent << "Statement_Block" << " [" << std::endl;
//         dst << indent << indent_unit << "Expression:" << std::endl;
//         tree->print(dst, indent + indent_unit);
//         single->print(dst, indent + indent_unit);
//         dst << indent << "]" << std::endl;
//     }

//     void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override
//     {
//         tree->codeGen(dst, context, 8);
//         single->codeGen(dst, context, 8);
//     }
// };

// class Declaration_Block
//     : public Node
// {
// private:
//     NodePtr tree;
//     NodePtr single;
// public:
//     Declaration_Block(NodePtr _tree, NodePtr _single)
//         : tree(_tree)
//         , single(_single)
//     {}

//     virtual void print(std::ostream &dst, std::string indent) const override 
//     {
//         dst << indent << "Declaration_Block" << " [" << std::endl;
//         dst << indent << indent_unit << "Expression:" << std::endl;
//         tree->print(dst, indent + indent_unit);
//         single->print(dst, indent + indent_unit);
//         dst << indent << "]" << std::endl;
//     }

//     void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override
//     {
//         dst<<"Reached Statement Block"<<std::endl;
//         tree->codeGen(dst, context, 8);
//         single->codeGen(dst, context, 8);
//     }
// };

#endif