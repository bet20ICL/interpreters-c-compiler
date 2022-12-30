#ifndef ast_declarations_hpp
#define ast_declarations_hpp

#include <string>
#include <iostream>

#include "ast_node.hpp"

class Chain_Declaration
    : public Node
{
private:
    NodePtr specifiers;
    NodePtr init_declarator_list;
public:
    Chain_Declaration(NodePtr _specifiers, NodePtr _init_declarator_list)
        : specifiers(_specifiers)
        , init_declarator_list(_init_declarator_list)
    {}

    virtual ~Chain_Declaration()
    { 
        delete specifiers;
        delete init_declarator_list;
    }

    // virtual const char *getName() const override
    // {
    //     return Name.c_str();
    // }

    void print(std::ostream &dst, std::string indent) const override
    {
        dst << indent << "Chain_Declaration [" << std::endl;
        dst << indent << indent_unit << "Declaration_Specifiers:" << std::endl;
        specifiers->print(dst, indent + indent_unit);
        dst << indent << indent_unit << "Init_Declarator_List:" << std::endl;
        init_declarator_list->print(dst, indent + indent_unit);
        dst << indent << "]" << std::endl;
    }

    virtual ContextPtr genContext(ContextPtr root, std::string type) const override
    {
        std::string spec_type = specifiers->getType();
        return init_declarator_list->genContext(root, spec_type);
    }

    virtual void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override
    {
        // std::string declarator_type = init_declarator_list->DecFlag();
        // if(declarator_type == "Identifier"){
        // }
        init_declarator_list -> codeGen(dst, context, destReg);
    }

};

class Declaration_List
    : public Node
{
private:
    NodePtr body;
public:
    Declaration_List(NodePtr _body)
        : body(_body)
    {}

    virtual void print(std::ostream &dst, std::string indent) const override 
    {
        body->print(dst, indent);
    }

    virtual ContextPtr genContext(ContextPtr root, std::string type) const override
    {
        return body->genContext(root, type);
    }

    void codeGen(std::ostream &dst, ContextPtr context, int destReg) const override
    {
        codeGen(dst, context, destReg);
    } 
};

#endif