#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

struct book
{
	char* bookName;  //�ѦW�� key �Ӥ���j�p
	char* authors;
	int price;
};


template <typename T>
struct treeNodeTP
{
	T data;
	treeNodeTP* leftPtr;
	treeNodeTP* rightPtr;
};






//���int��Ƥj�p
int compareFun(int a, int b)
{
	if(a>b)
	{
		return -1;
	}else if(a<b)
	{
		return  1;
	}else
	{
		return 0;
	}
}


//���float��Ƥj�p
int compareFun(float a, float b)
{
	if (a > b)
	{
		return -1;
	}
	else if (a < b)
	{
		return  1;
	}
	else
	{
		return 0;
	}
}


int compareFun(book a, book b)
{
	if(strcmp(a.bookName,b.bookName)>0)
	{
		return -1;
	}else if (strcmp(a.bookName, b.bookName) < 0)
	{
		return 1;
	}else
	{
		return 0;
	}
}


inline void printFun(book a)
{
	cout<< "�ѦW: "<<a.bookName<< "\t�@��: " << a.authors<< "\t����: "<<a.price<<endl;
}
																	

void printFun(int a)
{
	cout << a << "  ";
}
void printFun(float a)
{
	cout << a << "  ";
}



template <typename T>
void insertNodeTP(treeNodeTP<T>* & tree, T input)
{
	
	
	if (tree == nullptr)
	{
		
		tree = (treeNodeTP<T>*)malloc(sizeof(treeNodeTP<T>));
		tree->data = input;
		tree->leftPtr = nullptr;
		tree->rightPtr = nullptr;
	}else
	{
		
		if(compareFun(input, tree->data)==-1)
		{
			insertNodeTP(tree->rightPtr, input);
		}else if(compareFun(input, tree->data) == 1)
		{
			insertNodeTP(tree->leftPtr, input);
		}else
		{
			cout << "same value has already been stored" << endl;
		}
	}
}



template<typename T>
void inOrderTP(treeNodeTP<T>* tree)
{
	if (tree != NULL) {
		inOrderTP(tree->leftPtr);
		printFun(tree->data);
		inOrderTP(tree->rightPtr);
	}
}

template<typename T>
void preOrderTP(treeNodeTP<T>* tree)
{
	if (tree != NULL) {
		printFun(tree->data);
		preOrderTP(tree->leftPtr);
		preOrderTP(tree->rightPtr);
	}
}



template<typename T>
void postOrderTP(treeNodeTP<T>* tree)
{
	if (tree != NULL) {	
		postOrderTP(tree->leftPtr);
		postOrderTP(tree->rightPtr);
		printFun(tree->data);
	}
}

template<typename T>
void reConnect(treeNodeTP<T>*& tree, treeNodeTP<T>*& connectPtr)
{
	if (tree == nullptr)
	{
		tree = (treeNodeTP<T>*)malloc(sizeof(treeNodeTP<T>));
		tree = connectPtr;
	}
	else
	{

		if (compareFun(connectPtr->data, tree->data) == -1)
		{
			reConnect(tree->rightPtr, connectPtr);
		}
		else if (compareFun(connectPtr->data, tree->data) == 1)
		{
			reConnect(tree->leftPtr, connectPtr);
		}
		else
		{
			cout << "same value has already been stored" << endl;
		}
	}
}

template <typename T>
treeNodeTP<T>* locateUpper(treeNodeTP<T>*& tree, T input)
{


	if (tree == nullptr)
	{

		return nullptr;
	}
	else
	{
		if(tree->rightPtr!=nullptr)
		{
			if(compareFun(input, tree->rightPtr->data)==0)
			{
				return tree;
			}
		}
		if (tree->leftPtr != nullptr)
		{
			if (compareFun(input, tree->leftPtr->data) == 0)
			{
				return tree;
			}
		}



		if (compareFun(input, tree->data) == -1)
		{
			locateUpper(tree->rightPtr, input);
		}
		else if (compareFun(input, tree->data) == 1)
		{
			locateUpper(tree->leftPtr, input);
		}
		
	}
}



template <typename T>
treeNodeTP<T>* locateNode(treeNodeTP<T>*& tree, T input)
{


	if (tree == nullptr)
	{

		return nullptr;
	}
	else
	{

		if (compareFun(input, tree->data) == -1)
		{
			locateNode(tree->rightPtr, input);
		}
		else if (compareFun(input, tree->data) == 1)
		{
			locateNode(tree->leftPtr, input);
		}
		else
		{
			return tree;
		}
	}
}

template<typename T>
int deleteNodeTP(treeNodeTP<T>*& treePtr, T keyToDelete) {


	treeNodeTP<T>* deleteNode = locateNode(treePtr, keyToDelete);
	if(deleteNode== nullptr)
	{
			cout << "not Found"<<endl;
			return 0;
	}
	
	cout << "�Y�N�R��:";
	printFun(deleteNode->data);


	treeNodeTP<T>* deleteUpper=locateUpper(treePtr, keyToDelete);

	if(deleteUpper==nullptr)
	{
		treePtr = deleteNode->rightPtr;
		if(deleteNode->rightPtr==NULL)
		{
			treePtr = deleteNode->leftPtr;
			free(deleteNode);
			return 1;
		}
		if (deleteNode->leftPtr != NULL)
		{
			reConnect(treePtr, deleteNode->leftPtr);
		}
		free(deleteNode);
		return 1;
	}else
	{
		//printFun(deleteUpper->data);
		if(deleteUpper->leftPtr==deleteNode)
		{
			deleteUpper->leftPtr = deleteNode->rightPtr;
			
			if(deleteNode->rightPtr==NULL)
			{
				deleteUpper->leftPtr = deleteNode->leftPtr;
				free(deleteNode);
				return 1;
			}
			if(deleteNode->leftPtr!=NULL)
			{
				reConnect(deleteUpper->leftPtr, deleteNode->leftPtr);
			}
			
			free(deleteNode);
			return 1;
			
		}
		if (deleteUpper->rightPtr == deleteNode)
		{
			deleteUpper->rightPtr = deleteNode->rightPtr;
			if (deleteNode->rightPtr == NULL)
			{
				deleteUpper->rightPtr = deleteNode->leftPtr;
				free(deleteNode);
				return 1;
			}
			if(deleteNode->leftPtr!=NULL)
			{
				reConnect(deleteUpper->rightPtr, deleteNode->leftPtr);
			}
			
			free(deleteNode);
			return 1;
		}
		
	}
	
		
		
		
	return 1;
	
}


template<typename T>
void doStuff(treeNodeTP<T>* &rootNode)
{
	int operation;
	while (true)
	{
		cout << "\n1.�s�W���\n2.�Ƨ�\n3.�R�����\n4.���}";
		cout << "\ninput your operation:";
		cin >> operation;
		getchar();
		if (operation == 1)
		{
			book insertBook;
			insertBook.bookName = new char[500];
			insertBook.authors = new char[500];

			cout << "�ninsert���ѦW:";
			fgets(insertBook.bookName, 500,  );
			strtok(insertBook.bookName, "\r\n");
			cout << "�ninsert���Ѫ��@��:";
			fgets(insertBook.authors, 500, stdin);
			strtok(insertBook.authors, "\r\n");

			cout << "�ninsert���Ѫ�����:";
			cin >> insertBook.price;
			getchar();
			insertNodeTP(rootNode, insertBook);


		}
		else if (operation == 2)
		{
			cout << "\n\tin order:" << endl;
			inOrderTP(rootNode);
			cout << "\n\tpre order:" << endl;
			preOrderTP(rootNode);
			cout << "\n\tpost order:" << endl;
			postOrderTP(rootNode);
			cout << endl;
		}
		else if (operation == 3)
		{
			book tempBook;
			tempBook.bookName = new char[500];
			cout << "�n�R�����ѦW:";
			fgets(tempBook.bookName, 500, stdin);
			strtok(tempBook.bookName, "\r\n");
			deleteNodeTP(rootNode, tempBook);
			
			
		}else if(operation==4)
		{
			break;
		}

	}
}



int main()
{
	treeNodeTP<book>* rootNode = nullptr;
	doStuff(rootNode);
	
}


/*
 ����:
1
��q���ǿ��ѧ޳N�G����ABBYY FineReader 11 OCR
�����q
371
1
VISUAL FORTRAN�{���]�p�P�}�o
�i�űj�B���E��
400
1
�{���]�p�Шϥ�C++
���خx
420
1
��Ʈw�t�Ρ�MTA�{�Ҽv���о�
���K��
336
1
���P�d�wGoogle���ݧ޳N�GMaps.Android.App Engine.Cloud SQL�P�q�l�Ӱ�API��ҸѪR
���@��
560
1
�H�u���z�G���z���t�ξɽ�(�ĤT��)
���p�� ��ҹ�w �¬F��
590
1
�q����������(�ĤG��)
�����s
420
1
���ں����P�q�l�Ӱ�(�ĤT��)
������
450
1
��Ʈw�t�βz�סШϥ�SQL Server 2008
���K��
650
1
�ʵe�ϸѸ�Ʈw�t�βz�סШϥ�Access 2010��@(�ĤG��)
���K��
600
 */