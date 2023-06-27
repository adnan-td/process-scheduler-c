#include "queue.c"

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
      current_time = cur.arrival_time;
    }
    else
    {
      while (!isQueueEmpty(&q) && (q.front->data.burst_time < cur.burst_time && q.front->data.arrival_time <= current_time))
      {
        Process frontProcess = dequeue(&q);
        frontProcess.start_time = current_time;
        frontProcess.wt = current_time - frontProcess.arrival_time;
        frontProcess.tat = frontProcess.wt + frontProcess.burst_time;
        current_time += frontProcess.burst_time;
        insertNode(&g, current_time, frontProcess);
      }
      cur.start_time = current_time;
      cur.wt = current_time - cur.arrival_time;
      cur.tat = cur.wt + cur.burst_time;
      current_time += cur.burst_time;
      processes[i] = cur;
      insertNode(&g, current_time, processes[i]);
    }
  }

  while (!isQueueEmpty(&q))
  {
    Process frontProcess = dequeue(&q);
    frontProcess.start_time = current_time;
    frontProcess.wt = current_time - frontProcess.arrival_time;
    frontProcess.tat = frontProcess.wt + frontProcess.burst_time;
    current_time += frontProcess.burst_time;
    insertNode(&g, current_time, frontProcess);
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

  calculateAverageTimes(processes, p, &avg_tat, &avg_wt);
  printGanttChart(g);
  printf("Average TAT  = %.2f\n", avg_tat);
  printf("Average WT   = %.2f\n", avg_wt);

  return 0;
}
