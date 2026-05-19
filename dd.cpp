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

    int alloc[10][10], request[10][10];
    int avail[10];

    // Allocation Matrix
    cout << "\nEnter Allocation Matrix:\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> alloc[i][j];
        }
    }

    // Request Matrix
    cout << "\nEnter Request Matrix:\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> request[i][j];
        }
    }

    // Available Resources
    cout << "\nEnter Available Resources:\n";
    for(int j = 0; j < m; j++) {
        cin >> avail[j];
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

                // Check if request can be satisfied
                for(int j = 0; j < m; j++) {

                    if(request[i][j] > avail[j]) {
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

    // Deadlock Check
    if(count == n) {

        cout << "\nNo Deadlock Detected\n";
        cout << "Execution Sequence: ";

        for(int i = 0; i < n; i++) {

            cout << "P" << safeSeq[i];

            if(i != n - 1)
                cout << " -> ";
        }
    }
    else {

        cout << "\nDeadlock Detected\n";

        cout << "Processes in Deadlock: ";

        for(int i = 0; i < n; i++) {

            if(finish[i] == 0) {
                cout << "P" << i << " ";
            }
        }
    }

    return 0;
}