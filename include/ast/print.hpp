#ifndef print_hpp
#define print_hpp

#include <iostream>
#include <string>
#include <unordered_map>

const std::string indent_unit = "    ";

template<typename K, typename V>
void print_map(std::ostream &dst, std::string indent, std::unordered_map<K, V> const &m)
{
    for (auto const &pair: m) {
        dst << indent << "{" << pair.first << ": " << pair.second << "}\n";
    }
}

static int makeNameUnq=0;

static std::string makeName(std::string base)
{
    return "_"+base+"_"+std::to_string(makeNameUnq++);
}

#endif