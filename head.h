#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define ADD_NODE     1
#define DELETE_NODE  2
#define FIND_NODE    3
#define SHOW_TREE    4
#define QUIT         5
#define PRINT_WIDTH  6

//char *element[10][30];
int mylow = 1;
int DEPTH = 0;
int reserve_prev_node_col = 1;

typedef struct _node
{
	char *words;
	int  wordsNum;
	int  row;
	int  col;
	struct _node *parent;
	struct _node *left;
	struct _node *right;
	
}node;

typedef struct _tree
{
	int  nodeNum;
	int  depth;
	node *root;
	
}tree;

