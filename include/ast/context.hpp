#ifndef context_hpp
#define context_hpp

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "print.hpp"

struct Context;
typedef Context *ContextPtr;

struct Context 
{
    int offset_address;
    int dest_address1;
    std::string return_label;

    const char * address(){
        return (std::to_string(offset_address) + "($sp)").c_str();
    }

    std::vector<ContextPtr> children;
    ContextPtr parent = NULL;
    std::unordered_map<std::string, int> bindings;
    int stack_size = 0;
    int param_offset = 0;
    int frame_offset = 32; // 8 registers below stack, 4 for arguments, 4 for saved registers

    void printBindings(std::ostream &dst, std::string indent)
    {
        dst << indent << "Bindings" << std::endl;
        dst << indent << "Stack_Size " << stack_size << std::endl;
        print_map(dst, indent, bindings);
        if (children.size()) {
            dst << indent << "Children Context" << std::endl;
            for (unsigned i = 0; i < children.size(); i++) {
                children[i]->printBindings(dst, indent + indent_unit);
            }
        }
    }

    int searchBindings(std::string id)
    {
        if (parent == NULL) {
            std::cerr <<"no parent" << std::endl;
            return bindings.at(id) + param_offset;
        }
        if (bindings.find(id) != bindings.end()) {
            return bindings.at(id) + frame_offset;
        } else if (parent != NULL) {
            return parent->searchBindings(id);
        } else {
            return -1;
        }
    }

    std::unordered_map<std::string, std::string> types;

    void printTypes(std::ostream &dst, std::string indent)
    {
        dst << indent << "Types" << std::endl;
        print_map(dst, indent, types);
        if (children.size()) {
            dst << indent << "Children Types" << std::endl;
            for (unsigned i = 0; i < children.size(); i++) {
                children[i]->printTypes(dst, indent + indent_unit);
            }
        }
    }

    std::string searchTypes(std::string id)
    {
        if (parent == NULL) {
            std::cerr <<"no parent (type)" << std::endl;
            return types.at(id);
        } 
        if (types.find(id) != types.end()) {
            return types.at(id);
        } else if (parent != NULL) {
            return parent->searchTypes(id);
        } else {
            return "int";
        }
    }

    int regPointer = 8;

    int getNewReg() {
        regPointer++;
        return regPointer - 1;
    }

    int argCount = 0;
};

#endif