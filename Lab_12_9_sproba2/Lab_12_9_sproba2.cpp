#include <iomanip>
#include <iostream>
using namespace std;
typedef int Info;
struct Node
{
	Node* left,
		* right;
	Info info;
	string word;

};
void PrintTree(Node* root, int level);
Node* BinarySearchInsert(Node*& root, Info value, string word, bool& found);
Node* Find(Node* root, Info value);
Node* FindMax(Node* root);
void RightRotation(Node*& root);
void LeftRotation(Node*& root);
int Height(Node* root);
int BFactor(Node* root);
void BalanceHeight(Node*& root);
Node* BinarySearchDelete(Node* root, Info val);
void DeleteTree(Node*& root, Node* node);
void PrintMenu();
Node* DeleteNodeWithoutChildren(Node* root, Info valueNoChildren);
Node* DeleteNodeWithOneChild(Node* root, Info valueOneChildren);
Node* DeleteNodeWithTwoChildren(Node* root, Info valueTwoChild);
Node* FindMin(Node* root);
void InfixOrder(Node* root, Node** maxNode);
Node* SearchMax(Node* root);
void DeleteTree(Node*& root, Node* node);

int main()
{
	int N;

	int choice;
	Node* root = NULL;
	Info value;
	Info valueNoChildren;
	Info valueOneChildren;
	Info valueTwoChild;
	Info valueForAll;
	string word;
	bool found = false;
	while (true)
	{
		PrintMenu();
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			cout << "Nodes count: "; cin >> N;
			for (int i = 0; i < N; i++)
			{
				cout << "value and a word: "; cin >> value; cin >> word;
				BinarySearchInsert(root, value, word, found);
			}
			cout << endl;
			break;

		}

		case 2:
		{
			PrintTree(root, 0);
			cout << endl;
			break;
		}

		case 3:
		{
			cout << "\n Enter a number and a word to insert: ";
			cin >> value >> word;
			BinarySearchInsert(root, value, word, found);
			if (found) {
				cout << "Error: The number " << value << " already exists in the tree." << endl;
			}
			else {
				cout << "The number " << value << " and the word " << word << " were successfully inserted." << endl;
			}

			break;
		}

		case 4:
		{
			BalanceHeight(root);
			cout << endl;
			break;
		}

		case 5:
		{
			cout << "\n Enter node without clild element to delete: \n";
			cin >> valueNoChildren;
			DeleteNodeWithoutChildren(root, valueNoChildren);
			cout << endl;
			break;
		}

		case 6:
		{
			cout << "\n Enter node with one child element to delete: \n";
			cin >> valueOneChildren;
			DeleteNodeWithOneChild(root, valueOneChildren);
			cout << endl;
			break;
		}

		case 7:
		{
			cout << "\n Enter node with two children elements to delete: \n";
			cin >> valueTwoChild;
			DeleteNodeWithTwoChildren(root, valueTwoChild);
			cout << endl;
			break;
		}

		case 8:
		{
			cout << "\n Enter node to delete it and all its children: \n";
			cin >> valueForAll;
			DeleteTree(root, Find(root, valueForAll));
			cout << endl;
			break;
		}
		case 9:
		{
			Node* maxNode = NULL;
			maxNode = SearchMax(root);
			cout << maxNode->info << maxNode->word << endl;
			cout << endl;
			break;
		}
		}
	}
}

void DeleteTree(Node*& root, Node* node)
{
	if (node != NULL)
	{
		DeleteTree(root, node->left);
		DeleteTree(root, node->right);
		root = BinarySearchDelete(root, node->info);
	}
}

void PrintMenu()
{
	cout << "\n Choose anaction:\n ";
	cout << " 1. Create a binary tree\n ";
	cout << " 2. Display the binary tree\n ";
	cout << " 3. Add the new element maintaining order\n ";
	cout << " 4. Balance the binary search tree\n ";
	cout << " 5. Remove a tree element with no child nodes\n";
	cout << " 6. Remove a tree element with one child nodes\n";
	cout << " 7. Remove a tree element with two child nodes\n";
	cout << " 8. Remove a tree element with all its child nodes\n";
	cout << " 9. Find the first element of the binary tree with the maximum value\n ";

}


void PrintTree(Node* root, int level)
{
	if (root != NULL)
	{
		PrintTree(root->right, level + 1);
		for (int i = 1; i <= level; i++)
			cout << " ";
		cout << root->info << root->word << endl;
		PrintTree(root->left, level + 1);
	}
}

Node* SearchMax(Node* root)
{
	Node* maxNode = NULL;
	InfixOrder(root, &maxNode);
	return maxNode;
}
void InfixOrder(Node* root, Node** maxNode)
{
	if (root != NULL)
	{
		InfixOrder(root->left, maxNode);
		if (*maxNode == NULL || root->info > (*maxNode)->info)
		{
			*maxNode = root;
		}
		InfixOrder(root->right, maxNode);
	}
}
Node* BinarySearchInsert(Node*& root, Info value, string word, bool& found)
{
	if (root == NULL)
	{
		root = new Node;
		root->info = value;
		root->word = word;
		root->left = NULL;
		root->right = NULL;
		found = false;
		return root;
	}
	else
		if (value == root->info && word == root->word)
		{
			found = true;
			return root;
		}
		else
			if (value < root->info)
				return BinarySearchInsert(root->left, value, word, found);
			else
				return BinarySearchInsert(root->right, value, word, found);
}

Node* Find(Node* root, Info value)
{
	if (root == NULL || value == root->info)
		return root;
	if (value < root->info)
		return Find(root->left, value);
	else
		return Find(root->right, value);
}

Node* FindMax(Node* root)
{
	if (root->right != NULL)
		return FindMax(root->right);
	else
		return root;
}

Node* FindMin(Node* root)
{
	if (root == nullptr) {
		return nullptr; // Піддерево порожнє
	}

	while (root->left != nullptr) {
		root = root->left; // Рухаємось вліво, доки не досягнемо найлівішого вузла
	}

	return root; // Повертаємо найменший елемент
}

void RightRotation(Node*& root)
{
	Node* tmp1 = root->left;
	Node* tmp2 = tmp1->right;
	tmp1->right = root;
	root->left = tmp2;
	root = tmp1;
}
void LeftRotation(Node*& root)
{
	Node* tmp1 = root->right;
	Node* tmp2 = tmp1->left;
	tmp1->left = root;
	root->right = tmp2;
	root = tmp1;
}
int Height(Node* root)
{
	if (root == NULL)
		return 0;
	int hL = Height(root->left);
	int hR = Height(root->right);
	return (hL > hR ? hL : hR) + 1;
}
int BFactor(Node* root)
{
	return Height(root->right) - Height(root->left);
}
void BalanceHeight(Node*& root)
{
	if (root != NULL)
	{
		while (BFactor(root) >= 2)
		{
			if (BFactor(root->right) < 0)
				RightRotation(root->right);
			LeftRotation(root);
		}
		while (BFactor(root) <= -2)
		{
			if (BFactor(root->left) > 0)
				LeftRotation(root->left);
			RightRotation(root);
		}
		BalanceHeight(root->left);
		BalanceHeight(root->right);
	}
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

Node* DeleteNodeWithoutChildren(Node* root, Info valueNoChildren)
{
	if (root == nullptr) {
		return nullptr; // Дерево порожнє, нічого видаляти
	}

	if (root->info == valueNoChildren) {
		delete root;
		return nullptr; // Знайдено елемент із немає дочірніх вузлів, видаляємо його
	}

	if (valueNoChildren < root->info) {
		root->left = DeleteNodeWithoutChildren(root->left, valueNoChildren); // Рухаємось вліво
	}
	else {
		root->right = DeleteNodeWithoutChildren(root->right, valueNoChildren); // Рухаємось вправо
	}

	return root; // Повертаємо змінений корінь піддерева
}
Node* DeleteNodeWithOneChild(Node* root, Info valueOneChildren)
{
	if (root == nullptr) {
		return nullptr; // Дерево порожнє, нічого видаляти
	}

	if (root->info == valueOneChildren) {
		Node* temp = nullptr;
		if (root->left != nullptr) {
			temp = root->left; // Запам'ятовуємо дочірній вузол
		}
		else {
			temp = root->right; // Запам'ятовуємо дочірній вузол
		}
		delete root;
		return temp; // Повертаємо дочірній вузол
	}

	if (valueOneChildren < root->info) {
		root->left = DeleteNodeWithOneChild(root->left, valueOneChildren); // Рухаємось вліво
	}
	else {
		root->right = DeleteNodeWithOneChild(root->right, valueOneChildren); // Рухаємось вправо
	}

	return root; // Повертаємо змінений корінь піддерева
}
Node* DeleteNodeWithTwoChildren(Node* root, Info valueTwoChild)
{
	if (root == nullptr) {
		return nullptr; // Дерево порожнє, нічого видаляти
	}

	if (root->info == valueTwoChild) {
		if (root->left == nullptr && root->right == nullptr) {
			delete root;
			return nullptr; // Елемент без дочірніх вузлів, просто видаляємо його
		}
		else if (root->left != nullptr && root->right != nullptr) {
			Node* minRight = FindMin(root->right); // Знаходимо найменший елемент у правому піддереві
			root->info = minRight->info; // Замінюємо значення елемента, який видаляємо, на найменший елемент у правому піддереві
			root->right = DeleteNodeWithTwoChildren(root->right, minRight->info); // Рекурсивно видаляємо найменший елемент у правому піддереві
		}
		else {
			Node* temp = nullptr;
			if (root->left != nullptr) {
				temp = root->left; // Є тільки лівий дочірній вузол
			}
			else {
				temp = root->right; // Є тільки правий дочірній вузол
			}
			delete root;
			return temp; // Повертаємо дочірній вузол
		}
	}

	if (valueTwoChild < root->info) {
		root->left = DeleteNodeWithTwoChildren(root->left, valueTwoChild); // Рухаємось вліво
	}
	else {
		root->right = DeleteNodeWithTwoChildren(root->right, valueTwoChild); // Рухаємось вправо
	}

	return root; // Повертаємо змінений корінь піддерева
}