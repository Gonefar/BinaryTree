void print_nblanks(int n)
{
	while(n -- > 0)
		{
			printf(" ");
		}
}

void print_data(node *pNode)
{
	int i = 0;

	if( (pNode->row == DEPTH) )
		{
			if(pNode->parent == NULL)
				{
					NULL;
				}
			else if( (reserve_prev_node_col == 1) && (pNode->parent->left == NULL) )
				{
					print_nblanks(PRINT_WIDTH * (pNode->col - 1) );
				}
			else
				{
					print_nblanks(PRINT_WIDTH * (pNode->col - reserve_prev_node_col - 1) );
				}
			
			printf("%6s", pNode->words);
		}
	else
		{
			if( (pNode->col - reserve_prev_node_col) >= 2 )
				{
					print_nblanks(PRINT_WIDTH * (pNode->col - reserve_prev_node_col - 1) * (DEPTH - pNode->row + 1) );
				}

			print_nblanks(PRINT_WIDTH / 2 * (int)(ldexp(1, DEPTH - pNode->row) - 1));
			printf("%6s", pNode->words);
			print_nblanks(PRINT_WIDTH / 2 * (int)(ldexp(1, DEPTH - pNode->row) - 1));
		}

	reserve_prev_node_col = pNode->col;
	
}

void in_order(node *pNode)
{
	if(pNode != NULL)
		{
			in_order(pNode->left);
			//printf("%10s,row:%d\n", pNode->words, pNode->row);
			
			if(pNode->row == mylow)
				{
					//printf("%10s||Row:%d||Col:%d", pNode->words, pNode->row, pNode->col);
					print_data(pNode);

				}

			
			in_order(pNode->right);
		}
}

void in_order2(node *pNode)
{
	if(pNode != NULL)
		{
			if(pNode->parent == NULL)//refresh the nodes' col and row
				{
					pNode->row = 1;
					pNode->col = 1;
				}
			else
				{
					if(pNode == pNode->parent->left)
						{
							pNode->row = pNode->parent->row + 1;
							pNode->col = 2 * pNode->parent->col - 1;
						}
					else
						{
							pNode->row = pNode->parent->row + 1;
							pNode->col = 2 * pNode->parent->col;
						}
				}


			in_order2(pNode->left);
			//printf("%10s, row:%d, col:%d\n", pNode->words, pNode->row, pNode->col);
			if(pNode->row > DEPTH)
				{
					DEPTH = pNode->row;	
				}
			
			in_order2(pNode->right);
		}

}

void traverse2(tree *pTree)
{
	if(pTree->root != NULL)
		{
			in_order2(pTree->root);
		}
}


void traverse(tree *pTree)
{
	if(pTree->root != NULL)
		{
			in_order(pTree->root);
		}
}

int get_tree_depth(tree *pTree)
{
	DEPTH = 0;
	traverse2(pTree);
}

void print_tree(tree *pTree)
{
	get_tree_depth(pTree);
	int temp = DEPTH;
	//printf("node num:%d\n", pTree->nodeNum);
	while(temp-- > 0)
		{
			printf("Row %d", mylow);
			traverse(pTree);
			printf("\n");
			mylow++;
			reserve_prev_node_col = 1;
		}

	mylow = 1;
	//reserve_prev_node_col = 1;
}

node *search_node_by_content(tree *pTree, char *words)
{
	node *mid_val = NULL;
	int cmp_result;
	int row = 1, col = 1;
	
	mid_val = pTree->root;

	if(mid_val->words == NULL)
		{
			printf("The tree is NULL\n");
			return NULL;
		}
	
	//while( (mid_val->left != NULL) || (mid_val->right != NULL) )
	  while(mid_val != NULL)
		{
			cmp_result = strcmp(mid_val->words, words);
			mid_val->row = row;
			
			mid_val->col = col;
			
			if(cmp_result < 0)
				{
					if(mid_val->right != NULL)
						{
							col = 2 * mid_val->col;
							mid_val = mid_val->right;
							row++;
						}
					else
						{
							//mid_val->row++;
							//printf("add node in row %d\n", mid_val->row);
							return mid_val;
						}
				}
			else if(cmp_result > 0)
				{
					if(mid_val->left != NULL)
						{
							col = (2 * mid_val->col - 1);
							mid_val = mid_val->left;
							row++;
						}
					else
						{
							//mid_val->row++;
							//printf("add node in row %d\n", mid_val->row);
							return mid_val;
						}

				}
			else
				{
					printf("Find it!\n");
					return mid_val;
				}
		}

	printf("No this node in the tree\n");
	printf("return the last search node\n");
	return mid_val;
	
}

void *Malloc(int size)
{
	void *temp = malloc(size);
	if(temp == NULL )
		{
			printf("allocate address error\n");
			exit(-1);
		}
	else
		{
			return temp;
		}

}

void print_choice(void)
{
	printf("Input your choice:\n");
	printf("1: Add a node\n");
	printf("2: Delete a node\n");
	printf("3: Find a node\n");
	printf("4: Show the tree\n");
	printf("5: Quit\n");
}

tree *create_tree(void)
{
	tree *temp = (tree *)Malloc(sizeof(tree));
	temp->nodeNum = 0;
	temp->root    = NULL;
	temp->depth   = 0;

	return temp;
}

node *create_node(char *words)
{
	node *new_node =(node *) Malloc(sizeof(node));

	new_node->left     = NULL;
	new_node->right    = NULL;
	new_node->parent   = NULL;
	new_node->row      = -1;
	new_node->col      = -1;
	new_node->words    = words;
	new_node->wordsNum = 1;

	return new_node;
}

void bind_node(node * node_in_tree, node* obj)
{
	int cmp_result;
	cmp_result = strcmp(node_in_tree->words, obj->words);
			
	if(cmp_result < 0)
		{
			node_in_tree->right = obj;
			obj->parent         = node_in_tree;
			//obj->row  = node_in_tree->row + 1;
			//obj->col  = 2 * node_in_tree->col;
		}
	else if(cmp_result > 0)
		{
			node_in_tree->left = obj;
			obj->parent        = node_in_tree;
			//obj->row  = node_in_tree->row + 1;
			//obj->col  = (2 * node_in_tree->col - 1);
		}
	else
		{
			node_in_tree->wordsNum++;
		}	
}

int insert_node(tree *pTree, char *words)
{
	node *search_result = NULL;
	node *new_node = NULL;
	new_node = (node *)create_node(words);
	
	if(pTree->root == NULL)
		{
			pTree->root = new_node;
			pTree->nodeNum = 1;
			pTree->depth   = 1;
			return 1;
		}
	
	search_result = search_node_by_content(pTree, words);

	if(!strcmp(search_result->words, words))
		{
			search_result->wordsNum++;
		}
	else
		{
	
			if(search_result != NULL && search_result->left == NULL \
				&& search_result->right == NULL)
				{
					bind_node(search_result, new_node);
					pTree->nodeNum++;
				}
			else if((search_result != NULL) && (search_result->left != NULL))

					{
						search_result->right = new_node;
						new_node->parent = search_result;
						//new_node->row = search_result->row + 1;
						//new_node->col = 2 * search_result->col;
						pTree->nodeNum++;
					}
			else if((search_result != NULL) && (search_result->right != NULL))
				{
						search_result->left = new_node;
						new_node->parent = search_result;
						//new_node->row = search_result->row + 1;
						//new_node->col = (2 * search_result->col - 1);
						pTree->nodeNum++;
				}
		}
		
}

node *find_leftTree_keyNode(node *obj)
{
	node *temp = NULL;

	temp = obj;
	
	if(temp == NULL)
		{
			printf("left tree is NULL\n");
			return NULL;
		}
	
	while(temp->right != NULL)
		{
			temp = temp->right;
		}
	printf("the most right node in the left tree:%s\n", temp->words);
	return temp;
	
}

node *find_rightTree_keyNode(node *obj)
{
	node *temp = NULL;

	temp = obj;
	
	if(temp == NULL)
		{
			printf("left tree is NULL\n");
			return NULL;
		}
	
	while(temp->left != NULL)
		{
			temp = temp->left;
		}
	printf("the most left node in the right tree:%s\n", temp->words);
	return temp;
	
}


void delete_leaf_node(tree *pTree, node *obj)
{
	int cmp_result;
	cmp_result = strcmp(obj->parent->words, obj->words);
	if(cmp_result > 0)
		{
			obj->parent->left = NULL;
			pTree->nodeNum--;
			free(obj);
		}
	else if(cmp_result < 0)
		{
			obj->parent->right = NULL;
			pTree->nodeNum--;
			free(obj);
		}
}

void relink_tree(tree *pTree, node *obj)
{
	node *temp = NULL;
	int cmp_res;
	
	if(obj->left == NULL)
		{
			obj->parent->right = obj->right;
			obj->right->parent = obj->parent;
			pTree->nodeNum--;
			free(obj);
		}
	else if(obj->right == NULL)
		{
			obj->parent->left = obj->left;
			obj->left->parent = obj->parent;
			pTree->nodeNum--;
			free(obj);
		}
	else
		{
			cmp_res = strcmp(obj->parent->words, obj->words);
			
			if(cmp_res > 0)
				{					
					temp = find_leftTree_keyNode(obj->left);
					obj->parent->left = obj->left;
					obj->left->parent = obj->parent;
					//obj->left->row--;
					//obj->left->col = obj->col;
					
					temp->right = obj->right;
					obj->right->parent  = temp;
				}
			else
				{
					temp = find_rightTree_keyNode(obj->right);
					obj->parent->right = obj->right;
					obj->right->parent = obj->parent;
					//obj->right->row--;
					//obj->right->col = obj->col;//other nodes also need refresh row & col

					temp->left = obj->left;
					obj->left->parent = temp;
					
				}

			free(obj);
			pTree->nodeNum--;
			
		}
}

int destroy_node(tree *pTree, char *words)
{
	node *search_result = NULL, *temp = NULL;
	search_result = (node *)search_node_by_content(pTree, words);

	if(search_result != NULL && search_result->left == NULL \
	&& search_result->right == NULL)
	{
		delete_leaf_node(pTree, search_result);
		
	}
	else if(search_result != NULL && (search_result->left != NULL \
		|| search_result->right != NULL))
		{
			if(search_result->wordsNum == 1)
				{
					relink_tree(pTree, search_result);					
				}
			else
				{
					search_result->wordsNum--;
				}

		}
	else
		{
			printf("No this data in the tree\n");
			return -1;
		}
	
	traverse2(pTree);
	return 0;
}

int process_choice(tree *pTree, int choice)
{
	char *words = (char *)Malloc(64*sizeof(char));
	node *temp = NULL;
	char ch = 'A';

	switch(choice)
		{
			case ADD_NODE:				
				printf("Input the adding node content:\n");
				while(scanf("%s", words) > 0)
					{
						
						//scanf("%s", words);
						ch = getchar();
						insert_node(pTree, words);
						if(ch == '\n')
							{
								break;
							}
						words = (char *)Malloc(64*sizeof(char));
					}
				break;
				
			case DELETE_NODE:
				printf("Input the destroy node content\n");
				while(scanf("%s", words) > 0)
					{
					
						//scanf("%s", words);
						destroy_node(pTree, words);
						ch = getchar();
						if(ch == '\n')
							{
								break;
							}
						words = (char *)Malloc(64*sizeof(char));
					}
				break;
					
			case FIND_NODE:
				printf("Input the search node content\n");
				scanf("%s", words);
				temp = search_node_by_content( pTree, words);
				break;
				
			case SHOW_TREE:
				print_tree(pTree);
				break;
				
			case QUIT:
				print_tree(pTree);
				printf("Nodes num:%d, row:%d\n", pTree->nodeNum, DEPTH);
				exit(1);
				break;
		}
			
	print_choice();	
	return 1;
}

