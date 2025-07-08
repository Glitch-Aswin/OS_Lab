#include <stdio.h>
#include <stdbool.h>

struct Process {
    int pid;          // Process ID
    int arrival_time; // Arrival time
    int burst_time;   // Burst time
    int priority;     // Priority (lower value means higher priority)
    int start_time;   // Start time of execution
    int completion_time; // Completion time
    int waiting_time;    // Waiting time
    int turnaround_time; // Turnaround time
    bool executed;       // Flag to check if process is executed
};

// Function to find the process with highest priority among arrived processes
int findHighestPriorityProcess(struct Process processes[], int n, int current_time) {
    int highest_priority_index = -1;
    int highest_priority = 9999;
    
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= current_time && !processes[i].executed) {
            if (processes[i].priority < highest_priority) {
                highest_priority = processes[i].priority;
                highest_priority_index = i;
            }
        }
    }
    
    return highest_priority_index;
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
        int highest_priority_process = findHighestPriorityProcess(processes, n, current_time);
        
        if (highest_priority_process == -1) {
            // No process available at current time
            current_time++;
            continue;
        }
        
        // Update process details
        processes[highest_priority_process].start_time = current_time;
        processes[highest_priority_process].completion_time = current_time + processes[highest_priority_process].burst_time;
        processes[highest_priority_process].turnaround_time = processes[highest_priority_process].completion_time - processes[highest_priority_process].arrival_time;
        processes[highest_priority_process].waiting_time = processes[highest_priority_process].turnaround_time - processes[highest_priority_process].burst_time;
        processes[highest_priority_process].executed = true;
        
       
        
        // Update current time
        current_time = processes[highest_priority_process].completion_time;
        completed++;
    }
    
  
    
    // Calculate average times
    float total_waiting_time = 0, total_turnaround_time = 0;
    
    printf("\n+----------+-------------+-----------+----------+-------------+----------------+\n");
    printf("| Process  | Arrival Time| Burst Time| Priority | Waiting Time| Turnaround Time|\n");
    printf("+----------+-------------+-----------+----------+-------------+----------------+\n");
    
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
        printf("| P%-7d | %-11d | %-9d | %-8d | %-11d | %-14d |\n", 
               processes[i].pid, processes[i].arrival_time, processes[i].burst_time, 
               processes[i].priority, processes[i].waiting_time, processes[i].turnaround_time);
    }
    
    printf("+----------+-------------+-----------+----------+-------------+----------------+\n");
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
        
        printf("Enter priority (lower value means higher priority): ");
        scanf("%d", &processes[i].priority);
    }
    
    printf("\nPriority Scheduling Algorithm\n");
    printf("============================\n");
    calculateTimes(processes, n);

    return 0;
}
