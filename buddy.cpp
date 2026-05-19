#include <iostream>
using namespace std;
class BuddySystem
{
    int memory[100];
    int blockSize[100];
    int freeBlock[100];
    int blockCount;
public:
    BuddySystem(int totalMemory)
    {
        blockCount = 1;
        memory[0] = 0;              // starting address
        blockSize[0] = totalMemory;
        freeBlock[0] = 1;           // free
    }
    // Find next power of 2
    int nextPowerOf2(int n)
    {
        int power = 1;
        while(power < n)
        {
            power = power * 2;
        }
        return power;
    }
    // Allocate memory
    void allocate(int size)
    {
        int reqSize = nextPowerOf2(size);
        int index = -1;
        // Find suitable free block
        for(int i = 0; i < blockCount; i++)
        {
            if(freeBlock[i] == 1 && blockSize[i] >= reqSize)
            {
                index = i;
                break;
            }
        }
        if(index == -1)
        {
            cout << "Memory not available\n";
            return;
        }
        // Split until exact size obtained
        while(blockSize[index] > reqSize)
        {
            int newSize = blockSize[index] / 2;
            // Shift elements to create new buddy
            for(int j = blockCount; j > index + 1; j--)
            {
                memory[j] = memory[j - 1];
                blockSize[j] = blockSize[j - 1];
                freeBlock[j] = freeBlock[j - 1];
            }
            // First buddy
            blockSize[index] = newSize;
            // Second buddy
            memory[index + 1] = memory[index] + newSize;
            blockSize[index + 1] = newSize;
            freeBlock[index + 1] = 1;
            blockCount++;
        }
        freeBlock[index] = 0;
        cout << "Allocated "
             << reqSize
             << " KB at address "
             << memory[index]
             << endl;
    }
    // Free memory block
    void deallocate(int address)
    {
        int index = -1;
        // Find block
        for(int i = 0; i < blockCount; i++)
        {
            if(memory[i] == address)
            {
                index = i;
                break;
            }
        }
        if(index == -1)
        {
            cout << "Invalid address\n";
            return;
        }
        freeBlock[index] = 1;
        cout << "Memory freed at address "
             << address
             << endl;
        merge();
    }
    // Merge free buddies
    void merge()
    {
        for(int i = 0; i < blockCount - 1; i++)
        {
            if(freeBlock[i] == 1 &&
               freeBlock[i + 1] == 1 &&
               blockSize[i] == blockSize[i + 1])
            {
                // Merge
                blockSize[i] = blockSize[i] * 2;
                // Shift left
                for(int j = i + 1; j < blockCount - 1; j++)
                {
                    memory[j] = memory[j + 1];
                    blockSize[j] = blockSize[j + 1];
                    freeBlock[j] = freeBlock[j + 1];
                }
                blockCount--;
                i = -1; // restart checking
            }
        }
    }
    // Display memory blocks
    void display()
    {
        cout << "\nMemory Blocks:\n";
        cout << "Address\tSize\tStatus\n";
        for(int i = 0; i < blockCount; i++)
        {
            cout << memory[i]
                 << "\t"
                 << blockSize[i]
                 << "\t";
            if(freeBlock[i] == 1)
                cout << "Free";
            else
                cout << "Allocated";
            cout << endl;
        }
    }
};
int main()
{
    BuddySystem bs(64);
    bs.display();
    bs.allocate(10);
    bs.display();
    bs.allocate(20);
    bs.display();
    bs.deallocate(0);
    bs.display();
    return 0;
}