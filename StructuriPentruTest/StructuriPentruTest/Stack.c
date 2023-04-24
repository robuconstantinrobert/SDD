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

typedef struct Node Stack;



//useful info memory management
StudentInfo* createStudentInfo(const char*, double, unsigned short);
void* deleteStudentInfo(StudentInfo*);
void displayStudents(StudentInfo**, int);
void displayStudent(StudentInfo*);
Stack* createNode(StudentInfo*);
Stack* pushNode(Stack*, Stack*);
StudentInfo* peekNode(Stack*);
Stack* popNode(Stack**);
void clearStack(Stack**);
Stack* findNodeByName(Stack*, const char*);
void stackToArray(Stack*, StudentInfo**, int);
#define LINE_SIZE 128

void main()
{
	FILE* pFile = fopen("Stack.txt", "r");
	Stack* circularDoubleLinkedList = NULL;
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
			Stack* node = createNode(stud);
			circularDoubleLinkedList = pushNode(circularDoubleLinkedList, node);
			
			agenda[index++] = stud;
		}
		StudentInfo* stud = peekNode(circularDoubleLinkedList);
		displayStudent(stud);
		//Stack* node = popNode(&circularDoubleLinkedList);
		//displayStudent(node->info);

		//clearStack(&circularDoubleLinkedList);
		displayStudents(agenda, sizeof(agenda) / sizeof(StudentInfo*));
		
		Stack* result = findNodeByName(circularDoubleLinkedList, "Popescu Maria");
		if (result != NULL)
		{
			displayStudent(result->info);
		}
		else
		{
			printf("Student not found\n");
		}
		StudentInfo* array[3];
		stackToArray(circularDoubleLinkedList, array, 3);
		for (int i = 0; i < 3; i++) {
			
			printf(" \n Name: %s, Age: %f, GPA: %.2d\n", array[i]->name, array[i]->income, array[i]->reference);
		}
		fclose(pFile);
	}
}

void clearStack(Stack** stack)
{
	Stack* node = NULL;
	while ((node = popNode(stack)) != NULL)
	{
		displayStudent(node->info);
		free(node->info->name);
		free(node->info);
		free(node);
	}
}

Stack* popNode(Stack** stack)
{
	Stack* result = NULL;
	if (*stack != NULL)
	{
		result = *stack;
		if ((*stack)->prev == (*stack))
		{
			*stack = NULL;
		}
		else
		{
			(*stack)->next->prev = (*stack)->prev;
			(*stack)->prev->next = (*stack)->next;
			(*stack) = (*stack)->next;
		}
	}
	return result;
}

StudentInfo* peekNode(Stack* stack)
{
	StudentInfo* result = NULL;
	if (stack != NULL)
	{
		result = stack->info;
	}
	return result;
}
Stack* pushNode(Stack* stack, Stack* node)
{
	if (stack == NULL)
	{
		node->next = node->prev = node;
		return node;
	}
	node->next = stack;
	node->prev = stack->prev;
	stack->prev->next = node;
	stack->prev = node;
	return node;
}

Stack* createNode(StudentInfo* stud)
{
	Stack* result = NULL;
	result = (Stack*)malloc(sizeof(Stack));
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

//search function searching by name
Stack* findNodeByName(Stack* stack, const char* name)
{
	Stack* current = stack;
	while (current != NULL)
	{
		if (strcmp(current->info->name, name) == 0)
		{
			return current;
		}
		current = current->next;
		if (current == stack)
		{
			break;
		}
	}
	return NULL;
}

//move stack nodes to array
void stackToArray(Stack* stack, StudentInfo** array, int size)
{
	if (stack == NULL || array == NULL)
	{
		return;
	}
	Stack* current = stack;
	for (int i = 0; i < size; i++)
	{
		if (current == NULL)
		{
			break;
		}
		array[i] = current->info;
		current = current->next;
	}
}