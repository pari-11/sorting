#include <iostream>
using namespace std;

int main() {
    
    int pageTable[10];
    int pages, pageSize;
    
    cout << "Enter number of pages: ";
    cin >> pages;

    cout << "Enter page size: ";
    cin >> pageSize;

    // Input page table
    cout << "Enter frame number for each page:\n";

    for(int i = 0; i < pages; i++) {
        cout << "Page " << i << " -> Frame: ";
        cin >> pageTable[i];
    }

    int logicalAddress;

    cout << "Enter logical address: ";
    cin >> logicalAddress;

    // Find page number and offset
    int pageNumber = logicalAddress / pageSize;
    int offset = logicalAddress % pageSize;

    // Get frame number
    int frameNumber = pageTable[pageNumber];

    // Calculate physical address
    int physicalAddress = (frameNumber * pageSize) + offset;

    cout << "\nPage Number = " << pageNumber << endl;
    cout << "Offset = " << offset << endl;
    cout << "Frame Number = " << frameNumber << endl;
    cout << "Physical Address = " << physicalAddress << endl;

    return 0;
}