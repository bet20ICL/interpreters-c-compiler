#ifndef ast_translation_unit_hpp
#define ast_translation_unit_hpp

#include <iostream>
#include <string>

#include "ast_node.hpp"

class Global_Scope
    : public Node
{
private:
    NodePtr content;
public:
    Global_Scope(NodePtr _content)
        : content(_content)
    {}
    
    virtual void print(std::ostream &dst, std::string indent) const override
    {
        dst << indent << "Global Scope [" << std::endl;
        content->print(dst, indent + indent_unit);
        dst << indent << "]" << std::endl;
    }

    virtual ContextPtr genContext(ContextPtr root, std::string type) const override
    {
        return content->genContext(root, type);
    }

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override
    {
        content->codeGen(dst, context, destReg);
    }

};

#endif