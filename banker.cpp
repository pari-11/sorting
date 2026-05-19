#include <iostream>
using namespace std;

int main() {
    int n, m;

    // n = number of processes
    // m = number of resources

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter number of resources: ";
    cin >> m;

    int alloc[10][10], max[10][10], need[10][10];
    int avail[10];

    // Allocation Matrix
    cout << "\nEnter Allocation Matrix:\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> alloc[i][j];
        }
    }

    // Max Matrix
    cout << "\nEnter Max Matrix:\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> max[i][j];
        }
    }

    // Available Resources
    cout << "\nEnter Available Resources:\n";
    for(int j = 0; j < m; j++) {
        cin >> avail[j];
    }

    // Need Matrix = Max - Allocation
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int finish[10] = {0};
    int safeSeq[10];
    int count = 0;

    while(count < n) {

        int found = 0;

        for(int i = 0; i < n; i++) {

            // If process not completed
            if(finish[i] == 0) {

                int possible = 1;

                // Check if resources can be allocated
                for(int j = 0; j < m; j++) {

                    if(need[i][j] > avail[j]) {
                        possible = 0;
                        break;
                    }
                }

                // If possible, execute process
                if(possible == 1) {

                    for(int j = 0; j < m; j++) {
                        avail[j] = avail[j] + alloc[i][j];
                    }

                    safeSeq[count] = i;
                    count++;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        // No process could execute
        if(found == 0) {
            break;
        }
    }

    // Check safe state
    if(count == n) {

        cout << "\nSystem is in SAFE state\n";
        cout << "Safe Sequence: ";

        for(int i = 0; i < n; i++) {
            cout << "P" << safeSeq[i];

            if(i != n - 1)
                cout << " -> ";
        }
    }
    else {
        cout << "\nSystem is NOT in safe state";
    }

    return 0;
}