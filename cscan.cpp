#include <iostream>
#include <cmath>
using namespace std;

int main() {

    int req[100], n;
    int head, total = 0;

    cout << "Enter number of requests: ";
    cin >> n;

    cout << "Enter requests: ";
    for(int i = 0; i < n; i++) {
        cin >> req[i];
    }

    cout << "Enter initial head position: ";
    cin >> head;

    // Bubble Sort
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {

            if(req[j] > req[j+1]) {

                int temp = req[j];
                req[j] = req[j+1];
                req[j+1] = temp;
            }
        }
    }

    int index;

    for(int i = 0; i < n; i++) {
        if(req[i] > head) {
            index = i;
            break;
        }
    }

    cout << "\nSeek Sequence: " << head;

    // Move Right
    for(int i = index; i < n; i++) {
        total += abs(req[i] - head);
        head = req[i];
        cout << " -> " << head;
    }

    // Move to end
    total += abs(199 - head);
    head = 199;

    // Jump to beginning
    total += 199;
    head = 0;

    // Continue from start
    for(int i = 0; i < index; i++) {
        total += abs(req[i] - head);
        head = req[i];
        cout << " -> " << head;
    }

    cout << "\nTotal Head Movement = " << total;

    return 0;
}