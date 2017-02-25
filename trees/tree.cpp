#include <iostream>
using namespace std;

class node
{
	friend class tree;
	int data;
	class node *left;
	class node * right;
public:
	node(int info);
	~node();
	
};

node::node (int info)
{
	data = info;
	right = left = NULL;
}

node::~node ()
{

}

class tree
{
	class node *Root;
	node* buildBalanceTree (node *root, node *newNode);
	void addNodetoLeft(node * newNode);
	void inOrderTraverse(node *root);
public:
	tree();
	~tree();
	void addNode(class node* node);
	void inOrder();
};

tree::tree()
{
	Root = NULL;
}

tree::~tree()
{
}

void tree::addNodetoLeft(node * newNode)
{
	node *root = Root;
	while(root->left!=NULL)
		root= root->left;
	root->left = newNode;
}

node* tree::buildBalanceTree (node *root, node *newNode)
{
	if(root->left && root->right)
	{
		buildBalanceTree(root->left,newNode);
		buildBalanceTree(root->right,newNode);	
	}
	else if(root->left == NULL)
		return root->left = newNode;
	
	else if (root->right == NULL)
		return root->right = newNode;	
	
	return NULL;
}

void tree::addNode(class node* node)
{
	if(!Root)
	{
		cout << "creating root of the tree";
		Root = node;
	}
	else
	{
		if(!buildBalanceTree(Root,node))
		{
			addNodetoLeft(node);
		}
	}	
}

void tree::inOrderTraverse(node *root)
{
	if(!root)
		return;
	inOrderTraverse(root->left);
	printf("%d ",root->data);
	inOrderTraverse(root->right);
}

void tree::inOrder()
{
	inOrderTraverse(Root);	
}
int main()
{
	tree r;
	r.addNode(new node(1));
	r.addNode(new node(3));
	r.addNode(new node(2));
	r.addNode(new node(4));
	r.addNode(new node(5));
	r.inOrder();
}
