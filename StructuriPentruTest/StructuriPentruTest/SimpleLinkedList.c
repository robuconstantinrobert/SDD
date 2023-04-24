#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

union Reference
{
	unsigned char intRef;
	unsigned short extRef;
};

typedef union Reference RefInfo;

struct Student
{
	char* name;
	double income;
	RefInfo reference;
};

typedef struct Student StudentInfo;

//node for simple linked list
struct Node 
{
	StudentInfo* info;
	struct Node* next;
};

typedef struct Node ListNode;

//useful info memory management
StudentInfo* createStudentInfo(const char*, double, unsigned short);
void* deleteStudentInfo(StudentInfo*);
void displayStudents(StudentInfo**, int);
void displayStudent(StudentInfo*);



//functions for simple linked list
ListNode* createNode(StudentInfo*);
void insertNode(ListNode**, ListNode*);
ListNode* insertOnPosition(ListNode*, ListNode*, int);
void printList(ListNode*);
void insertEvenReference(ListNode**, ListNode*);
void insertOddReference(ListNode**, ListNode*);
void insertAtHead(ListNode** , ListNode* );
void insertAtEnd(ListNode**, ListNode*);
ListNode* filterByName(ListNode*, const char*);
void sortByInitial(ListNode**);
void sortListByIncome(ListNode**);
void swapNodes(ListNode*, ListNode*);
void moveNodesToArray(ListNode*, StudentInfo**, int);
void insertFromArray(ListNode**, StudentInfo*, int);
void bubbleSort(ListNode* );
int isPalindrome(ListNode*);
ListNode* reverseList(ListNode*);
ListNode* insertOnOddPosition(ListNode*, ListNode*, int);
ListNode* insertOnEvenPosition(ListNode*, ListNode*);


#define LINE_SIZE 128

void main()
{
	FILE* pFile = fopen("SimpleLinkedList.txt", "r");
	ListNode* simpleLinkedList = NULL;
	if (pFile)
	{
		StudentInfo* agenda[10];
		memset(agenda, 0, sizeof(agenda));
		char* token; char delimiter[] = ",\n";
		double income; unsigned short ref;
		char lineBuffer[LINE_SIZE], name[LINE_SIZE];
		int index = 0;
		while (fgets(lineBuffer, sizeof(lineBuffer), pFile))
		{
			token = strtok(lineBuffer, delimiter);
			strcpy(name, token);
			token = strtok(NULL, delimiter);
			income = atof(token);
			token = strtok(NULL, delimiter);
			ref = atoi(token);

			StudentInfo* stud = createStudentInfo(name, income, ref);
			ListNode* node = createNode(stud);
			insertNode(&simpleLinkedList, node);
			//insertEvenReference(&simpleLinkedList, node);
			//insertOddReference(&simpleLinkedList, node);
			
			

			agenda[index++] = stud;

			

		}
		//displayStudents(agenda, sizeof(agenda) / sizeof(StudentInfo*));



		printf("\n -------Bubble-Sorting------- \n");
		bubbleSort(simpleLinkedList);
		printList(simpleLinkedList);


		StudentInfo* info = createStudentInfo("Popescu Eugen", 1300.34, 38767);
		ListNode* node = createNode(info);
		int position = 78;
		simpleLinkedList = insertOnPosition(simpleLinkedList, node, position);

		StudentInfo* info2 = createStudentInfo("Alexandru Alexandru", 1600.34, 34);
		ListNode* node2 = createNode(info2);
		//insertAtHead(&simpleLinkedList, node2);
		insertAtEnd(&simpleLinkedList, node2);

		ListNode* filteredList = filterByName(simpleLinkedList, "Popescu Eugen");


		printList(simpleLinkedList);
		printf("\n ----------------------- \n");
		printList(filteredList);

		printf("\n ----------------------- \n");
		sortByInitial(&simpleLinkedList);
		printList(simpleLinkedList);

		printf("\n ----------------------- \n");
		sortListByIncome(&simpleLinkedList);
		printList(simpleLinkedList);

		printf("\n -------List-To-Array------- \n");
		int size = countList(simpleLinkedList);
		StudentInfo** studentsArray = (StudentInfo**)malloc(size * sizeof(StudentInfo*));
		moveNodesToArray(simpleLinkedList, studentsArray, size);
		displayStudents(studentsArray, size);


		printf("\n -------Array-To-List------- \n");
		StudentInfo newArray[] = {
		{ "Jhon Doe", 1500.0, {10} }, { "Jane Smith", 2000.0, {20}}
		};
		int ArraySize = sizeof(newArray) / sizeof(StudentInfo);
		insertFromArray(&simpleLinkedList, newArray, ArraySize);
		printList(simpleLinkedList);

		
		printf("\n -------Check-Palindrome------- \n");
		int isPal = isPalindrome(simpleLinkedList);
		if (isPal == 1) {
			printf("The linked list is a palindrome.\n");
		}
		else {
			printf("The linked list is not a palindrome.\n");
		}

		printf("\n -------Odd-Position-------- \n");
		StudentInfo* info3 = createStudentInfo("Popescu Marian", 1900.34, 38737);
		ListNode* node3 = createNode(info3);
		int position2 = 77;
		simpleLinkedList = insertOnOddPosition(simpleLinkedList, node3, position2);
		printList(simpleLinkedList);
		fclose(pFile);

		printf("\n -------Even-Position-------- \n");
		StudentInfo* info4 = createStudentInfo("John Jhon", 2000.0, 12345);
		ListNode* node4 = createNode(info4);
		simpleLinkedList = insertOnEvenPosition(simpleLinkedList, node4);
		printList(simpleLinkedList);
	}
}


ListNode* insertOnPosition(ListNode* list, ListNode* node, int index) 
{
	if (index == 1) 
	{
		node->next = list;
		return node;
	}

	int i = 1;
	ListNode* aux = list;
	while (aux->next && i < index - 1) 
	{
		i++;
		aux = aux->next;
	}
	if (aux->next == NULL) 
	{
		aux->next = node;
	}
	else 
	{
		node->next = aux->next;
		aux->next = node;
	}
	return list;
}

void printList(ListNode* list) 
{
	while (list) 
	{
		displayStudent(list->info);
		list = list->next;
	}
}

void insertNode(ListNode** list, ListNode* node) 
{
	//insert at head if the list is empty
	if (*list == NULL) 
	{
		*list = node;
	}
	//insert at the end where next is NULL
	else 
	{
		ListNode* aux = *list;
		while (aux->next) 
		{
			aux = aux->next;
		}
		aux->next = node;
	}
}

ListNode* createNode(StudentInfo* stud) 
{
	ListNode* result = NULL;
	result = (ListNode*)malloc(sizeof(ListNode));
	result->info = stud;
	result->next = NULL;
	return result;
}


void displayStudent(StudentInfo* stud)
{
	if (stud)
	{
		printf("Name: %s, income: %f\n", stud->name, stud->income);
		if (stud->reference.extRef >> 15 == 1)
		{
			short uid = stud->reference.extRef >> 8 & 127;
			printf("University ref: %d\n", uid);
			printf("External ref: %d\n", stud->reference.extRef & 255);
		}
		else
		{
			printf("Internal ref: %d\n", stud->reference.intRef);
		}
	}
}
void displayStudents(StudentInfo** agenda, int noEl)
{
	for (int i = 0; i < noEl; i++)
	{
		displayStudent(agenda[i]);
	}
}
void* deleteStudentInfo(StudentInfo* stud)
{
	if (stud != NULL)
	{
		free(stud->name);
		free(stud);
	}
	return NULL;
}

StudentInfo* createStudentInfo(const char* name, double income, unsigned short ref)
{
	StudentInfo* result = NULL;

	result = (StudentInfo*)malloc(sizeof(StudentInfo));
	result->name = (char*)malloc(strlen(name) + 1);
	strcpy(result->name, name);
	result->income = income;
	result->reference.extRef = ref;
	return result;

}

//add a node that has an odd internal reference and external reference
void insertOddReference(ListNode** list, ListNode* node) {
	// check if the internal and external references of the student are odd
	if (node->info->reference.intRef % 2 == 0 || node->info->reference.extRef % 2 == 0) {
		// skip insertion if either reference is even
		deleteStudentInfo(node->info);
		free(node);
		return;
	}

	// insert at head if the list is empty
	if (*list == NULL) {
		*list = node;
	}
	// insert at the end where next is NULL
	else {
		ListNode* aux = *list;
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = node;
	}
}

//add a node that has an even internal reference and external reference
void insertEvenReference(ListNode** list, ListNode* node)
{
	// check if the internal reference of the student is even
	if (node->info->reference.intRef % 2 != 0)
	{
		// skip insertion if the internal reference is odd
		deleteStudentInfo(node->info);
		free(node);
		return;
	}

	// check if the external reference of the student is even
	if (node->info->reference.extRef % 2 != 0)
	{
		// skip insertion if the external reference is odd
		deleteStudentInfo(node->info);
		free(node);
		return;
	}

	// insert at head if the list is empty
	if (*list == NULL)
	{
		*list = node;
	}
	// insert at the end where next is NULL
	else
	{
		ListNode* aux = *list;
		while (aux->next)
		{
			aux = aux->next;
		}
		aux->next = node;
	}
}

//add a node at the front
void insertAtHead(ListNode** list, ListNode* node) 
{
	node->next = *list;
	*list = node;
}

//add a node at the end of the list
void insertAtEnd(ListNode** list, ListNode* node) 
{
	ListNode* aux = *list;
	while (aux->next)
	{
		aux = aux->next;
	}
	aux->next = node;
}

//filtering the list based on the name
ListNode* filterByName(ListNode* list, const char* name)
{
	ListNode* filteredList = NULL;
	while (list != NULL)
	{
		if (strcmp(list->info->name, name) == 0)
		{
			ListNode* newNode = createNode(list->info);
			insertNode(&filteredList, newNode);
		}
		list = list->next;
	}
	return filteredList;
}

//sorting the list based on the initial of the last name of the student
void sortByInitial(ListNode** list)
{
	int swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ListNode* current = *list;
		while (current->next != NULL)
		{
			if (strcmp(current->info->name, current->next->info->name) > 0)
			{
				// swap nodes
				StudentInfo* temp = current->info;
				current->info = current->next->info;
				current->next->info = temp;
				swapped = 1;
			}
			current = current->next;
		}
	}
}

//function for sorting the list based on the income
void sortListByIncome(ListNode** list)
{
	int swapped, i;
	ListNode* ptr1;
	ListNode* lptr = NULL;

	/* Checking for empty list */
	if (*list == NULL)
		return;

	do
	{
		swapped = 0;
		ptr1 = *list;

		while (ptr1->next != lptr)
		{
			if (ptr1->info->income > ptr1->next->info->income)
			{
				swapNodes(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	} while (swapped);
}

//function for swapping two nodes
void swapNodes(ListNode* a, ListNode* b)
{
	StudentInfo* temp = a->info;
	a->info = b->info;
	b->info = temp;
}

//move nodes from list into array
void moveNodesToArray(ListNode* list, StudentInfo** agenda, int size) {
	int i = 0;
	while (list && i < size) {
		agenda[i++] = list->info;
		list = list->next;
	}
}

int countList(ListNode* list) 
{
	int index = 0;
	ListNode* temp = list;
	while (temp != NULL) 
	{
		temp = temp->next;
		index++;
	}
	return index;
}

void insertFromArray(ListNode** list, StudentInfo* array, int size) {
	for (int i = 0; i < size; i++) {
		ListNode* node = createNode(&array[i]);
		insertNode(list, node);
	}
}


//insertion O(log n)
void insertNodeBinarySearchComplexity(ListNode** list, ListNode* node)
{
	ListNode* curr = *list;
	ListNode* prev = NULL;

	while (curr && node->info->income > curr->info->income) {
		prev = curr;
		curr = curr->next;
	}

	if (prev == NULL) {
		node->next = *list;
		*list = node;
	}
	else {
		node->next = prev->next;
		prev->next = node;
	}
}

//Bubble sorting
void bubbleSort(ListNode* list)
{
	int swapped;
	ListNode* ptr1;
	ListNode* lptr = NULL;

	/* Checking for empty list */
	if (list == NULL)
		return;

	do
	{
		swapped = 0;
		ptr1 = list;

		while (ptr1->next != lptr)
		{
			if (strcmp(ptr1->info->name, ptr1->next->info->name) > 0)
			{
				swapNodes(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	} while (swapped);
}

//function to check if my simple linked list is a palindrome
int isPalindrome(ListNode* head) {
	if (head == NULL || head->next == NULL) {
		return 1;
	}
	ListNode* slow = head;
	ListNode* fast = head;
	while (fast->next != NULL && fast->next->next != NULL) {
		slow = slow->next;
		fast = fast->next->next;
	}
	slow->next = reverseList(slow->next);
	slow = slow->next;
	while (slow != NULL) {
		if (head->info->income != slow->info->income) {
			return 0;
		}
		head = head->next;
		slow = slow->next;
	}
	return 1;
}

//function for reversing the list
ListNode* reverseList(ListNode* head) {
	ListNode* prev = NULL;
	ListNode* curr = head;
	ListNode* next;
	while (curr != NULL) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	return prev;
}


ListNode* insertOnOddPosition(ListNode* list, ListNode* node, int index)
{
	if (index == 1)
	{
		node->next = list;
		return node;
	}
	int i = 1;
	ListNode* aux = list;
	while (aux->next && i < index - 1)
	{
		i++;
		aux = aux->next;
	}
	if (aux->next == NULL)
	{
		aux->next = node;
	}
	else
	{
		if (i % 2 == 1) // add on odd position
		{
			node->next = aux->next;
			aux->next = node;
		}
		else // add on even position
		{
			node->next = aux->next->next;
			aux->next->next = node;
		}
	}
	return list;
}

ListNode* insertOnEvenPosition(ListNode* list, ListNode* node)
{
	ListNode* aux = list;
	int position = 1;

	while (aux != NULL && position % 2 == 0) {
		aux = aux->next;
		position++;
	}

	if (aux == NULL) {
		// The list has less than 2 nodes, insert at the end
		insertNode(&list, node);
	}
	else {
		list = insertOnPosition(list, node, position);
	}

	return list;
}












////Searching with O(log n) complexity
//int search(struct Node* head, int value) {
//	struct Node* current = head;
//	while (current != NULL) {
//		if (current->info == value) {
//			return 1; // element found
//		}
//		else if (current->info < value) {
//			//current = current->right; // go to right subtree
//		}
//		else {
//			//current = current->left; // go to left subtree
//		}
//	}
//	return 0; // element not found
//}
//
////deleting using O(log n) Complexity
//struct Node* deleteNode(struct Node* root, int key) {
//	// base case
//	if (root == NULL) {
//		return root;
//	}
//	// if the key to be deleted is smaller than the root's key,
//	// then it lies in left subtree
//	if (key < root->data) {
//		root->left = deleteNode(root->left, key);
//	}
//	// if the key to be deleted is greater than the root's key,
//	// then it lies in right subtree
//	else if (key > root->data) {
//		root->right = deleteNode(root->right, key);
//	}
//	// if key is same as root's key, then this is the node
//	// to be deleted
//	else {
//		// node with only one child or no child
//		if (root->left == NULL) {
//			struct Node* temp = root->right;
//			free(root);
//			return temp;
//		}
//		else if (root->right == NULL) {
//			struct Node* temp = root->left;
//			free(root);
//			return temp;
//		}
//		// node with two children: Get the inorder successor
//		// (smallest in the right subtree)
//		struct Node* temp = minValueNode(root->right);
//		// copy the inorder successor's content to this node
//		root->data = temp->data;
//		// delete the inorder successor
//		root->right = deleteNode(root->right, temp->data);
//	}
//	return root;
//}

//functions:
//createNode
//insertNode
//insertOnPosition
//printList

//add on oddPosition --
//add on evenPosition --
//add on Front --
//add on Back --
//deallocation - deleting the whole structure --
//filtering -- 
//sorting based on one element --
//sorting after the whole node ?? --
//bubble sorting - this has complexity O(n)
//move nodes from list to array -- 
//move nodes from array to list ?? --
//palindron --


//Linked List Complexity
//Search O(n), Insert O(1), Delete O(1)
// 
// 
//Constant Time Complexity - O(1)
//Logarithmic Time Complexity - O(log n)
//Linear Time Complexity - O(n) -> 
//O(n log n) Time Complexity. -> priority queue
//Quadratic Time Complexity - O(n2) -- 