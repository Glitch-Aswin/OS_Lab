#include <stdio.h>
#include <stdbool.h>

#define P 5  
#define R 3 

bool isSafe(int avail[], int max[][R], int allot[][R]) 
{
    int work[R];
    bool finish[P] = {0};
    int safeSeq[P];
    int count = 0;
    
    for (int i = 0; i < R; i++) 
        work[i] = avail[i];
    
    int need[P][R];
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allot[i][j];
    
    bool found;
    do 
    {
        found = false;
        for (int p = 0; p < P; p++) 
        {
            if (finish[p]) 
                continue;
            bool canAllocate = true;
            for (int j = 0; j < R; j++) 
            {
                if (need[p][j] > work[j]) 
                {
                    canAllocate = false;
                    break;
                }
            }
            if (canAllocate) 
            {
                for (int j = 0; j < R; j++) 
                    work[j] += allot[p][j];
                
                safeSeq[count++] = p;
                finish[p] = true;
                found = true;
            }
        }
    }
     while (found && count < P);
    if (count < P) {
        return false;
    }
    printf("Safe sequence: ");
    for (int i = 0; i < P; i++)
        printf("%d ", safeSeq[i]);
    printf("\n");
    return true;
}
bool requestResources(int processID, int request[], int avail[], int max[][R], int allot[][R]) 
{
    int need[P][R];
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allot[i][j];
    for (int i = 0; i < R; i++) 
    {
        if (request[i] > need[processID][i]) 
        {
            printf("Error: Process %d has exceeded its remaining need.\n", processID);
            printf("Request: %d, Need: %d for resource %d\n", 
                   request[i], need[processID][i], i);
            return false;
        }
    }
    for (int i = 0; i < R; i++) 
    {
        if (request[i] > avail[i]) 
        {
            printf("Error: Resources not available for Process %d.\n", processID);
            return false;
        }
    }
    for (int i = 0; i < R; i++) 
    {
        avail[i] -= request[i];
        allot[processID][i] += request[i];
    }
    if (isSafe(avail, max, allot)) 
    {
        printf("Request granted for Process %d.\n", processID);
        return true;
    } 
    else 
    {
        printf("Request denied for Process %d. System would be in an unsafe state.\n", processID);
        for (int i = 0; i < R; i++) 
        {
            avail[i] += request[i];
            allot[processID][i] -= request[i];
        }
        return false;
    }
}

void displayState(int avail[], int max[][R], int allot[][R]) 
{
    int need[P][R];
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allot[i][j];
    printf("\nCurrent System State:\n");
    printf("Process\tAllocation\tMax\tNeed\tAvailable\n");
    for (int i = 0; i < P; i++) 
    {
        printf("P%d\t", i);
        for (int j = 0; j < R; j++)
            printf("%d ", allot[i][j]);
        printf("\t\t");
        for (int j = 0; j < R; j++)
            printf("%d ", max[i][j]);
        printf("\t");
        for (int j = 0; j < R; j++)
            printf("%d ", need[i][j]);
        if (i == 0) 
        {
            printf("\t");
            for (int j = 0; j < R; j++)
                printf("%d ", avail[j]);
        }
        
        printf("\n");
    }
    printf("\n");
}

int main() 
{
    int avail[R], max[P][R], allot[P][R];
    int numRequests, processID;
    printf("Enter available resources (separated by space):\n");
    for (int i = 0; i < R; i++) 
        scanf("%d", &avail[i]);
    for (int i = 0; i < P; i++) 
    {
        printf("Enter maximum resources for Process %d (separated by space):\n", i);
        for (int j = 0; j < R; j++) 
            scanf("%d", &max[i][j]);
    }
    for (int i = 0; i < P; i++) 
    {
        printf("Enter allocated resources for Process %d (separated by space):\n", i);
        for (int j = 0; j < R; j++) 
            scanf("%d", &allot[i][j]);
    }
    if (!isSafe(avail, max, allot)) 
    {
        printf("Error: Initial system state is not safe.\n");
        return 1;
    }
   // displayState(avail, max, allot);
    printf("Enter the number of processes making requests: ");
    scanf("%d", &numRequests);
    for (int i = 0; i < numRequests; i++) 
    {
        int request[R];
        printf("Enter process ID (0-%d) making the request: ", P - 1);
        scanf("%d", &processID);
        if (processID < 0 || processID >= P) 
        {
            printf("Invalid process ID. Please enter a value between 0 and %d.\n", P-1);
            i--;
            continue;
        }
        printf("Enter the requested resources for Process %d (separated by space):\n", processID);
        for (int j = 0; j < R; j++) 
            scanf("%d", &request[j]);
        requestResources(processID, request, avail, max, allot);
       // displayState(avail, max, allot);
    }
    
    return 0;
}
