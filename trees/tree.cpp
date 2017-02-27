#include <iostream>
#include <queue>
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
	void inOrderTraverse(node *root);
	void addLeftNode(node * root, node* node);
	void addRightNode(node * root, node* node);
	void addNode(class node* node);
	int heightUtil(node *root);
	void levelOrderTraverseUtil(node *root, int level);
	void levelOrderTraverseUtil(node *root, queue<node *> q);
	void diameterUtil(node *root, int& d);
public:
	tree();
	~tree();
	void inOrder();
	void buildTree();
	int height();
	void levelOrderTraverse();
	void levelOrderTraversewithQ();
	int diameter();
};

tree::tree()
{
	Root = NULL;
}

tree::~tree()
{
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
			//addNodetoLeft(node);
		}
	}	
}

int tree::heightUtil(node *root)
{
	if(!root)
		return 0;
	int lh = heightUtil(root->left);
	int rh = heightUtil(root->right);
	return 1+(lh>rh?lh:rh);
		
}
int tree::height()
{
	return heightUtil(Root);	
}

void tree::buildTree()
{
	addNode(new node(1));	
	addLeftNode(Root,new node(2));	
	addRightNode(Root,new node(3));	
	addLeftNode(Root->left,new node(4));	
	addRightNode(Root->left,new node(5));	
	addLeftNode(Root->right,new node(6));	
	addRightNode(Root->right,new node(7));	
	addLeftNode(Root->right->right,new node(8));	
	addLeftNode(Root->right->right->left,new node(9));	
	addLeftNode(Root->left->left,new node(4));	
	addLeftNode(Root->left->left->left,new node(4));	
}


void tree::addLeftNode(node * root, node* node)
{
	root->left = node;
}

void tree::addRightNode(node * root, node* node)
{
	root->right = node;
}

void tree::inOrderTraverse(node *root)
{
	if(!root)
		return;
	inOrderTraverse(root->left);
	printf("%d ",root->data);
	inOrderTraverse(root->right);
}

void tree::levelOrderTraverseUtil(node *root, int level)
{
	printf("i holy crap");
	if(!root )
		return;
	if( level ==1)
	{
		printf("%d ",root->data);
		return;
	}
	levelOrderTraverseUtil(root->left,level-1);
	levelOrderTraverseUtil(root->right,level-1);
}

void tree::levelOrderTraverseUtil(node *root, queue<node *> q)
{
	if(q.empty() && root)
	{
		q.push(root);
	}
	while(!q.empty())
	{
		node * n = q.front();
		printf("%d ",n->data);
		q.pop();
		if(n->left)
			q.push(n->left); 
		if(n->right)
			q.push(n->right); 
	}
	
}
void tree::levelOrderTraversewithQ()
{
	queue<node *> q;
	if(q.empty())
		cout << "Q is empty";
	else
		cout << "Q is non empty";
	
	levelOrderTraverseUtil(Root,q);
}
void tree::levelOrderTraverse()
{
	int h = height();
	for (int i = 1; i<=h; i++)
		levelOrderTraverseUtil(Root,i);	
}

void tree::diameterUtil(node *root, int& d)
{
	if(!root)
		return;
	int lh = heightUtil(root->left);
	int rh = heightUtil(root->right);
	if(lh+rh+1 > d)
		d = lh+rh+1;
	
	diameterUtil(root->left,d);
	diameterUtil(root->right,d);
}
int tree::diameter()
{
	int d=0;
	diameterUtil(Root,d);
	return d;
}

void tree::inOrder()
{
	inOrderTraverse(Root);	
}
int main()
{
	tree r;
	r.buildTree();
//	r.inOrder();
	printf("diameter: %d",r.diameter());
}
