#include "queue.c"

int func(Process processes[], int index, Process cur, int current_time, LinkedListNode **g, Queue *q, int time_qt)
{
  int n = time_qt;
  while (n--)
  {
    if (cur.remaining_bt <= 0)
    {
      break;
    }
    current_time++;
    cur.remaining_bt--;
  }
  if (cur.remaining_bt <= 0)
  {
    cur.tat = current_time - cur.arrival_time;
    cur.wt = cur.tat - cur.burst_time;
  }
  else
  {
    cur.start_time = current_time;
    enqueue(q, cur);
  }
  processes[index] = cur;
  insertNode(g, current_time, cur);
  return current_time;
}

LinkedListNode *calculateTimes(Process *processes, int p, int time_qt)
{
  qsort(processes, p, sizeof(Process), compareProcessesByPriority);
  Queue q;
  initqueue(&q);

  int current_time = 0;
  LinkedListNode *g = NULL;

  for (int i = 0; i < p; i++)
  {
    Process cur = processes[i];

    if (current_time < cur.arrival_time)
    {
      cur.start_time = cur.arrival_time;
      enqueue(&q, cur);
    }
    else
    {
      current_time = func(processes, i, cur, current_time, &g, &q, time_qt);
      while (!isQueueEmpty(&q) && (q.front->data.start_time <= current_time))
      {
        if (i + 1 < p && q.front->data.start_time >= processes[i + 1].arrival_time)
          break;
        Process p = dequeue(&q);
        current_time = func(processes, p.name - 1, p, current_time, &g, &q, time_qt);
      }
    }
  }

  while (!isQueueEmpty(&q))
  {
    Process p = dequeue(&q);
    current_time = func(processes, p.name - 1, p, current_time, &g, &q, time_qt);
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

  LinkedListNode *g = calculateTimes(processes, p, time_qt);
  printProcessAfterTable(processes, p);

  calculateAverageTimes(processes, p, &avg_tat, &avg_wt);
  printGanttChart(g);
  printf("Average TAT  = %.2f\n", avg_tat);
  printf("Average WT   = %.2f\n", avg_wt);

  return 0;
}
