#include <stdio.h>
#include <stdbool.h>

// Structure to represent a process
struct Process {
    int pid;          // Process ID
    int arrival_time; // Arrival time
    int burst_time;   // Burst time
    int start_time;   // Start time of execution
    int completion_time; // Completion time
    int waiting_time;    // Waiting time
    int turnaround_time; // Turnaround time
    bool executed;       // Flag to check if process is executed
};

// Function to find the process with minimum burst time among arrived processes
int findShortestJob(struct Process processes[], int n, int current_time) {
    int min_index = -1;
    int min_burst = 9999;
    
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= current_time && !processes[i].executed) {
            if (processes[i].burst_time < min_burst) {
                min_burst = processes[i].burst_time;
                min_index = i;
            }
        }
    }
    
    return min_index;
}

// Function to calculate waiting time and turnaround time
void calculateTimes(struct Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    
    // Initialize all processes as not executed
    for (int i = 0; i < n; i++) {
        processes[i].executed = false;
    }
    
    // Process until all processes are completed
    while (completed < n) {
        int shortest_job = findShortestJob(processes, n, current_time);
        
        if (shortest_job == -1) {
            // No process available at current time
            current_time++;
            continue;
        }
        
        // Update process details
        processes[shortest_job].start_time = current_time;
        processes[shortest_job].completion_time = current_time + processes[shortest_job].burst_time;
        processes[shortest_job].turnaround_time = processes[shortest_job].completion_time - processes[shortest_job].arrival_time;
        processes[shortest_job].waiting_time = processes[shortest_job].turnaround_time - processes[shortest_job].burst_time;
        processes[shortest_job].executed = true;
        

        
        // Update current time
        current_time = processes[shortest_job].completion_time;
        completed++;
    }
    

    
    // Calculate average times
    float total_waiting_time = 0, total_turnaround_time = 0;
    
    printf("\n+----------+-------------+-----------+-------------+----------------+\n");
    printf("| Process  | Arrival Time| Burst Time| Waiting Time| Turnaround Time|\n");
    printf("+----------+-------------+-----------+-------------+----------------+\n");
    
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
        printf("| P%-7d | %-11d | %-9d | %-11d | %-14d |\n", 
               processes[i].pid, processes[i].arrival_time, processes[i].burst_time, 
               processes[i].waiting_time, processes[i].turnaround_time);
    }
    
    printf("+----------+-------------+-----------+-------------+----------------+\n");
    printf("Average waiting time = %.2f\n", total_waiting_time / n);
    printf("Average turnaround time = %.2f\n", total_turnaround_time / n);
    
    printf("\n");
}

int main() {
    int n;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process processes[n];
    
    printf("\nEnter process details:\n");
    for (int i = 0; i < n; i++) {
        printf("\nProcess %d:\n", i + 1);
        
        processes[i].pid = i + 1;  // Process ID
        
        printf("Enter arrival time: ");
        scanf("%d", &processes[i].arrival_time);
        
        printf("Enter burst time: ");
        scanf("%d", &processes[i].burst_time);
    }
    
    printf("\nShortest Job First (SJF) Scheduling Algorithm\n");
    printf("===========================================\n");
    calculateTimes(processes, n);

    return 0;
}
