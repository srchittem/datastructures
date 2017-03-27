//#include "stdafx.h"

#include <iostream>
#include <queue>
#include <stdio.h>
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
	void LCAUtil(node *root, int f, int s, queue<int>& q1, queue<int>& q2);
	int leftMostNodeUtil(node *root, int &ml, int &lvalue);
	void greatestNodeatEachLevelUtil(node *root, queue<node *> q);
	void maxSeqLengthUtil(node *root,int seq, int &cur, int&max);
	void modifyUtil(node *root, int &val);
	int LcaInBstUtil(node *root, int a, int b);
public:
	tree();
	~tree();
	void inOrder();
	void buildTree();
	int height();
	void levelOrderTraverse();
	void levelOrderTraversewithQ();
	int diameter();
	int LCAWithQ(int a, int b);
	int leftMostNode();
	void greatestNodeatEachLevel();
	int maxSeqLength();
	void modifyTree();
	int LcaInBst(int a, int b);
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

void tree::modifyUtil(node *root, int &val)
{
	int temp;
	if(!root)
		return;
	modifyUtil(root->right,val);
	temp = root->data;
	root->data = val;
	val += temp;
	modifyUtil(root->left,val);
	
	

}

void tree::modifyTree()
{
	int val = 0;
	modifyUtil(Root,val);
}
void tree::buildTree()
{
	addNode(new node(10));	
	addLeftNode(Root,new node(6));	
	addRightNode(Root,new node(15));	
	addLeftNode(Root->left,new node(2));	
	addRightNode(Root->left,new node(8));	
	addLeftNode(Root->right,new node(14));	
	addRightNode(Root->right,new node(20));	
#if 0
	addRightNode(Root->right->right,new node(8));
	addRightNode(Root->right->right->right,new node(9));
	addRightNode(Root->right->right->right->right,new node(10));
	addRightNode(Root->right->right->right->right->right,new node(11));
	addLeftNode(Root->left->left,new node(8));
	addRightNode(Root->left->left, new node(10));
//	addLeftNode(Root->left->left->left,new node(11));	
#endif
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

int tree::leftMostNodeUtil(node *root, int &ml, int &lvalue)
{
	if (!root)
		return 0;
	int ll =1+ leftMostNodeUtil(root->left,ml,lvalue);
	int rl = 1+ leftMostNodeUtil(root->right,ml,lvalue);

	if (ml < ll)
	{
		ml = ll;
		lvalue = root->data;
	}
		
	return  (ll < rl ? ll : ll);
	//return ml;
}

int tree::leftMostNode()
{
	int ll = 1,rl=1,ml=0, value = 0;
	 leftMostNodeUtil(Root,ml,value);
	cout << value << endl;
	return ml;

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

void tree::greatestNodeatEachLevelUtil(node *root, queue<node *> q)
{
	if (q.empty() && root)
	{
		q.push(root);
	}
	while (!q.empty())
	{
		int size = q.size();
		int max = 0;
		for (int i = 0; i < size; i++)
		{
			node * n = q.front();
			if (n->data > max)
			{
				max = n->data;
			}
			q.pop();
			if (n->left)
				q.push(n->left);
			if (n->right)
				q.push(n->right);

		}
		cout << "maximum at this level:" << max <<endl;
		
	}

}

void tree::greatestNodeatEachLevel()
{
	queue<node *> q;

	greatestNodeatEachLevelUtil(Root, q);
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

int tree::LcaInBstUtil(node *root, int a, int b)
{
	if(!root)
		return -1;
	if(root->data == a || root->data == b)
	{	
			cout << "returning from here"<<endl;
			return root->data;
	}
	if((root->data >a && root->data <b) || (root->data < a && root->data > b) )
		return root->data;
	else if(root->data > a && root->data > b)
	{
		LcaInBstUtil(root->left,a,b);
	}
	else if(root->data < a && root->data < b)
	{
		LcaInBstUtil(root->right,a,b);
	}
	


}


int  tree::LcaInBst(int a, int b)
{
	return LcaInBstUtil(Root,a,b);

}
void tree::LCAUtil(node *root, int f, int s, queue<int>& q1, queue<int>& q2)
{
	static int f_f,s_f;

	if(!root)
		return;

	if(f_f && s_f)
		return;

	if(root->data != f && root->data != s)
	{

		if(!f_f)
			q1.push(root->data);
		if(!s_f)
			q2.push(root->data);
	}	
	else if(root->data == f)
	{
		f_f = 1;
	}
	else
		s_f = 1;
	
	LCAUtil(root->left,f,s,q1,q2);
	LCAUtil(root->right,f,s,q1,q2);
	

}

void tree::maxSeqLengthUtil(node *root,int seq, int &cur, int&max)
{
    if(!root)
           return;
    if(root->data == seq)
    {
        cur =cur+1;
        if(cur >max)
               max = cur;
	cout<<"max:"<<max<<"cur:"<<cur <<endl;
    }
    else
        cur = 1;
    maxSeqLengthUtil(root->left,root->data+1,cur,max);
    maxSeqLengthUtil(root->right,root->data+1,cur,max);
    
    
}
int tree::maxSeqLength()
{
	int lc = 0,rc =0, max =0;
	maxSeqLengthUtil(Root,Root->data,lc,max);
	return max;
}

int tree::LCAWithQ(int a, int b)
{
	queue<int> q1,q2;
	LCAUtil(Root,a,b,q1,q2);
	//cout <<"q1 size"<<q1.size()<<"q2 size"<<q2.size();
	while(!q1.empty() && !q2.empty())
	{
		if(q1.front() == q2.front())
		{

			return q1.front();
		}
		q1.pop();
		q2.pop();
	}	
	return 0;
}

int main()
{
	tree r;
	r.buildTree();
//	r.inOrder();
//	r.greatestNodeatEachLevel();
//	r.modifyTree();
	cout <<"LCA:"<<r.LcaInBst(2,6)<<endl;
//	r.inOrder(); 
}
