#include <iostream>
#include <cstdint>

using namespace std;

struct node
{
	int key_value;
	node *left;
	node *right;
};

class btree 
{
	public:
		btree();
		~btree();
		void insert(int key);
		node *search(int key);
		void destroy_tree();
		node *root_retriever();
		
	private:
		void destroy_tree(node *leaf);
		void insert(int key, node *leaf);
		node *search(int key, node *leaf);
		node *root;
};

btree::btree()
{
	root=NULL;
}

btree::~btree()
{
	destroy_tree();
}

void btree::destroy_tree(node *leaf)
{
	if(leaf!=NULL)
	{
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
	}
}

void btree::insert(int key, node *leaf)
{
	if(key< leaf->key_value)
	{
		if(leaf->left!=NULL)
		 insert(key, leaf->left);	
		else
		{
		  leaf->left=new node;
		  leaf->left->key_value=key;
		  leaf->left->left=NULL;
		  leaf->left->right=NULL;
		}
	}
	else if (key>=leaf->key_value)
	{
		if(leaf->right!=NULL)
			insert(key, leaf->right);
		else
		{
		  leaf->right=new node;
		  leaf->right->key_value=key;
		  leaf->right->left=NULL;
		  leaf->right->right=NULL;
		}
	}
}

node *btree::search(int key, node *leaf)
{
	if(leaf!=NULL)
	{
		if(key==leaf->key_value)
			return leaf;
		if(key<leaf->key_value)
			return search(key, leaf->left);
		else
			return search(key, leaf->right);
	}
	else return NULL;
}

void btree::insert(int key)
{
	if(root!=NULL)
		insert(key, root);
	else
	{
		root=new node;
		root->key_value=key;
		root->left=NULL;
		root->right=NULL;
	}
}

node *btree::search(int key)
{
	return search(key, root);
}

void btree::destroy_tree()
{
	destroy_tree(root);
}

node *btree::root_retriever()
{
	return root;
}

int main()
{
	 
	btree arbol;
	arbol.insert(8);
	arbol.insert(5);
	arbol.insert(10);
	arbol.insert(3);
	arbol.insert(15);
	
	
	cout  << "                      (" << arbol.root_retriever()->key_value << ") \n " ;
	cout  << "                    /   \\  \n" ;
	cout  << "                    /     \\   \n" ;
	cout  << "                   /       \\    \n" ;
	cout  << "                 (" << arbol.root_retriever()->left->key_value << ")       (" << arbol.root_retriever()->right->key_value << ") \n " ;
		cout  << "             /       \\    \n" ;
	cout  << "            (" << arbol.root_retriever()->left->left->key_value << ") (" << arbol.root_retriever()->left->right->key_value << ")      (" << arbol.root_retriever()->right->key_value << ") \n " ;
	cout  << arbol.search(0)->key_value;
	arbol.destroy_tree();
	return 0;

}


