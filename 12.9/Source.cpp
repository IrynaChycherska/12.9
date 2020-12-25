#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;
typedef int Info;
struct Node
{
	Node* left,
		* right;
	Info info;
};
Node* CreateTree(int nodeCount);
void PrintTree(Node* root, int level);
Node* BinarySearchInsert(Node*& root, Info value, bool& found);
Node* CreateTree1(int nodeCount);
int Count(Node* root);
void RightRotation(Node*& root);
void LeftRotation(Node*& root);
void BalanceCount(Node*& root);
Node* FindMax(Node* root);
Node* BinarySearchDelete(Node* root, Info value);
void InfixOrder(Node* root);
int main()
{
	int N;
	cout << "Enter nodes count: "; cin >> N;
	Node* root = CreateTree(N);
	Info value;
	bool found = false;
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Dia:" << endl << endl;
		cout << " [1] - creating a binary tree" << endl;
		cout << " [2] - output of the binary tree" << endl;
		cout << " [3] - creating a binary search tree" << endl;
		cout << " [4] - adding" << endl;
		cout << " [5] - balancing binary search tree" << endl;
		cout << " [6] -  delete a binary search tree element that has no child nodes" << endl;
		cout << " [7] - delete a binary search tree element that has child nodes" << endl;
		cout << " [8] - delete a binary search tree element that has two child nodes" << endl;
		cout << " [9] - delete a binary search tree elemen " << endl;
		cout << " [10] - «Infix» bypass " << endl;
		cout << " [0] - exit" << endl << endl;
		cout << "Enter a value: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			CreateTree(N);
			break;
		case 2:
			PrintTree(root,0);
			break;
		case 3:
				cout << "value: "; cin >> value;
				BinarySearchInsert(root, value, found);
			break;
		case 4:
			CreateTree1(N);
			break;
		case 5:
			BalanceCount(root);
			break;
		case 6:
			cout << "delete value: "; cin >> value;
			root = BinarySearchDelete(root, value);
			break;
		case 7:
			cout << "delete value: "; cin >> value;
			root = BinarySearchDelete(root, value);
			break;
		case 8:
			cout << "delete value: "; cin >> value;
			root = BinarySearchDelete(root, value);
			break;
		case 9:
			cout << "delete value: "; cin >> value;
			root = BinarySearchDelete(root, value);
			break;
		case 10:
			cout << "Infix order: ";
			InfixOrder(root); cout << endl;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	return 0;
}
Node* CreateTree(int nodeCount)
{
	if (nodeCount == 0)
		return NULL;
	else
	{
		Node* newNode = new Node;

		cout << " Enter node value: ";
		cin >> newNode->info;

		int leftCount = nodeCount / 2;
		int rightCount = nodeCount - leftCount - 1;
		newNode->left = CreateTree(leftCount);
		newNode->right = CreateTree(rightCount);
		return newNode;
	}
}
void PrintTree(Node* root, int level)
{
	if (root != NULL)
	{
		PrintTree(root->right, level + 1);
		for (int i = 1; i <= level; i++)
			cout << " ";
		cout << root->info << endl;
		PrintTree(root->left, level + 1);
	}
}
Node* BinarySearchInsert(Node*& root, Info value, bool& found)
{
	if (root == NULL)
	{
		root = new Node;
		root->info = value;
		root->left = NULL;
		root->right = NULL;
		found = false;
		return root;
	}
	else
		if (value == root->info)
		{
			found = true;
			return root;
		}
		else
			if (value < root->info)
				return BinarySearchInsert(root->left, value, found);
			else
				return BinarySearchInsert(root->right, value, found);
}
Node* CreateTree1(int nodeCount)
{
	if (nodeCount == 0)
		return NULL;
	else
	{
		Node* newNode = new Node;

		cout << " Enter node value: ";
		cin >> newNode->info;

		int leftCount = nodeCount / 2;
		int rightCount = nodeCount - leftCount - 1;
		newNode->left = CreateTree(leftCount);
		newNode->right = CreateTree(rightCount);
		return newNode;
	}
}
int Count(Node* root)
{
	if (root == NULL)
		return 0;
	else
		return 1 + Count(root->left) + Count(root->right);
}
void RightRotation(Node*& root)
{
	Node* tmp1 = root->left;
	Node* tmp2 = tmp1->right;
	tmp1->right = root; //1
	root->left = tmp2; //2
	root = tmp1; //3
}
void LeftRotation(Node*& root)
{
	Node* tmp1 = root->right;
	Node* tmp2 = tmp1->left;
	tmp1->left = root; //1
	root->right = tmp2; //2
	root = tmp1; //3
}
void BalanceCount(Node*& root)
{
	if (root != NULL)
	{
		while (Count(root->left) > Count(root->right) + 1)
			RightRotation(root);
		while (Count(root->left) + 1 < Count(root->right))
			LeftRotation(root);
		BalanceCount(root->left);
		BalanceCount(root->right);
	}
}
Node* FindMax(Node* root) {
	if (root
		->right != NULL
		)
		return FindMax(root
			->right);
	else
		return root;
}
Node* BinarySearchDelete(Node* root, Info value)
{
	if (NULL == root) return NULL;
	if (root->info == value)
	{
		if (NULL == root->left && NULL == root->right)
		{
			delete root;
			return NULL;
		}
		if (NULL == root->right && root->left != NULL)
		{
			Node* temp = root->left;
			delete root;
			return temp;
		}
		if (NULL == root->left && root->right != NULL)
		{
			Node* temp = root->right;
			delete root;
			return temp;
		}
		root->info = FindMax(root->left)->info;
		root->left = BinarySearchDelete(root->left, root->info);
		return root;
	}
	if (value < root->info)
	{
		root->left = BinarySearchDelete(root->left, value);
		return root;
	}
	if (value > root->info)
	{
		root->right = BinarySearchDelete(root->right, value);
		return root;
	}
	return root;
}

void InfixOrder(Node* root)
{
	if (root != NULL)
	{
		InfixOrder(root->left);
		cout << root->info << " ";
		InfixOrder(root->right);
	}
}
