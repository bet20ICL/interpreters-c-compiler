%code requires{
	#include <stdio.h>
    #include "ast.hpp"

	extern const Node* global_scope;

    int yylex(void);
    void yyerror(const char*);
}

%union{
	const Node* node;
	int number;
    std::string* string;
}

%token <number> INT_CONST
%token <string> IDENTIFIER CONSTANT SIZEOF
%token <string> STRING_LITERAL
%token <string> PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token <string> AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token <string> SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token <string> XOR_ASSIGN OR_ASSIGN TYPE_NAME

%token <string> TYPEDEF EXTERN STATIC AUTO REGISTER
%token <string> CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token <string> STRUCT UNION ENUM ELLIPSIS

%token <string> CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%type <node> assignment_operator
%type <node> init_declarator_list init_declarator initializer declaration declaration_list
%type <node> translation_unit direct_declarator primary_expression external_declaration function_definition type_specifier
%type <node> parameter_declaration parameter_list parameter_type_list
%type <node> jump_statement declarator declaration_specifiers compound_statement statement statement_list expression assignment_expression
%type <node> conditional_expression logical_or_expression logical_and_expression postfix_expression unary_expression cast_expression multiplicative_expression
%type <node> additive_expression shift_expression relational_expression equality_expression and_expression exclusive_or_expression inclusive_or_expression
%type <node> expression_statement selection_statement iteration_statement
%type <node> constant_expression
%type <node> argument_expression_list
%type <node> specifier_qualifier_list type_name
%type <node> global_scope

%start global_scope

%%

primary_expression
            : INT_CONST { $$ = new Integer_Constant($1); }
            | IDENTIFIER { $$ = new Identifier(*$1); }
            | '(' expression ')' { $$ = $2; }
            ;

postfix_expression
            : primary_expression { $$ = $1; }
            | postfix_expression '[' expression ']' { $$ = new Array_Identifier($1, $3); }
            | postfix_expression INC_OP { $$ = new Post_Increment($1); }
            | postfix_expression DEC_OP { $$ = new Post_Decrement($1); }
            | postfix_expression '(' ')' { $$ = new Function_Call($1, NULL); }
            | postfix_expression '(' argument_expression_list ')' { $$ = new Function_Call($1, $3); }
            ;

argument_expression_list
            : assignment_expression { $$ = new Argument($1); }
            | argument_expression_list ',' assignment_expression { $$ = new Node_List($1, new Argument($3)); }
            ;

unary_expression
            : postfix_expression { $$ = $1; }
            | '+' cast_expression { $$ = $2; }
            | '-' cast_expression { $$ = new Neg_Operator($2); }
            | '!' cast_expression { $$ = new lNOT_Operator($2); }
            | '~' cast_expression { $$ = new bNOT_Operator($2); }
            | INC_OP cast_expression { $$ = new Pre_Increment($2); }
            | DEC_OP cast_expression { $$ = new Pre_Decrement($2); }
            | SIZEOF unary_expression { $$ = new Size_Of_Operator($2); }
	        | SIZEOF '(' type_name ')' { $$ = new Size_Of_Operator($3); }
            ;

cast_expression
            : unary_expression { $$ = $1; }
            ;

multiplicative_expression
            : cast_expression { $$ = $1; }
            | multiplicative_expression '*' cast_expression { $$ = new Mul_Operator($1, $3); }
            | multiplicative_expression '/' cast_expression { $$ = new Div_Operator($1, $3); }
            | multiplicative_expression '%' cast_expression { $$ = new Mod_Operator($1, $3); }
            ;

additive_expression
            : multiplicative_expression { $$ = $1; }
            | additive_expression '+' multiplicative_expression { $$ = new Add_Operator($1, $3); }
	        | additive_expression '-' multiplicative_expression { $$ = new Sub_Operator($1, $3); }
            ;

shift_expression
            : additive_expression { $$ = $1; }
            | shift_expression LEFT_OP additive_expression { $$ = new SLL_Operator($1, $3); }
            | shift_expression RIGHT_OP additive_expression { $$ = new SRA_Operator($1, $3); }
            ;

relational_expression
            : shift_expression { $$ = $1; }
            | relational_expression '<' shift_expression { $$ = new LT_Operator($1, $3); }
            | relational_expression '>' shift_expression { $$ = new GT_Operator($1, $3); }
            | relational_expression LE_OP shift_expression { $$ = new LET_Operator($1, $3); }
            | relational_expression GE_OP shift_expression { $$ = new GET_Operator($1, $3); }
            ;

equality_expression
            : relational_expression { $$ = $1; }
            | equality_expression EQ_OP relational_expression { $$ = new EQ_Operator($1, $3); }
	        | equality_expression NE_OP relational_expression { $$ = new NE_Operator($1, $3); }
            ;

and_expression
            : equality_expression { $$ = $1; }
            | and_expression '&' equality_expression { $$ = new bAND_Operator($1, $3); }
            ;

exclusive_or_expression
            : and_expression { $$ = $1; }
            | exclusive_or_expression '^' and_expression { $$ = new bXOR_Operator($1, $3); }
            ;

inclusive_or_expression
            : exclusive_or_expression { $$ = $1; }
            | inclusive_or_expression '|' exclusive_or_expression { $$ = new bOR_Operator($1, $3); }
            ;

logical_and_expression
            : inclusive_or_expression { $$ = $1; }
            | logical_and_expression AND_OP inclusive_or_expression { $$ = new lAND_Operator($1, $3); }
            ;

logical_or_expression
            : logical_and_expression { $$ = $1; }
            | logical_or_expression OR_OP logical_and_expression { $$ = new lOR_Operator($1, $3); }
            ;
        
conditional_expression
            : logical_or_expression { $$ = $1; }
            | logical_or_expression '?' expression ':' conditional_expression { $$ = new Ternary_Operator($1, $3, $5); }
            ;

assignment_expression
            : conditional_expression { $$ = $1; }
            | unary_expression assignment_operator assignment_expression { $$ = new Assignment_Expression($1, $2, $3); };
            ;

assignment_operator
            : '=' { $$ = new Equals_Operator(); } 
            | MUL_ASSIGN { $$ = new Mul_A_Operator(); } 
            | DIV_ASSIGN { $$ = new Div_A_Operator(); } 
            | MOD_ASSIGN { $$ = new Mod_A_Operator(); } 
            | ADD_ASSIGN { $$ = new Add_A_Operator(); } 
            | SUB_ASSIGN { $$ = new Sub_A_Operator(); } 
            | LEFT_ASSIGN { $$ = new Left_A_Operator(); } 
            | RIGHT_ASSIGN { $$ = new Right_A_Operator(); } 
            | AND_ASSIGN { $$ = new And_A_Operator(); } 
            | XOR_ASSIGN { $$ = new Xor_A_Operator(); } 
            | OR_ASSIGN { $$ = new Or_A_Operator(); } 
            ;

expression
            : assignment_expression { $$ = $1; }
            | expression ',' assignment_expression { $$ = new Node_List($1, $3); }
            ; 

constant_expression
            : conditional_expression { $$ = $1; }
            ;

statement
            : jump_statement { $$ = $1; }
            | compound_statement { $$ = $1; }
            | expression_statement { $$ = $1; }
            | selection_statement { $$ = $1; }
            | iteration_statement { $$ = $1; }
            ;

statement_list
            : statement { $$ = $1; }
            | statement_list statement { $$ = new Node_List($1, $2); }
            ;

expression_statement
            : ';' { $$ = new Empty_Expression(); }
            | expression ';' { $$ = $1; }
            ;

compound_statement
            : '{' statement_list '}' { $$ = $2; } 
            | '{' declaration_list '}' { $$ = $2; } 
            | '{' declaration_list statement_list '}' { $$ = new Node_List($2, $3);  }
            | '{' '}' { $$ = new Empty_Block(); }
            ;

declaration_list
            : declaration { $$ = $1; }
            | declaration_list declaration { $$ = new Node_List($1, $2); }
            ;

selection_statement
            : IF '(' expression ')' statement {$$ = new If_Statement($3,$5);}
            | IF '(' expression ')' statement ELSE statement {$$ = new If_Else_Statement($3,$5,$7);}
            | SWITCH '(' expression ')' statement { $$ = new Switch_Statement($3,$5); }
            ;

iteration_statement
            : WHILE '(' expression ')' statement { $$ = new While_Statement($3,$5);}
            | FOR '(' expression_statement expression_statement ')' statement { $$ = new For_Loop_Empty($3, $4, $6);}
            | FOR '(' expression_statement expression_statement expression ')' statement { $$ = new For_Loop($3,$4,$5,$7); }
            ;

jump_statement
            : RETURN expression ';' { $$ = new Return($2); }
            /* | CONTINUE ';'
            | BREAK ';'
            | RETURN ';' { $$ = new ast_return(); }
            | GOTO IDENTIFIER ';' */
            ;

declarator
            : direct_declarator { $$ = $1; }
            ;

direct_declarator
            : IDENTIFIER { $$ = new Identifier(*$1); }
            | direct_declarator '[' constant_expression ']' { $$ = new Array_Declarator($1, $3); }
            | direct_declarator '(' ')' { $$ = new Function_Declarator_Empty($1); }
            | direct_declarator '(' parameter_type_list ')' { $$ = new Function_Declarator_Inputs($1, $3); }
            ;

parameter_type_list
            : parameter_list { $$ = $1; }
            ;

parameter_list
            : parameter_declaration { $$ = $1; }
            | parameter_list ',' parameter_declaration { $$ = new Node_List($1, $3); }
            ;

parameter_declaration
            : declaration_specifiers declarator { $$ = new Function_Parameter($1, $2); }
            ;

declaration
            : declaration_specifiers init_declarator_list ';' { $$ = new Chain_Declaration($1, $2); }
            /* | declaration_specifiers ';' { ; } */
            ;

declaration_specifiers
            : type_specifier { $$ = $1; }
            ;

init_declarator_list
            : init_declarator { $$ = $1; }
            | init_declarator_list ',' init_declarator { $$ = new Node_List($1, $3); }
            ;

init_declarator
            : declarator { $$ = $1; }
            | declarator '=' initializer { NodePtr equals = new Equals_Operator(); $$ = new Assignment_Expression($1, equals, $3); }
            ;

initializer
            : assignment_expression { $$ = $1; };
            /* | '{' initializer_list '}'
            | '{' initializer_list ',' '}' */
            ;

type_specifier
            : INT { $$ = new Integer_Type(); }
            | UNSIGNED { $$ = new Integer_Type(); }
            | CHAR { $$ = new Char_Type(); }
            | FLOAT { $$ = new Float_Type(); }
            | DOUBLE { $$ = new Double_Type(); }
            ;

specifier_qualifier_list
            : type_specifier { $$ = $1; }
            ;

type_name
            : specifier_qualifier_list { $$ = $1; }
            ;

global_scope
            : translation_unit { global_scope = new Global_Scope($1); }

translation_unit
            : external_declaration { $$ = $1; }
            | translation_unit external_declaration { $$ = new Node_List($1, $2); } 
            ;

external_declaration
            : function_definition { $$ = $1; }
            ;

function_definition
            : declaration_specifiers declarator compound_statement { $$ = new Standard_Function($1, $2, $3);}
            /* | declarator compound_statement {;} */
            ;

%%

const Node *global_scope;

const Node *parseAST()
{
    global_scope = 0;
    yyparse();
    return global_scope;
}