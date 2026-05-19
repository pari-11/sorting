#include <iostream>
using namespace std;

class Memory {

    int blockSize[20], processSize[20];
    int allocation[20];

    int b, p;

public:

    void input() {

        cout << "Enter number of memory blocks: ";
        cin >> b;

        cout << "Enter number of processes: ";
        cin >> p;

        cout << "\nEnter block sizes:\n";
        for(int i = 0; i < b; i++) {
            cin >> blockSize[i];
        }

        cout << "\nEnter process sizes:\n";
        for(int i = 0; i < p; i++) {
            cin >> processSize[i];
        }
    }

    // ---------------- FIRST FIT ----------------
    void firstFit() {

        int tempBlock[20];

        // Copy original blocks
        for(int i = 0; i < b; i++) {
            tempBlock[i] = blockSize[i];
        }

        for(int i = 0; i < p; i++) {
            allocation[i] = -1;
        }

        for(int i = 0; i < p; i++) {

            for(int j = 0; j < b; j++) {

                if(tempBlock[j] >= processSize[i]) {
                        
                    allocation[i] = j;
                    tempBlock[j] -= processSize[i];
                    break;
                }
            }
        }

        cout << "\n----- FIRST FIT -----\n";

        display();
    }

    // ---------------- BEST FIT ----------------
    void bestFit() {

        int tempBlock[20];

        for(int i = 0; i < b; i++) {
            tempBlock[i] = blockSize[i];
        }

        for(int i = 0; i < p; i++) {
            allocation[i] = -1;
        }

        for(int i = 0; i < p; i++) {

            int bestIndex = -1;

            for(int j = 0; j < b; j++) {

                if(tempBlock[j] >= processSize[i]) {

                    if(bestIndex == -1 ||
                       tempBlock[j] < tempBlock[bestIndex]) {

                        bestIndex = j;
                    }
                }
            }

            if(bestIndex != -1) {

                allocation[i] = bestIndex;
                tempBlock[bestIndex] -= processSize[i];
            }
        }

        cout << "\n----- BEST FIT -----\n";

        display();
    }

    // ---------------- WORST FIT ----------------
    void worstFit() {

        int tempBlock[20];

        for(int i = 0; i < b; i++) {
            tempBlock[i] = blockSize[i];
        }

        for(int i = 0; i < p; i++) {
            allocation[i] = -1;
        }

        for(int i = 0; i < p; i++) {

            int worstIndex = -1;

            for(int j = 0; j < b; j++) {

                if(tempBlock[j] >= processSize[i]) {

                    if(worstIndex == -1 ||
                       tempBlock[j] > tempBlock[worstIndex]) {

                        worstIndex = j;
                    }
                }
            }

            if(worstIndex != -1) {

                allocation[i] = worstIndex;
                tempBlock[worstIndex] -= processSize[i];
            }
        }

        cout << "\n----- WORST FIT -----\n";

        display();
    }

    // ---------------- NEXT FIT ----------------
    void nextFit() {

        int tempBlock[20];

        for(int i = 0; i < b; i++) {
            tempBlock[i] = blockSize[i];
        }

        for(int i = 0; i < p; i++) {
            allocation[i] = -1;
        }

        int lastIndex = 0;

        for(int i = 0; i < p; i++) {

            int count = 0;
            int j = lastIndex;

            while(count < b) {

                if(tempBlock[j] >= processSize[i]) {

                    allocation[i] = j;
                    tempBlock[j] -= processSize[i];

                    lastIndex = j;
                    break;
                }

                j = (j + 1) % b;
                count++;
            }
        }

        cout << "\n----- NEXT FIT -----\n";

        display();
    }

    // ---------------- DISPLAY ----------------
    void display() {

        cout << "\nProcess No\tProcess Size\tBlock No\n";

        for(int i = 0; i < p; i++) {

            cout << "P" << i + 1 << "\t\t";
            cout << processSize[i] << "\t\t";

            if(allocation[i] != -1)
                cout << allocation[i] + 1;
            else
                cout << "Not Allocated";

            cout << endl;
        }
    }
};

int main() {

    Memory m;

    m.input();

    m.firstFit();
    m.bestFit();
    m.worstFit();
    m.nextFit();

    return 0;
}