#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int req[100], visited[100];
    int n, head;
    int total = 0;

    cout << "Enter number of requests: ";
    cin >> n;

    cout << "Enter requests: ";
    for(int i = 0; i < n; i++) {
        cin >> req[i];
        visited[i] = 0;
    }

    cout << "Enter initial head position: ";
    cin >> head;

    cout << "\nSeek Sequence: " << head;

    for(int i = 0; i < n; i++) {

        int min = 9999;
        int index = -1;

        for(int j = 0; j < n; j++) {

            if(visited[j] == 0) {

                int dist = abs(req[j] - head);

                if(dist < min) {
                    min = dist;
                    index = j;
                }
            }
        }

        total += abs(req[index] - head);

        head = req[index];

        visited[index] = 1;

        cout << " -> " << head;
    }

    cout << "\nTotal Head Movement = " << total;

    return 0;
}