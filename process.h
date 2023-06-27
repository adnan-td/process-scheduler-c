#ifndef PROCESS_H
#define PROCESS_H

typedef struct
{
  int name;
  int arrival_time;
  int burst_time;
  int remaining_bt;
  int start_time;
  int priority;
  int tat;
  int wt;
} Process;

#endif