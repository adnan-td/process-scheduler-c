#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"
#include "linkedlist.c"

#define MAX_PROCESS 10

int compareProcessesByName(const void *a, const void *b)
{
  const Process *processA = (const Process *)a;
  const Process *processB = (const Process *)b;

  return processA->name - processB->name;
}

int compareProcessesByAT(const void *a, const void *b)
{
  const Process *processA = (const Process *)a;
  const Process *processB = (const Process *)b;

  return processA->arrival_time - processB->arrival_time;
}

int compareProcessesByPriority(const void *a, const void *b)
{
  const Process *processA = (const Process *)a;
  const Process *processB = (const Process *)b;
  return processA->priority - processB->priority;
}

int compareProcessesByBT(const void *a, const void *b)
{
  const Process *processA = (const Process *)a;
  const Process *processB = (const Process *)b;
  return processA->burst_time - processB->burst_time;
}

void readProcessesFromFile(const char *filename, Process processes[], int *p, int *time_qt)
{
  FILE *file = fopen(filename, "r");
  if (file == NULL)
  {
    printf("Error opening file.\n");
    exit(1);
  }

  fscanf(file, "%d", p);
  fscanf(file, "%d", time_qt);
  if (*p > MAX_PROCESS)
  {
    printf("Exceeded maximum number of processes.\n");
    exit(1);
  }

  for (int i = 0; i < *p; i++)
  {
    fscanf(file, "%d %d %d %d", &processes[i].name, &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
    processes[i].remaining_bt = processes[i].burst_time;
  }

  fclose(file);
}

void calculateAverageTimes(Process processes[], int p, float *avg_tat, float *avg_wt)
{
  int total_tat = 0, total_wt = 0;

  for (int i = 0; i < p; i++)
  {
    total_tat += processes[i].tat;
    total_wt += processes[i].wt;
  }

  *avg_tat = (float)total_tat / p;
  *avg_wt = (float)total_wt / p;
}

void printGanttChart(LinkedListNode *head)
{
  printf("Gantt Chart:\n");

  LinkedListNode *current = head;
  while (current != NULL)
  {
    printf("| P%d\t", current->process.name);
    current = current->next;
  }
  printf("|");
  printf("\n");
  printf("%d\t", 0);
  current = head;
  while (current != NULL)
  {
    printf("%d\t", current->value);
    current = current->next;
  }
  printf("\n\n");
}

void printProcessTable(Process processes[], int p)
{
  printf("Process  \t BT \t AT \t Priority\n");
  for (int i = 0; i < p; i++)
  {
    printf("%d \t\t %d \t %d \t %d\n", processes[i].name, processes[i].burst_time, processes[i].arrival_time, processes[i].priority);
  }
  printf("\n");
}

void printProcessAfterTable(Process processes[], int p)
{
  qsort(processes, p, sizeof(Process), compareProcessesByName);
  printf("Process  \t WT \t TAT\n");
  for (int i = 0; i < p; i++)
  {
    printf("%d \t\t %d \t %d\n", processes[i].name, processes[i].wt, processes[i].tat);
  }
  printf("\n");
}