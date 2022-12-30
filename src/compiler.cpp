#include <iostream>
#include <cstdlib>
#include <fstream>

#include "ast.hpp"

void deallocate_context(ContextPtr context)
{
    for (unsigned i = 0; i < context->children.size(); i++)
    {
        deallocate_context(context->children[i]);
    }
    delete context;
}

int main()
{
	const Node *ast = parseAST();

	// Print AST - mostly for debugging
	ast->print(std::cerr, "");
	std::cerr << std::endl;
	ContextPtr context = new Context();
	context = ast->genContext(context, "");
	context->printBindings(std::cerr, "");
	context->printTypes(std::cerr, "");
	// Generate assembly
	ast->codeGen(std::cout,context,31);
	deallocate_context(context);
}