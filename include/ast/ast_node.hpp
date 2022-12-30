#ifndef ast_node_hpp
#define ast_node_hpp

#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include "context.hpp"
#include "print.hpp"

class Node;
typedef const Node *NodePtr;

class Node{
public:
    // Destructor
    virtual ~Node(){};

    virtual void print(
        std::ostream &dst,
        std::string indent
    ) const = 0;

    virtual std::string getName() const { return ""; }

    virtual std::string getType() const { return "int"; }

    virtual std::string getType(ContextPtr context) const { return "int"; }

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const {}

    virtual ContextPtr genContext(ContextPtr root, std::string type) const 
    {
        return root;
    }

    virtual int getValue() const 
    {
        return 0;
    }

    virtual int getAddress(ContextPtr context) const
    {
        return 0;
    }

    virtual bool isArray() const
    {
        return 0;
    }

    virtual NodePtr getIndex() const
    {
        return NULL;
    }
};

class Node_List
    : public Node
{
private:
    NodePtr left;
    NodePtr right;
public:
    Node_List(NodePtr _left, NodePtr _right)
        : left(_left)
        , right(_right)
    {}

    virtual ~Node_List()
    { 
        delete left;
        delete right;
    }

    void print(std::ostream &dst, std::string indent) const override
    {
        left->print(dst, indent);
        right->print(dst, indent);
    }

    virtual ContextPtr genContext(ContextPtr root, std::string type) const override
    {
        ContextPtr tmp;
        tmp = left->genContext(root, type);
        tmp = right->genContext(root, type);
        return tmp;
    }

    void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override
    {
        left->codeGen(dst, context, destReg);
        right->codeGen(dst, context, destReg);
    }
};

#endif