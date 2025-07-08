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

void firstFit(Block* blockList, Process* processList, int blockCount, int processCount) {
    for (int i = 0; i < processCount; i++) {
        Block* currentBlock = blockList;
        int allocated = 0;

        while (currentBlock != NULL) {
            if (currentBlock->remainingSize >= processList[i].processSize) {
                processList[i].allocatedBlock = currentBlock->blockSize;
                processList[i].remainingBlockSize = currentBlock->remainingSize - processList[i].processSize;
                currentBlock->remainingSize -= processList[i].processSize;
                allocated = 1;
                break;
            }
            currentBlock = currentBlock->next;
        }

        if (!allocated) {
            processList[i].allocatedBlock = -1;
            processList[i].remainingBlockSize = -1;
        }
    }

    printf("\nFirst-Fit Memory Allocation Results:\n");
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

void freeMemory(Block* blockList, Process* processList) {
    Block* currentBlock = blockList;
    while (currentBlock != NULL) {
        Block* temp = currentBlock;
        currentBlock = currentBlock->next;
        free(temp);
    }
}

int main() {
    int blockCount, processCount;

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

    firstFit(blockList, processList, blockCount, processCount);

    freeMemory(blockList, processList);
    free(processList);

    return 0;
}