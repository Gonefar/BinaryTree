#include "head.h"
#include "func.c"

int main()
{
	int  choice;
	tree *pTree = create_tree();

	print_choice();
	scanf("%d", &choice);
	while(1)
		{
			process_choice(pTree, choice);
			scanf("%d", &choice);
		}
	
}

