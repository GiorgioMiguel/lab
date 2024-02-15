/*
COP 3502 SEC 0028 LAB ASSIGNMENT 4
© Giorgio Torregrosa 2/08/2024
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char letter;
	struct node* next;
} node;

// Returns number of nodes in the linkedList.
int length(node* head)
{
	int counter = 0;//intializing counter
	if (head == NULL) 
	{
		return 0;//returning 0 if the list is empty
	}
	node* tmp = head;//tmp point at head
	while (tmp != NULL) //while tmp is null traverse the list and incrment counter by 1
	{
		tmp = tmp->next;
		counter++;
	}
	return counter;
}

// parses the string in the linkedList
// if the linked list is head -> |a|->|b|->|c|
// then toCString function wil return "abc"
char* toCString(node* head)
{
	int size = length(head); //using the length functiong to grab the size of the list
	size++;//incrementing the size by 1 to account for the null terminator '\0'
	char* str = (char*)malloc(size*sizeof(char));//dynamically allocating memory
	if (!str) 
	{
		return;//if allocation fails return
	}
	node* tmp = head;//tmp pointer to head
	int i = 0;
	while (tmp != NULL)//while tmp is null 
	{
		str[i] = tmp->letter;//assigning letters to string
		tmp = tmp->next;
		i++;
	}
	str[i] = '\0';
	return str;
}

// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{
	node* newNode = (node*)malloc(sizeof(node));
	if (!newNode) 
	{
		return;//memory allocation fail
	}
	newNode->letter = c;//intializing new node
	newNode->next = NULL;
	if (*pHead == NULL) //if the list is empy make the new character the head first in the string
	{
		*pHead = newNode;
		return;
	}
	node* tmp = *pHead;
	while (tmp->next != NULL) //if the above condition didnt exit the function then there are nodes in the list and we need to find the last one.
	{
		tmp = tmp->next;
	}
	tmp->next = newNode;//once we found the last node we point it to our new node
}

// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
	if (*pHead == NULL)
	{
		return;//list empty nothing to delete
	}
	node* current = *pHead;
	node* tmp = *pHead;
	while (tmp != NULL)//classic traverse and delete with two different pointers
	{
		current = tmp->next;
		free(tmp);
		tmp = current;
		
	}
	*pHead = NULL;//make sure to avoid dangling pointers..
}

int main(void)
{
	int i, strLen, numInputs;
	node* head = NULL;
	char* str;
	char c;
	FILE* inFile = fopen("input.txt", "r");
	fscanf(inFile, " %d\n", &numInputs);
	while (numInputs-- > 0)
	{
		fscanf(inFile, " %d\n", &strLen);
		for (i = 0; i < strLen; i++)
		{
			fscanf(inFile, " %c", &c);
		insertChar(&head, c);
		}
		str = toCString(head);
		printf("String is : %s\n", str);
		free(str);
		deleteList(&head);
		if (head != NULL)
		{
			printf("deleteList is not correct!");
			break;
		}
	}
	fclose(inFile);
}