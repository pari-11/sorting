#include <iostream>
using namespace std;

int main() {

    // ---------------- PAGING ----------------

    int pageTable[10];
    int pages, pageSize;

    cout << "===== PAGING =====\n";

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

    // Find page number
    int pageNumber = logicalAddress / pageSize;

    // Find offset
    int offset = logicalAddress % pageSize;

    // Get frame number from page table
    int frameNumber = pageTable[pageNumber];

    // Calculate physical address
    int physicalAddress = (frameNumber * pageSize) + offset;

    cout << "\n--- Paging Output ---\n";

    cout << "Page Number = " << pageNumber << endl;
    cout << "Offset = " << offset << endl;
    cout << "Frame Number = " << frameNumber << endl;
    cout << "Physical Address = " << physicalAddress << endl;



    // ---------------- SEGMENTATION ----------------

    int segments;
    int base[10], limit[10];

    cout << "\n\n===== SEGMENTATION =====\n";

    cout << "Enter number of segments: ";
    cin >> segments;

    // Input base and limit for each segment
    for(int i = 0; i < segments; i++) {

        cout << "\nSegment " << i << endl;

        cout << "Enter base address: ";
        cin >> base[i];

        cout << "Enter limit: ";
        cin >> limit[i];
    }

    int segmentNumber, segmentOffset;

    cout << "\nEnter segment number: ";
    cin >> segmentNumber;

    cout << "Enter offset: ";
    cin >> segmentOffset;

    // Check whether offset is valid
    if(segmentOffset < limit[segmentNumber]) {

        // Physical address calculation
        int physicalAddr = base[segmentNumber] + segmentOffset;

        cout << "\n--- Segmentation Output ---\n";

        cout << "Base Address = " << base[segmentNumber] << endl;
        cout << "Offset = " << segmentOffset << endl;
        cout << "Physical Address = " << physicalAddr << endl;
    }
    else {

        cout << "\nSegmentation Fault! Offset exceeds limit.\n";
    }

    return 0;
}
