#include <stdio.h>
#include <stdlib.h>

typedef struct Block {
    int blockSize;       // Total size of the memory block
    int remainingSize;   // Remaining size of the block
    struct Block* next;  // Pointer to the next block
} Block;

typedef struct Process {
    int processSize;     // Size of the process
    int allocatedBlock;  // Block to which the process is allocated (-1 if not allocated)
    int remainingBlockSize; // Remaining size of the allocated block
} Process;

// Function to create a new block node
Block* createBlock(int blockSize) {
    Block* newBlock = (Block*)malloc(sizeof(Block));
    if (newBlock == NULL) {
        printf("Memory allocation failed for block\n");
        exit(1);
    }
    newBlock->blockSize = blockSize;
    newBlock->remainingSize = blockSize;
    newBlock->next = NULL;
    return newBlock;
}

// Function to allocate processes using Best-Fit algorithm
void bestFit(Block* blockList, Process* processList, int blockCount, int processCount) {
    for (int i = 0; i < processCount; i++) {
        Block* currentBlock = blockList;
        Block* bestBlock = NULL;
        int smallestRemainingSize = 9999; // Large arbitrary value

        // Find the best-fit block
        while (currentBlock != NULL) {
            // Check if block can accommodate the process
            if (currentBlock->remainingSize >= processList[i].processSize) {
                // Find block with smallest remaining size that can fit the process
                if (currentBlock->remainingSize < smallestRemainingSize) {
                    bestBlock = currentBlock;
                    smallestRemainingSize = currentBlock->remainingSize;
                }
            }
            currentBlock = currentBlock->next;
        }

        // Allocate to the best-fit block
        if (bestBlock != NULL) {
            processList[i].allocatedBlock = bestBlock->blockSize;
            processList[i].remainingBlockSize = bestBlock->remainingSize - processList[i].processSize;
            bestBlock->remainingSize -= processList[i].processSize;
        } else {
            processList[i].allocatedBlock = -1;
            processList[i].remainingBlockSize = -1;
        }
    }

    // Print the results in a tabular format
    printf("\nBest-Fit Memory Allocation Results:\n");
    printf("-----------------------------------------------------------------\n");
    printf("| Process No. | Process Size | Block Size | Remaining Block Size |\n");
    printf("-----------------------------------------------------------------\n");

    for (int i = 0; i < processCount; i++) {
        if (processList[i].allocatedBlock != -1) {
            printf("| %-11d | %-12d | %-10d | %-19d |\n", 
                   i + 1, 
                   processList[i].processSize, 
                   processList[i].allocatedBlock,
                   processList[i].remainingBlockSize);
        } else {
            printf("| %-11d | %-12d | %-10s | %-19s |\n", 
                   i + 1, 
                   processList[i].processSize, 
                   "N/A", 
                   "N/A");
        }
    }
    printf("-----------------------------------------------------------------\n");
}

// Function to free allocated memory
void freeMemory(Block* blockList) {
    Block* currentBlock = blockList;
    while (currentBlock != NULL) {
        Block* temp = currentBlock;
        currentBlock = currentBlock->next;
        free(temp);
    }
}

int main() {
    int blockCount, processCount;

    // Input memory block details
    printf("Enter the number of memory blocks: ");
    scanf("%d", &blockCount);

    Block* blockList = NULL;
    Block* tempBlock = NULL;

    for (int i = 0; i < blockCount; i++) {
        int blockMem;
        printf("Block %d size: ", i + 1);
        scanf("%d", &blockMem);

        Block* newBlock = createBlock(blockMem);
        
        if (blockList == NULL) {
            blockList = newBlock;
        } else {
            tempBlock->next = newBlock;
        }
        tempBlock = newBlock;
    }

    // Input process details
    printf("Enter the number of processes: ");
    scanf("%d", &processCount);

    Process* processList = malloc(processCount * sizeof(Process));
    if (processList == NULL) {
        printf("Memory allocation failed for processes\n");
        return 1;
    }

    for (int i = 0; i < processCount; i++) {
        printf("Process %d size: ", i + 1);
        scanf("%d", &processList[i].processSize);
        processList[i].allocatedBlock = -1;
    }

    // Perform Best-Fit memory allocation
    bestFit(blockList, processList, blockCount, processCount);

    // Free allocated memory
    freeMemory(blockList);
    free(processList);

    return 0;
}