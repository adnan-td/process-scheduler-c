#include "setup.c"

typedef struct Node
{
  Process data;
  struct Node *next;
} Node;

typedef struct
{
  Node *front;
  Node *rear;
} Queue;

void initqueue(Queue *queue)
{
  queue->front = NULL;
  queue->rear = NULL;
}

void enqueue(Queue *queue, Process process)
{
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == NULL)
  {
    printf("Memory allocation failed.\n");
    exit(1);
  }

  newNode->data = process;
  newNode->next = NULL;

  if (queue->rear == NULL)
  {
    queue->front = newNode;
    queue->rear = newNode;
  }
  else
  {
    queue->rear->next = newNode;
    queue->rear = newNode;
  }
}

Process dequeue(Queue *queue)
{
  if (queue->front == NULL)
  {
    printf("Queue is empty.\n");
    exit(1);
  }

  Node *temp = queue->front;
  Process dequeuedProcess = temp->data;

  queue->front = queue->front->next;
  if (queue->front == NULL)
  {
    queue->rear = NULL;
  }

  free(temp);
  return dequeuedProcess;
}

int isQueueEmpty(Queue *queue)
{
  return queue->front == NULL;
}
