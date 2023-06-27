#include "stdio.h"
#include "process.h"

typedef struct LinkedListNode
{
  int value;
  Process process;
  struct LinkedListNode *next;
} LinkedListNode;

LinkedListNode *createNode(int value, Process process)
{
  LinkedListNode *node = (LinkedListNode *)malloc(sizeof(LinkedListNode));
  if (node == NULL)
  {
    printf("Memory allocation failed.\n");
    exit(1);
  }

  node->value = value;
  node->process = process;
  node->next = NULL;

  return node;
}

void insertNode(LinkedListNode **head, int value, Process process)
{
  LinkedListNode *newNode = createNode(value, process);

  if (*head == NULL)
  {
    *head = newNode;
  }
  else
  {
    LinkedListNode *current = *head;
    while (current->next != NULL)
    {
      current = current->next;
    }
    current->next = newNode;
  }
}

void displayList(LinkedListNode *head)
{
  LinkedListNode *current = head;

  while (current != NULL)
  {
    printf("Value: %d\n", current->value);
    // Access process members
    printf("Process Name: %d\n", current->process.name);
    printf("Arrival Time: %d\n", current->process.arrival_time);
    printf("Burst Time: %d\n", current->process.burst_time);
    printf("Remaining BT: %d\n", current->process.remaining_bt);
    printf("Start Time: %d\n", current->process.start_time);
    printf("Priority: %d\n", current->process.priority);
    printf("TAT: %d\n", current->process.tat);
    printf("WT: %d\n", current->process.wt);
    printf("\n");

    current = current->next;
  }
}

void freeList(LinkedListNode *head)
{
  LinkedListNode *current = head;
  LinkedListNode *next;

  while (current != NULL)
  {
    next = current->next;
    free(current);
    current = next;
  }
}
