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

struct Node
{
	struct Node* prev;
	StudentInfo* info;
	struct Node* next;
};

typedef struct Node ListNode;

//useful info memory management
StudentInfo* createStudentInfo(const char*, double, unsigned short);
void* deleteStudentInfo(StudentInfo*);
void displayStudents(StudentInfo**, int);
void displayStudent(StudentInfo*);
ListNode* createNode(StudentInfo*);
ListNode* insertOnPosition(ListNode*, ListNode*, int);
void printList(ListNode*);


ListNode* insertOnOddPosition(ListNode* , ListNode* );
ListNode* insertOnEvenPosition(ListNode*, ListNode*);
ListNode* insertEnd(ListNode*, ListNode*);
ListNode* insertFront(ListNode*, ListNode*);
ListNode* filterBySalary(ListNode*);
void sortList(ListNode*);
void sortListByIncome(ListNode*);
void moveToList(ListNode*, StudentInfo**, int);
void displayStudentsArray(StudentInfo**, int);
int isPalindrome(ListNode*);



#define LINE_SIZE 128

void main()
{
	FILE* pFile = fopen("DoubleLinkedList.txt", "r");
	ListNode* doubleLinkedList = NULL;
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

			doubleLinkedList = insertOnPosition(doubleLinkedList, node, index);
			//moveToList(doubleLinkedList, agenda, index);

			agenda[index++] = stud;
		}
		//displayStudents(agenda, sizeof(agenda) / sizeof(StudentInfo*));
		StudentInfo* stud = createStudentInfo("Popa Maria", 3200.4, 39089);
		ListNode* node = createNode(stud);
		//insertOnPosition(doubleLinkedList, node, 3);
		printList(doubleLinkedList);

		//printf("\n ------Insert-On-Odd-Position-------- \n");
		//doubleLinkedList = insertOnOddPosition(doubleLinkedList, node);
		//printList(doubleLinkedList);

		/*printf("\n ------Insert-On-Even-Position-------- \n");
		doubleLinkedList = insertOnEvenPosition(doubleLinkedList, node);
		printList(doubleLinkedList);*/

		/*printf("\n ------Insert-Front-------- \n");
		doubleLinkedList = insertFront(doubleLinkedList, node);
		printList(doubleLinkedList);*/

		printf("\n ------Insert-End-------- \n");
		doubleLinkedList = insertEnd(doubleLinkedList, node);
		printList(doubleLinkedList);

		printf("\n Nodes with salary < 2000:\n");
		ListNode* filteredList = filterBySalary(doubleLinkedList);
		printList(filteredList);


		printf("\n ------Bubble-Sort-Names-------- \n");
		sortList(doubleLinkedList);
		printList(doubleLinkedList);

		printf("\n ------Income-Sort-------- \n");
		sortListByIncome(doubleLinkedList);
		printList(doubleLinkedList);

		//printf("\n ------Move-Nodes-To-Array-------- \n");
		
		//displayStudentsArray(agenda, index);

		int isPal = isPalindrome(doubleLinkedList);
		if (isPal == 1)
			printf("The linked list is a palindrome\n");
		else
			printf("The linked list is not a palindrome\n");

		fclose(pFile);
	}
}
void printList(ListNode* list)
{
	while (list->next)
	{
		displayStudent(list->info);
		list = list->next;
	}
	displayStudent(list->info);
	//here is the code to print the double linked list from front to end and then from end to front
	/*while (list)
	{
		displayStudent(list->info);
		list = list->prev;
	}*/
}

ListNode* insertOnPosition(ListNode* list, ListNode* node, int position)
{
	if (position <= 0)
	{
		if (list != NULL)
		{
			node->next = list;
			list->prev = node;
		}
		list = node;
	}
	else
	{
		ListNode* aux = list;
		int index = 0;
		while (aux->next != NULL && index < position - 1)
		{
			aux = aux->next;
			index++;
		}
		if (aux->next == NULL)
		{
			node->prev = aux;
			aux->next = node;
		}
		else
		{
			node->next = aux->next;
			node->prev = aux;
			aux->next->prev = node;
			aux->next = node;
		}
	}
	return list;
}

ListNode* createNode(StudentInfo* stud)
{
	ListNode* result = NULL;
	result = (ListNode*)malloc(sizeof(ListNode));
	result->info = stud;
	result->next = result->prev = NULL;
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

//inserting on oddPosition
ListNode* insertOnOddPosition(ListNode* list, ListNode* node)
{
	int position = 1;
	ListNode* aux = list;
	while (aux != NULL)
	{
		if (position % 2 == 1)
		{
			if (aux->prev != NULL)
			{
				node->prev = aux->prev;
				aux->prev->next = node;
			}
			else
			{
				list = node;
			}
			node->next = aux;
			aux->prev = node;
			return list;
		}
		position++;
		aux = aux->next;
	}
	if (position % 2 == 1)
	{
		if (aux->prev != NULL)
		{
			node->prev = aux->prev;
			aux->prev->next = node;
		}
		else
		{
			list = node;
		}
		node->next = aux;
		aux->prev = node;
	}
	else
	{
		printf("No odd position found!\n");
	}
	return list;
}

//function for inserting on the even position of the list
ListNode* insertOnEvenPosition(ListNode* list, ListNode* node)
{
	if (list == NULL)
	{
		list = node;
	}
	else
	{
		ListNode* aux = list;
		int index = 0;
		while (aux->next != NULL && index % 2 != 0)
		{
			aux = aux->next;
			index++;
		}
		if (aux->next == NULL && index % 2 != 0)
		{
			aux->next = node;
			node->prev = aux;
		}
		else
		{
			node->next = aux->next;
			node->prev = aux;
			aux->next->prev = node;
			aux->next = node;
		}
	}
	return list;
}

//function for inserting at the front of the list
ListNode* insertFront(ListNode* list, ListNode* node)
{
	if (list == NULL)
	{
		list = node;
	}
	else
	{
		node->next = list;
		list->prev = node;
		list = node;
	}
	return list;
}

//function for inserting at the back of the list
ListNode* insertEnd(ListNode* list, ListNode* node)
{
	if (list == NULL)
	{
		list = node;
	}
	else
	{
		ListNode* aux = list;
		while (aux->next != NULL)
		{
			aux = aux->next;
		}
		aux->next = node;
		node->prev = aux;
	}
	return list;
}


ListNode* filterBySalary(ListNode* list)
{
	ListNode* filteredList = NULL;
	ListNode* current = list;
	while (current)
	{
		if (current->info->income < 2000)
		{
			StudentInfo* stud = createStudentInfo(current->info->name, current->info->income, current->info->reference.extRef);
			ListNode* node = createNode(stud);
			filteredList = insertOnPosition(filteredList, node, 0);
		}
		current = current->next;
	}
	return filteredList;
}

//bubble sort
void sortList(ListNode* list) {
	int swapped;
	ListNode* ptr1;
	ListNode* lptr = NULL;

	/* Checking for empty list */
	if (list == NULL)
		return;

	do {
		swapped = 0;
		ptr1 = list;

		while (ptr1->next != lptr) {
			if (strcmp(ptr1->info->name, ptr1->next->info->name) > 0) {
				StudentInfo* temp = ptr1->info;
				ptr1->info = ptr1->next->info;
				ptr1->next->info = temp;
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	} while (swapped);
}

void sortListByIncome(ListNode* list)
{
	ListNode* i, * j;
	StudentInfo* temp;
	int swapped;

	if (list == NULL)
		return;

	i = list;
	do {
		swapped = 0;
		j = list;

		while (j->next != NULL) {
			if (j->info->income > j->next->info->income) {
				temp = j->info;
				j->info = j->next->info;
				j->next->info = temp;
				swapped = 1;
			}
			j = j->next;
		}
		i = i->next;
	} while (swapped);
}

//moving elements from list to an array
void moveToList(ListNode* list, StudentInfo** agenda, int noEl)
{
	int i = 0;
	while (list)
	{
		agenda[i++] = list->info;
		list = list->next;
	}
}

void displayStudentsArray(StudentInfo** agenda, int noEl)
{
	for (int i = 0; i < noEl; i++)
	{
		printf("Name: %s, income: %f\n", agenda[i]->name, agenda[i]->income);
		if (agenda[i]->reference.extRef >> 15 == 1)
		{
			short uid = agenda[i]->reference.extRef >> 8 & 127;
			printf("University ref: %d\n", uid);
			printf("External ref: %d\n", agenda[i]->reference.extRef & 255);
		}
		else
		{
			printf("Internal ref: %d\n", agenda[i]->reference.intRef);
		}
	}
}

int isPalindrome(ListNode* list)
{
	ListNode* start = list;
	ListNode* end = list;

	// move the end pointer to the last node
	while (end->next)
	{
		end = end->next;
	}

	// compare nodes from start and end
	while (start != end && end->next != start)
	{
		if (start->info->income != end->info->income)
		{
			return 0; // not a palindrome
		}
		start = start->next;
		end = end->prev;
	}

	return 1; // is a palindrome
}

//function from moving from a simple linked list into a double linked list
void moveNodesToDoubleLinkedList(ListNode** sourceList, ListNode** destList, int noNodesToMove)
{
	if (*sourceList == NULL || destList == NULL || noNodesToMove <= 0)
	{
		return;
	}

	ListNode* lastNode = *sourceList;

	while (lastNode->next != NULL)
	{
		lastNode = lastNode->next;
	}

	for (int i = 0; i < noNodesToMove; i++)
	{
		ListNode* nodeToMove = *sourceList;

		*sourceList = nodeToMove->next;
		nodeToMove->next = NULL;

		if (*destList == NULL)
		{
			*destList = nodeToMove;
			nodeToMove->prev = NULL;
		}
		else
		{
			lastNode->next = nodeToMove;
			nodeToMove->prev = lastNode;
		}

		lastNode = nodeToMove;
	}
}

//add on oddPosition --
//add on evenPosition --
//add on Front --
//add on Back --
//deallocation - deleting the whole structure --
//filtering --
//sorting based on one element --
//sorting after the whole node ??  --
//bubble sorting - this has complexity O(n) --
//move nodes from list to array 
//move nodes from array to list ?? 
//palindron 