#include<iostream>
using namespace std;

int seed = 1983;
int rand(){
	seed = seed*257931 + 7517711;
	return (seed>>16) & 0x7FFF;
}
typedef int KeyType;
struct Node{
	KeyType key;

	int priority, size;
	Node *left, *right;
	Node(KeyType & _key)
		: key(_key), priority(rand()), size(1), left(NULL),right(NULL) { }
	void setLeft(Node* newLeft){ left = newLeft; calcSize();}
	void setRight(Node* newRight){ right = newRight; calcSize();}
	void calcSize(){
		size = 1;
		if (left) size += left->size;
		if (right) size += right->size;
	}
};
struct NodePair{
	Node *first, *second;
	NodePair(Node *_f, Node *_s) : first(_f), second(_s){}
};
NodePair split(Node* root, KeyType key){
	if (root == NULL) return NodePair(NULL, NULL);

	if (root->key < key){
		NodePair rs = split(root->right, key);
		root->setRight(rs.first);
		return NodePair(root, rs.second);
	}
	NodePair ls = split(root->left, key);
	root->setLeft(ls.second);
	return  NodePair(ls.first, root);
}
Node* insert(Node* root, Node* node){
	if (root == NULL) return node;
	if (root->priority < node->priority){
		NodePair splitted = split(root,node->key);
		node->setLeft(splitted.first);
		node->setRight(splitted.second);
		return node;
	}
	else if (node->key < root->key){
		root->setLeft(insert(root->left, node));
	}else
		root->setRight(insert(root->right, node));
	return root;
}
// 전제 : max(a) < min(b)
Node* merge(Node* a, Node* b){
	if (a == NULL) return b;
	if (b == NULL) return a;
	if (a->priority < b->priority){
		b->setLeft(merge(a, b->left));
		return b;
	}

	a->setRight(merge(a->right,b));
	return a;
}
Node* erase(Node* root, KeyType key){
	if (root == NULL) return root;
	if (root->key == key){
		Node *ret = merge(root->left, root->right);
		delete root;
		return ret;
	}
	if (key < root->key)
		root->setLeft(erase(root->left, key));
	else
		root->setRight(erase(root->right, key));
	return root;
	
}
int main(){

	return 0;
}

