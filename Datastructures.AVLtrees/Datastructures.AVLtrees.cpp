// Datastructures.AVLtrees.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;


const int InsertItemCode = 1;
const int PrintCode = 2;
const int ExitCode = 4;
const int PrintMenuCode = 3;


void PrintMenu() {

	cout << "Type " << InsertItemCode << " Insert an itmeVL Tree" << endl;
	cout << "Type " << InsertItemCode << " to print the AVL Tree" << endl;
	cout << "Type " << InsertItemCode << " to Print the Menu." << endl;
	cout << "Type " << InsertItemCode << " To Exit the program." << endl;

}
void InValidOption() {
	cout << "Invalid option entered." << endl;
	PrintMenu();
}
void InsertTree() {
	cout << "Insert Item " << endl;

}

void PrintAVLTree() {
	cout << "PrintAVLTree" << endl;

}

int main()
{
	bool run = true;
	int option = -1;

	PrintMenu();
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