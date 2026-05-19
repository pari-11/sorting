#include <iostream>
#include <iomanip>
using namespace std;

// Class to store process details
class Process {

public:

    int id;         // Process ID
    int arrival;    // Arrival Time
    int burst;      // Burst Time
    int completion; // Completion Time
    int turnaround; // Turnaround Time
    int waiting;    // Waiting Time
};

// Class for FCFS Scheduling
class FCFS {

private:

    Process p[100]; // Array of processes
    int n;          // Number of processes

public:

    // Function to input process details
    void inputProcesses() {

        cout << "Enter number of processes: ";
        cin >> n;

        // Input details for each process
        for (int i = 0; i < n; i++) {

            p[i].id = i + 1;

            cout << "\nEnter details for Process P" << p[i].id << endl;

            cout << "Arrival Time: ";
            cin >> p[i].arrival;

            cout << "Burst Time: ";
            cin >> p[i].burst;
        }
    }

    // Function to sort processes by arrival time
    void sortProcesses() {

        for (int i = 0; i < n - 1; i++) {

            for (int j = 0; j < n - i - 1; j++) {

                // Swap if next process arrives earlier
                if (p[j].arrival > p[j + 1].arrival) {

                    Process temp = p[j];
                    p[j] = p[j + 1];
                    p[j + 1] = temp;
                }
            }
        }
    }

    // Function to calculate FCFS scheduling
    void calculateFCFS() {

        int currentTime = 0;

        // Calculate values for each process
        for (int i = 0; i < n; i++) {

            // If CPU is idle
            if (currentTime < p[i].arrival) {
                currentTime = p[i].arrival;
            }

            // Completion Time
            p[i].completion = currentTime + p[i].burst;

            // Turnaround Time = CT - AT
            p[i].turnaround =
                p[i].completion - p[i].arrival;

            // Waiting Time = TAT - BT
            p[i].waiting =
                p[i].turnaround - p[i].burst;

            // Update current time
            currentTime = p[i].completion;
        }
    }

    // Function to display Gantt chart
    void displayGanttChart() {

        cout << "\n\n========== GANTT CHART ==========\n\n";

        // Top line
        for (int i = 0; i < n; i++) {
            cout << "-------";
        }

        cout << "-" << endl;

        // Process IDs
        for (int i = 0; i < n; i++) {
            cout << "|  P" << p[i].id << "  ";
        }

        cout << "|" << endl;

        // Bottom line
        for (int i = 0; i < n; i++) {
            cout << "-------";
        }

        cout << "-" << endl;

        // Time values
        cout << "0";

        for (int i = 0; i < n; i++) {
            cout << setw(7) << p[i].completion;
        }

        cout << endl;
    }

    // Function to display process table
    void displayTable() {

        float totalWT = 0;
        float totalTAT = 0;

        cout << "\n========== FCFS TABLE ==========\n\n";

        cout << left
             << setw(10) << "Process"
             << setw(10) << "AT"
             << setw(10) << "BT"
             << setw(10) << "CT"
             << setw(10) << "TAT"
             << setw(10) << "WT"
             << endl;

        // Print process details
        for (int i = 0; i < n; i++) {

            cout << left
                 << setw(10) << ("P" + to_string(p[i].id))
                 << setw(10) << p[i].arrival
                 << setw(10) << p[i].burst
                 << setw(10) << p[i].completion
                 << setw(10) << p[i].turnaround
                 << setw(10) << p[i].waiting
                 << endl;

            // Add totals for average calculation
            totalWT += p[i].waiting;
            totalTAT += p[i].turnaround;
        }

        // Display averages
        cout << "\nAverage Waiting Time = "
             << totalWT / n;

        cout << "\nAverage Turnaround Time = "
             << totalTAT / n << endl;
    }
};

int main() {

    // Create FCFS object
    FCFS obj;

    // Call functions
    obj.inputProcesses();
    obj.sortProcesses();
    obj.calculateFCFS();
    obj.displayGanttChart();
    obj.displayTable();

    return 0;
}