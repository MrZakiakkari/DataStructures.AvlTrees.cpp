// Datastructures.AVLtrees.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AvlTrees.cpp"
using namespace std;


const int InsertItemCode = 1;
const int PrintCode = 2;
const int ExitCode = 4;
const int PrintMenuCode = 3;



void PrintMenu() {

	cout << "Type " << InsertItemCode << " to insert an item to the AVL Tree" << endl;
	cout << "Type " << PrintCode << " to print the AVL Tree" << endl;
	cout << "Type " << PrintMenuCode << " to Print the Menu." << endl;
	cout << "Type " << ExitCode << " To Exit the program." << endl;

}
void InValidOption() {
	cout << "Invalid option entered." << endl;
	PrintMenu();
}

AVLtree<int>* avlTree = new AVLtree<int>();

void InsertTree() {
	cout << "Insert Item " << endl;
	avlTree->InsertItem(1);
	avlTree->InsertItem(2);
}

void PrintAVLTree() {
	cout << "PrintAVLTree" << endl;
	cout << "AVL TREE";
	avlTree->PrintTree();
}

void InitializeAvlTree()
{

}



int main()
{
	bool run = true;
	int option = -1;

	PrintMenu();

	InitializeAvlTree();
	do
	{
		cin >> option;
		switch (option)
		{
		case PrintCode:
			PrintAVLTree();
			break;
		case InsertItemCode:
			InsertTree();
			break;
		case PrintMenuCode:
			PrintMenu();
			break;
		case ExitCode:
			run = false;
			break;
		default:
			InValidOption();
			break;
		}


		//The Progam
	} while (run);

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
