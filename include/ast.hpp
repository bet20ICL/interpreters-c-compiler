#ifndef ast_hpp
#define ast_hpp

#include "ast/ast_argument.hpp"
#include "ast/ast_array.hpp"
#include "ast/ast_assignment_expression.hpp"
#include "ast/ast_assignment_operator.hpp"
#include "ast/ast_binary_operator.hpp"
#include "ast/ast_block.hpp"
#include "ast/ast_constant.hpp"
#include "ast/ast_declarations.hpp"
#include "ast/ast_direct_declarator.hpp"
#include "ast/ast_expression.hpp"
#include "ast/ast_function_call.hpp"
#include "ast/ast_function_definition.hpp"
#include "ast/ast_function_parameter.hpp"
#include "ast/ast_identifier.hpp"
#include "ast/ast_unary_operator.hpp"
#include "ast/ast_node.hpp"
#include "ast/ast_return.hpp"
#include "ast/ast_ternary.hpp"
#include "ast/ast_translation_unit.hpp"
#include "ast/ast_type.hpp"
#include "ast/context.hpp"
#include "ast/ast_selection_statement.hpp"
#include "ast/ast_iteration_statement.hpp"

extern const Node* parseAST();

#endif

//ast was highly inspired by lab2 and lab3
