#ifndef ast_function_parameter_hpp
#define ast_function_parameter_hpp

#include <iostream>
#include <string>
#include <unordered_map>
#include "ast_node.hpp"

class Function_Parameter
    : public Node
{
private:
    NodePtr specifiers;
    NodePtr declarator;
public:
    Function_Parameter(NodePtr _specifiers, NodePtr _declarator)
        : specifiers(_specifiers)
        , declarator(_declarator)
    {}

    virtual ~Function_Parameter()
    {
        delete specifiers;
        delete declarator;
    }

    // virtual const char *getName() const override
    // {
    //     return Name.c_str();
    // }

    void print(std::ostream &dst, std::string indent) const override
    {
        dst << indent << "Function_Parameter " << "[" << std::endl;
        dst << indent << indent_unit << "Specifiers: " << std::endl;
        specifiers->print(dst, indent + indent_unit);
        dst << indent << indent_unit << "Declarator: " << std::endl;
        declarator->print(dst, indent + indent_unit);
        dst << indent << "]" << std::endl;
    }

    virtual ContextPtr genContext(ContextPtr root, std::string type) const 
    {
        std::string spec_type = specifiers->getType();
        return declarator->genContext(root, spec_type);
    }
};

#endif