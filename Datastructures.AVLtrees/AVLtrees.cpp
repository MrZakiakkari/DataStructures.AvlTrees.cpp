#pragma once
#include <iostream>

using namespace std;

//typedef is needed to help shorten writing down enum
typedef enum { LeftHigher, EqualHeight, RightHigher } BalanceFactor;


template <class T>
struct AvlTreeNode
{

	T info;
	T root;
	BalanceFactor balanceFactor;
	AvlTreeNode* leftSubTree;
	AvlTreeNode* rightSubTree;
};


template <class T>
class AVLtree
{
public:
	AVLtree();
	~AVLtree();
	//	Methods
	void DeleteItem(T item);
	void InsertItem(T item);
	void PrintTree();
	void SearchItem(T item);
private:
	void BalanceLeft(AvlTreeNode<T>*& tree, bool& taller);
	void BalanceRight(AvlTreeNode<T>*& tree, bool& taller);
	void Delete(AvlTreeNode<T>*& tree, T item, bool& shorter);
	void DeleteNode(AvlTreeNode<T>*& tree, bool& shorter);
	void Insert(AvlTreeNode<T>*& tree, T item, bool& taller);
	void Print(AvlTreeNode<T>*& tree);
	void Search(AvlTreeNode<T>*& tree, T item);
	void RotateRight(AvlTreeNode<T>*& tree);
	void RotateLeft(AvlTreeNode<T>*& tree);
	//	Fields
	AvlTreeNode<T>* root;
};


bool Located = false;


template <class T>
AVLtree<T>::AVLtree()
{
	root = NULL;
}

template <class T>
AVLtree<T>::~AVLtree()
{

}

template<class T>
void AVLtree<T>::InsertItem(T item)
// Calls recursive function Insert to insert item into tree.
{
	bool taller;
	Insert(root, item, taller);
}


template<class T>
void AVLtree<T>::Insert(AvlTreeNode<T>*& tree, T item, bool& taller)
// Inserts item into tree.
// Post: item is in tree; search property is maintained
{
	if (tree == NULL)
	{	// Insertion place found.
		tree = new AvlTreeNode<T>;
		tree->leftSubTree = NULL;
		tree->rightSubTree = NULL;
		tree->info = item;
		tree->balanceFactor = EqualHeight;
		taller = true;
	}
	else if (item == tree->info)
		cerr << "Duplicate key is not allowed in AVL tree." << endl;
	else if (item < tree->info)
	{
		Insert(tree->leftSubTree, item, taller);
		// Insert into left subtree if (taller)	switch (tree->bf)
		{
			switch (tree->balanceFactor)
			{
			case LeftHigher: LeftBalance(tree, taller);	break;
			case EqualHeight: tree->balanceFactor = LeftHigher;	break;
			case RightHigher: tree->balanceFactor = EqualHeight;	taller = false; break;
			}

		}
	}

	else
	{
		Insert(tree->rightSubTree, item, taller);
		// Insert into right subtree if (taller)
		switch (tree->balanceFactor)
		{
		case RightHigher: RightBalance(tree, taller); break;
		case EqualHeight: tree->balanceFactor = RightHigher; break;
		case LeftHigher: tree->balanceFactor = EqualHeight; taller = false; break;
		}
	}
}

template<class T>
void AVLtree<T>::PrintTree()
{
	Print(root);
}

template<class T>
void AVLtree<T>::SearchItem(T item)
{
	Search(root, item);
}

template<class T>
void AVLtree<T>::Search(AvlTreeNode<T>*& tree, T item)
{

	if (tree != NULL)
	{
		if (item < tree->info)
		{
			Search(tree->leftSubTree, item);

		}
		else if (item > tree->info)
		{
			Search(tree->rightSubTree, item);
		}
		else
		{
			Located = true;
			cout << "\n\nName found in tree" << endl;
		}
	}
	else
	{
		cout << "\n\nName not found in Avl Tree" << endl;
	}
}

template<class T>
void AVLtree<T>::DeleteItem(T item)
// Calls recursive function Delete to delete item from tree.

{
	bool shorter;
	Delete(root, item, shorter);
	Located = false;

}

template <class T>
void AVLtree<T>::Delete(AvlTreeNode<T>*& tree, T item, bool& shorter)
{
	if (tree != NULL)
	{
		if (item < tree->info)
		{
			Delete(tree->leftSubTree, item, shorter);
			// Look in left subtree.
			if (shorter)
				switch (tree->balanceFactor)
				{
				case LeftHigher:
					tree->balanceFactor = EqualHeight;
					break;
				case EqualHeight:
					tree->balanceFactor = RightHigher;
					shorter = false;
					break;
				case RightHigher:
					DelRightBalance(tree, shorter);
					break;
				} // END SWITCH
		}
		else if (item > tree->info)
		{
			Delete(tree->rightSubTree, item, shorter);
			// Look in right subtree.
			if (shorter)
				switch (tree->balanceFactor)
				{
				case LeftHigher:
					DelLeftBalance(tree, shorter);
					break;
				case EqualHeight:
					tree->balanceFactor = LeftHigher;
					shorter = false;
					break;
				case RightHigher:
					tree->balanceFactor = EqualHeight;
					break;
				} // END SWITCH
		}
		else
			DeleteNode(tree, shorter);
		// Node found; call DeleteNode.
	} // END if (tree != NULL)
	else
	{
		cout << "\nNOTE: " << item
			<< " not in the tree so cannot be deleted.";
	}
	//cout << "Item Deleted" << endl;

}

template <class T>
void AVLtree<T>::DeleteNode(AvlTreeNode <T>*& tree, bool& shorter)
// Delete the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no longer in the tree. // If tree is a leaf node or has only one non-NULL child pointer, the node
// pointed to by tree is deleted; otherwise, the user's data is replaced by its
// logical predecessor and the predecessor's node is deleted.
{
	T data;
	AvlTreeNode <T>* tempPtr;
	tempPtr = tree;
	if (tree->leftSubTree == NULL)
	{
		tree = tree->rightSubTree;
		delete tempPtr;
		shorter = true;
	}
	else if (tree->rightSubTree == NULL)
	{
		tree = tree->leftSubTree;
		delete tempPtr;
		shorter = true;
	}
	else
	{
		GetPredecessor(tree, data);
		tree->info = data;
		Delete(tree->leftSubTree, data, shorter);
		// Delete the predecessor node
		if (shorter)
		{
			switch (tree->balanceFactor)
			{
			case LeftHigher:
				tree->balanceFactor = EqualHeight;
				break;
			case EqualHeight:
				tree->balanceFactor = RightHigher;
				shorter = false;
				break;
			case RightHigher:
				DelRightBalance(tree, shorter);
				break;
			}
		}
	}
}

template <class T>
void GetPredecessor(AvlTreeNode<T>* tree, T& data)
// Sets data to the info member of the right-most node in tree.
{
	tree = tree->leftSubTree;
	while (tree->rightSubTree != NULL)
		tree = tree->rightSubTree;
	data = tree->info;
}

template <class T>
void DelRightBalance(AvlTreeNode<T>*& tree, bool& shorter)
{
	AvlTreeNode<T>* rs = tree->rightSubTree;
	AvlTreeNode<T>* ls;
	switch (rs->balanceFactor)
	{
	case RightHigher:	tree->balanceFactor = rs->balanceFactor = EqualHeight;
		RotateLeft(tree);
		shorter = true; break;
	case EqualHeight:	tree->balanceFactor = RightHigher;
		rs->balanceFactor = LeftHigher;
		RotateLeft(tree);
		shorter = false; break;
	case LeftHigher:	ls = rs->leftSubTree;
		switch (ls->balanceFactor)
		{
		case RightHigher:	tree->balanceFactor = LeftHigher;
			rs->balanceFactor = EqualHeight; break;
		case EqualHeight:	tree->balanceFactor = rs->balanceFactor = EqualHeight;
			break;
		case LeftHigher:	tree->balanceFactor = EqualHeight;
			rs->balanceFactor = RightHigher; break;
		} // END SWITCH

		ls->balanceFactor = EqualHeight;
		RotateRight(tree->rightSubTree);
		RotateLeft(tree);
		shorter = true;
	}
}

template <class T>
void DelLeftBalance(AvlTreeNode<T>*& tree, bool& shorter)
{
	AvlTreeNode<T>* ls = tree->leftSubTree;
	AvlTreeNode<T>* rs;
	switch (ls->balanceFactor)
	{
	case LeftHigher:
		tree->balanceFactor = ls->balanceFactor = EqualHeight;
		RotateRight(tree);
		shorter = true; break;
	case EqualHeight:
		tree->balanceFactor = LeftHigher;
		ls->balanceFactor = RightHigher;
		RotateRight(tree);
		shorter = false; break;
	case RightHigher:
		rs = ls->rightSubTree;
		switch (rs->balanceFactor)
		{
		case LeftHigher:	tree->balanceFactor = RightHigher;
			ls->balanceFactor = EqualHeight; break;
		case EqualHeight:	tree->balanceFactor = ls->balanceFactor = EqualHeight;
			break;
		case RightHigher:	tree->balanceFactor = EqualHeight;
			ls->balanceFactor = LeftHigher; break;
		} // END SWITCH
		rs->balanceFactor = EqualHeight;
		RotateLeft(tree->leftSubTree);
		RotateRight(tree);
		ls->balanceFactor = EqualHeight;
		shorter = true;
	}
}

template<class T>
void AVLtree<T>::Print(AvlTreeNode<T>*& tree)
{
	string bf, left, right;
	//If tree is empty print empty tree
	if (tree == NULL)
		//cout << "  AVL tree is empty.\n  Please enter names to fill AVL Tree\n\n" << endl;
		return;
	else
	{

		Print(tree->leftSubTree);

		if (tree != NULL)
		{
			cout << "\n\t " << tree->info << ":";
		}


		if (tree->leftSubTree == NULL)
		{
			left = "NULL";
			cout << "\tLeft: " << left << "";
		}
		else
			cout << "\tLeft: " << tree->leftSubTree->info << " ";

		if (tree->rightSubTree == NULL)
		{
			right = "NULL";
			cout << "\tRight: " << right << "";
		}
		else
			cout << "\tRight: " << tree->rightSubTree->info << "  ";

		switch (tree->balanceFactor)
		{
		case 0: bf = "Left High "; break;
		case 1: bf = "Equal High "; break;
		case 2: bf = "Right High "; break;
		}
		cout << "\tBalance Factor: " << bf << "" << endl;

		Print(tree->rightSubTree);
	}

}

template<class T>
void AVLtree<T>::BalanceRight(AvlTreeNode<T>*& tree, bool& taller)
{
	AvlTreeNode<T>* rs = tree->rightSubTree;
	AvlTreeNode<T>* ls;

	switch (rs->balanceFactor)
	{
	case RightHigher:	tree->balanceFactor = rs->balanceFactor = EqualHeight;
		RotateLeft(tree);
		taller = false;
		break;

	case EqualHeight:
		cerr << "Tree already balanced " << endl;
		break;
	case LeftHigher:	ls = rs->leftSubTree;
		switch (ls->balanceFactor)
		{
		case RightHigher:	tree->balanceFactor = LeftHigher;
			rs->balanceFactor = EqualHeight;
			break;
		case EqualHeight:	tree->balanceFactor = rs->balanceFactor = EqualHeight;
			break;
		case LeftHigher:	tree->balanceFactor = EqualHeight;
			rs->balanceFactor = RightHigher;
			break;
		}

		ls->balanceFactor = EqualHeight;
		RotateRight(tree->rightSubTree);
		RotateLeft(tree);
		taller = false;
	}
}

template<class T>
void AVLtree<T>::BalanceLeft(AvlTreeNode<T>*& tree, bool& taller)
{
	AvlTreeNode<T>* ls = tree->leftSubTree;
	AvlTreeNode<T>* rs;

	switch (ls->balanceFactor)
	{
	case LeftHigher:
		tree->balanceFactor = ls->balanceFactor = EqualHeight;
		RotateRight(tree);
		taller = false;
		break;

	case EqualHeight:
		cerr << "Tree already balanced " << endl;
		break;
	case RightHigher:
		rs = ls->rightSubTree;
		switch (rs->balanceFactor)
		{
		case LeftHigher:
			tree->balanceFactor = RightHigher;
			ls->balanceFactor = EqualHeight;
			break;
		case EqualHeight:
			tree->balanceFactor = ls->balanceFactor = EqualHeight;
			break;
		case RightHigher:
			tree->balanceFactor = EqualHeight;
			ls->balanceFactor = LeftHigher;
			break;
		}

		rs->balanceFactor = EqualHeight;
		RotateLeft(tree->leftSubTree);
		RotateRight(tree);
		taller = false;
	}
}

template<class T>
void RotateRight(AvlTreeNode<T>*& tree)
{
	AvlTreeNode<T>* ls;
	if (tree == NULL)
		cerr << "It is impossible to rotate an empty tree in RotateRight" << endl;
	else if (tree->leftSubTree == NULL)
		cerr << "It is impossible to make an empty subtree the root in RotateRight" << endl;
	else
	{
		ls = tree->leftSubTree;
		tree->leftSubTree = ls->rightSubTree;
		ls->rightSubTree = tree;
		tree = ls;
	}
}

template<class T>
void RotateLeft(AvlTreeNode<T>*& tree)
{
	AvlTreeNode<T>* rs;
	if (tree == NULL)
		cerr << "It is impossible to rotate an empty tree in RotateLeft" << endl;
	else if (tree->rightSubTree == NULL)
		cerr << "It is impossible to make an empty subtree the root in RotateLeft" << endl;
	else
	{
		rs = tree->rightSubTree;
		tree->rightSubTree = rs->leftSubTree;
		rs->leftSubTree = tree;
		tree = rs;
	}
}