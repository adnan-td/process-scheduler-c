#include "queue.c"

int func(Process processes[], int index, Process cur, int current_time, LinkedListNode **g, Queue *q)
{
  cur.start_time = current_time;
  while (cur.remaining_bt--)
  {
    while (!isQueueEmpty(q) && (q->front->data.burst_time < cur.burst_time && q->front->data.arrival_time <= current_time))
    {
      insertNode(g, current_time, cur);
      Process p = dequeue(q);
      current_time = func(processes, p.name - 1, p, current_time, g, q);
    }
    current_time++;
  }
  cur.tat = current_time - cur.arrival_time;
  cur.wt = cur.tat - cur.burst_time;
  processes[index] = cur;
  insertNode(g, current_time, cur);
  return current_time;
}

LinkedListNode *calculateTimes(Process *processes, int p)
{
  qsort(processes, p, sizeof(Process), compareProcessesByBT);
  Queue q;
  initqueue(&q);

  int current_time = 0;
  LinkedListNode *g = NULL;

  for (int i = 0; i < p; i++)
  {
    Process cur = processes[i];

    if (current_time < cur.arrival_time)
    {
      enqueue(&q, cur);
    }
    else
    {
      while (!isQueueEmpty(&q) && (q.front->data.burst_time < cur.burst_time && q.front->data.arrival_time <= current_time))
      {
        Process p = dequeue(&q);
        current_time = func(processes, p.name - 1, p, current_time, &g, &q);
      }
      current_time = func(processes, i, cur, current_time, &g, &q);
    }
  }

  while (!isQueueEmpty(&q))
  {
    Process p = dequeue(&q);
    current_time = func(processes, p.name - 1, p, current_time, &g, &q);
  }

  return g;
}

int main()
{
  int p, time_qt;
  Process processes[MAX_PROCESS];
  float avg_tat, avg_wt;

  const char *filename = "question.txt";

  readProcessesFromFile(filename, processes, &p, &time_qt);
  printProcessTable(processes, p);

  LinkedListNode *g = calculateTimes(processes, p);
  printProcessAfterTable(processes, p);

  // displayList(g);
  calculateAverageTimes(processes, p, &avg_tat, &avg_wt);
  printGanttChart(g);
  printf("Average TAT  = %.2f\n", avg_tat);
  printf("Average WT   = %.2f\n", avg_wt);

  return 0;
}
