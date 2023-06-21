#include <iostream>
#include <queue>
#include "rectangles.h"
#include "myconsole.h"
using namespace std;

class BinaryTree
{
private:

	struct TreeNode
	{
		int value;
		TreeNode* lChild;
		TreeNode* rChild;

		bool flag;

		rectangles* r;

		//default constructor
		TreeNode()
		{
			flag = false;
			this->lChild = this->rChild = nullptr;
			r = new rectangles[3];
		}

		//parameterised constructor
		TreeNode(int val)
		{
			flag = false;
			this->value = val;
			this->lChild = this->rChild = nullptr;
			r = new rectangles[3];
		}

		bool isLeaf()
		{
			return !this->lChild && !this->rChild;
		}

		~TreeNode() {
			delete[] r;
			r = nullptr;
		}
	};

	TreeNode* root;

	void deleteTree(TreeNode* node)
	{
		if (node == NULL) return;

		/* first delete both subtrees */
		deleteTree(node->lChild);
		deleteTree(node->rChild);

		/* then delete the node */
		delete node;
	}

	bool delete_(int key, TreeNode*& ptr)
	{
		if (ptr == NULL) {
			return false;
			//do nothing
		}

		//node is found
		if (ptr->value == key) {
			cout << "Node deleted" << endl;
			deleteTree(ptr);
			ptr = nullptr;
			return true;
		}
		else
		{
			/* then recur on left subtree */
			if (delete_(key, ptr->lChild) == true)
			{
				return true;
			}
			else
			{
				/* then recur on right subtree */
				if (delete_(key, ptr->rChild) == true)
				{
					return true;
				}

				return false;
			}
		}
	}//end of delete

	bool exists(int val1, TreeNode* ptr)
	{
		if (ptr == NULL) {
			return false;
		}

		//node is found
		if (ptr->value == val1) {
			return true;
		}
		else
		{
			/* then recur on left subtree */
			if (exists(val1, ptr->lChild) == true)
			{
				return true;
			}
			else
			{
				/* then recur on right subtree */
				if (exists(val1, ptr->rChild) == true)
				{
					return true;
				}

				return false;
			}
		}
	}

	bool insertR(int value, int node, TreeNode* ptr)
	{
		if (ptr == NULL) {
			return false;
		}

		//node is found
		if (ptr->value == node) {
			//node does not have a right child
			if ((ptr->rChild == nullptr))
			{
				ptr->rChild = new TreeNode(value);
				if (ptr->flag == false)
				{
					ptr->r[0].split(ptr->r[1], ptr->r[2]);
					ptr->flag = true;
				}

				ptr->rChild->r[0] = ptr->r[2];
			}
			//node has a right chil
			else
			{
				cout << "**Node already has a right child**" << endl;
			}

			return true;
		}
		else
		{
			/* then recur on left subtree */
			if (insertR(value, node, ptr->lChild) == true)
			{
				return true;
			}
			else
			{
				/* then recur on right subtree */
				if (insertR(value, node, ptr->rChild) == true)
				{
					return true;
				}

				return false;
			}
		}

	}

	bool insertL(int value, int node, TreeNode* ptr)
	{
		if (ptr == NULL) {
			return false;
		}

		//node is found
		if (ptr->value == node) {
			//node does not have a left child
			if ((ptr->lChild == nullptr))
			{
				ptr->lChild = new TreeNode(value);
				if (ptr->flag == false)
				{
					ptr->r[0].split(ptr->r[1], ptr->r[2]);
					ptr->flag = true;
				}

				ptr->lChild->r[0] = ptr->r[1];
			}
			//node has a left child
			else
			{
				cout << "**Node already has a left child**" << endl;
			}

			return true;
		}
		else
		{
			/* then recur on left subtree */
			if (insertL(value, node, ptr->lChild) == true)
			{
				return true;
			}
			else
			{
				/* then recur on right subtree */
				if (insertL(value, node, ptr->rChild) == true)
				{
					return true;
				}

				return false;
			}
		}

	}

	//displays whole tree
	void display(TreeNode* ptr) {
		if (ptr == NULL) {
			return;
		}
		else
		{
			ptr->r[0].draw();

			Sleep(1000);

			//if node is leaf, then we don't print white children
			if ((ptr->lChild == NULL) && (ptr->rChild == NULL))
			{
				return;
			}
			else
			{
				//if node left child exists, we print it black
				if (ptr->lChild != NULL) {
					display(ptr->lChild);
				}
				//if node left child does not exist, we print it white
				else
				{
					ptr->r[1].drawWhite();
				}

				//if node right child exists, we print it black
				if (ptr->rChild != NULL)
				{
					display(ptr->rChild);
				}
				//if right left child does not exist, we print it white
				else
				{
					ptr->r[2].drawWhite();
				}

				Sleep(1000);
			}

		}
	}

	//to display a single node
	bool displayNode(int val, TreeNode* ptr) {
		if (ptr == NULL) {
			return false;
		}

		//node is found
		if (ptr->value == val) {
			ptr->r[0].draw();
			return true;
		}
		//otherwise
		else
		{
			/* then recur on left subtree */
			if (displayNode(val, ptr->lChild) == true)
			{
				return true;
			}
			else
			{
				/* then recur on right subtree */
				if (displayNode(val, ptr->rChild) == true)
				{
					return true;
				}

				return false;
			}
		}
	}

	void displayLeaves(TreeNode* ptr) {
		if (ptr == NULL) {
			return;
		}

		//node is found
		if ((ptr->lChild == NULL) && (ptr->rChild == NULL)) {
			ptr->r[0].DrawShrinkedRectangle();
		}
		//otherwise
		else
		{
			if (ptr->lChild != NULL)
			{
				displayLeaves(ptr->lChild);
			}
			if (ptr->rChild != NULL)
			{
				displayLeaves(ptr->rChild);
			}
		}
	}

	//same as pre order
	void print(TreeNode* ptr) {
		if (ptr != nullptr)
		{
			print(ptr->lChild);
			cout << ptr->value << " ";
			print(ptr->rChild);
		}
	}

	/* Function to print level order traversal a tree*/
	void printLevelOrder(TreeNode* root)
	{
		int h = height(root);
		int i;
		for (i = 1; i <= h; i++)
			printCurrentLevel(root, i);
	}

	/* Print nodes at a current level */
	void printCurrentLevel(TreeNode* root, int level)
	{
		if (root == NULL)
			return;
		if (level == 1)
			cout << root->value << " ";
		else if (level > 1) {
			printCurrentLevel(root->lChild, level - 1);
			printCurrentLevel(root->rChild, level - 1);
		}
	}

	/* Compute the "height" of a tree -- the number of nodes along the longest path from the root node down to the farthest leaf node.*/
	int height(TreeNode* node)
	{
		if (node == NULL)
			return 0;
		else {
			/* compute the height of each subtree */
			int lheight = height(node->lChild);
			int rheight = height(node->rChild);

			/* use the larger one */
			if (lheight > rheight) {
				return (lheight + 1);
			}
			else {
				return (rheight + 1);
			}
		}
	}

public:

	BinaryTree()
	{
		this->root = nullptr;
	}

	//called when there is no root
	void insertroot(int val, int height) {
		root = new TreeNode(val);
		rectangles r1(2, 2, 50, height);

		root->r[0] = r1;

		root->r[0].split(root->r[1], root->r[2]);
	}

	void insertR(int val1, int node) {
		if (insertR(val1, node, this->root) == false)
		{
			cout << "The node you want to insert at doesn't exist" << endl;
		}
	}

	void insertL(int val1, int node) {
		if (insertL(val1, node, this->root) == false)
		{
			cout << "The node you want to insert at doesn't exist" << endl;
		}
	}

	bool exists(int val)
	{
		return this->exists(val, this->root);
	}

	void delete_(int val)
	{
		if (delete_(val, this->root) == false)
		{
			cout << "Node does not exist" << endl;
		}
	}

	int calculateHeight() {
		return height(this->root);
	}

	void display() {
		display(this->root);
	}

	void displayNode(int val) {
		bool temp = displayNode(val, this->root);
		if (temp == false)
		{
			cout << "** The Node you want to display does not exist **" << endl;
		}
	}

	void displayLeaves() {
		displayLeaves(this->root);
	}

	void print() {
		print(this->root);
	}

	void printLevelOrder()
	{
		printLevelOrder(this->root);
	}

	//destructor
	~BinaryTree() {
		deleteTree(this->root);
	}
};

void game() {
	bool flag = false;
	BinaryTree bst;
	int counter = 0;
	char option; //option
	int height = 0; //height of root rectangle to be displayed

	while (flag == false)
	{
		if (counter == 0)
		{
			int val = 0;
			cout << "Enter the value of Root" << endl;
			cin >> val;

			height = 0;
			cout << "Enter Height of display Rectangle: " << endl;
			cin >> height;

			bst.insertroot(val, height);

			counter++;

			cout << endl;
		}

		else
		{
			cout << "Would you like to insert right (r), insert left (l), print (p), delete (d), calculate height (h), or exit (e)" << endl;
			cin >> option;

			cout << endl;

			if ((option == 'e') || (option == 'E'))
			{
				flag = true;
				cout << "Good-Bye!" << endl;
			}

			else
			{
				if ((option == 'r') || (option == 'R'))
				{
					//inputting right child
					bool flag2 = false;
					int val1;
					while (flag2 == false)
					{
						cout << "Enter value of right child:" << endl;
						cin >> val1;

						if (bst.exists(val1) == true)
						{
							cout << endl << "** This value already exists in the tree, re-enter value **" << endl;
						}
						else
						{
							int node = 0;
							cout << "Enter value for the Node you wish to add this child to: " << endl;
							cin >> node;

							//call right insert here
							bst.insertR(val1, node);

							flag2 = true;
						}
					}
				}

				else
				{
					if ((option == 'l') || (option == 'L'))
					{
						//inputting left child
						bool flag2 = false;
						int val2;
						while (flag2 == false)
						{
							cout << "Enter value of left child:" << endl;
							cin >> val2;

							if (bst.exists(val2) == true)
							{
								cout << endl << "** This node already exists in the tree, re-enter value **" << endl;
							}
							else
							{
								int node = 0;

								cout << "Enter value for the Node you wish to add this child to: " << endl;
								cin >> node;

								//call left insert here
								bst.insertL(val2, node);
								flag2 = true;
							}
						}
					}

					else
					{
						if ((option == 'p') || (option == 'P'))
						{
							bool flag1 = false;
							char op;
							cout << "Would you like to Display Entire Tree (1) or a Single Node (2) or All Leaves (3): " << endl;
							cin >> op;

							while (flag1 == false)
							{
								if (op == '1')
								{
									ClearScreen();
									bst.display();

									char t;
									cin >> t;

									ClearScreen();

									flag1 = true;
								}
								else
								{
									if (op == '2')
									{
										int node;
										cout << "Enter value of Node you want to display: " << endl;
										cin >> node;

										ClearScreen();
										bst.displayNode(node);

										char t;
										cin >> t;

										ClearScreen();
										flag1 = true;
									}
									else
									{
										if (op == '3')
										{
											ClearScreen();
											bst.displayLeaves();

											char t;
											cin >> t;

											ClearScreen();
											flag1 = true;
										}
										else
										{
											cout << "** Re-enter correct option **" << endl;
										}
									}
								}
							}
						}

						else
						{
							if ((option == 'd') || (option == 'D'))
							{
								int node;
								cout << "Enter node to delete" << endl;
								cin >> node;

								bst.delete_(node);

								if (bst.calculateHeight() == 0)
								{
									counter--;
								}
							}

							else
							{
								if ((option == 'h') || (option == 'H'))
								{
									cout << "Height of tree is: " << bst.calculateHeight() - 1 << endl;
								}

								else cout << "Please enter the correct options only" << endl;
							}
						}
					}
				}
			}

			cout << endl;
		}
	}
}

int main() {
	game();
	system("pause");
}
