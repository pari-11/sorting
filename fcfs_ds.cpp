#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int req[100], n;
    int head;
    int total = 0;

    cout << "Enter number of requests: ";
    cin >> n;

    cout << "Enter requests: ";
    for(int i = 0; i < n; i++) {
        cin >> req[i];
    }

    cout << "Enter initial head position: ";
    cin >> head;

    cout << "\nSeek Sequence: " << head;

    for(int i = 0; i < n; i++) {
        total += abs(req[i] - head);

        head = req[i];

        cout << " -> " << head;
    }

    cout << "\nTotal Head Movement = " << total;

    return 0;
}