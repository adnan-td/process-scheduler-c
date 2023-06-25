#include "queue.c"

void calculateTimes(Process *processes, int p)
{
  qsort(processes, p, sizeof(Process), compareProcessesByAT);
  int current_time = 0;

  for (int i = 0; i < p; i++)
  {
    processes[i].start_time = current_time;
    processes[i].wt = current_time - processes[i].arrival_time;
    processes[i].tat = processes[i].wt + processes[i].burst_time;

    current_time += processes[i].burst_time;
  }
}

int main()
{
  int p, time_qt;
  Process processes[MAX_PROCESS];
  float avg_tat, avg_wt;

  const char *filename = "question.txt";

  readProcessesFromFile(filename, processes, &p, &time_qt);
  printProcessTable(processes, p);

  printProcessAfterTable(processes, p);
  calculateTimes(processes, p);
  printProcessAfterTable(processes, p);

  calculateAverageTimes(processes, p, &avg_tat, &avg_wt);
  printGanttChart(processes, p);
  printf("Average TAT  = %.2f\n", avg_tat);
  printf("Average WT   = %.2f\n", avg_wt);

  return 0;
}
