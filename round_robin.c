#include <stdio.h>
#include <stdbool.h>

// Structure to represent a process
struct Process {
    int pid;          // Process ID
    int arrival_time; // Arrival time
    int burst_time;   // Burst time
    int remaining_time; // Remaining burst time
    int completion_time; // Completion time
    int waiting_time;    // Waiting time
    int turnaround_time; // Turnaround time
    bool completed;      // Flag to check if process is completed
};

// Function to simulate Round Robin scheduling
void roundRobin(struct Process processes[], int n, int time_quantum) {
    int current_time = 0;
    int completed = 0;
    int current_process = -1;

    // Initialize remaining time and completion status for each process
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completed = false;
    }

    // Round Robin scheduling
    while (completed < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && !processes[i].completed) {
                int exec_time = (processes[i].remaining_time < time_quantum) ? processes[i].remaining_time : time_quantum;
                current_time += exec_time;
                processes[i].remaining_time -= exec_time;
                if (processes[i].remaining_time == 0) {
                    processes[i].completed = true;
                    processes[i].completion_time = current_time;
                    processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                    completed++;
                }
                found = true;
            }
        }
        if (!found) current_time++;
    }

    // Display results
    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
}

int main() {
    int n, time_quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
    }
    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    roundRobin(processes, n, time_quantum);
    return 0;
}

