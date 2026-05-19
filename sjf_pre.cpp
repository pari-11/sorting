#include <iostream>
#include <iomanip>
#include <climits>
using namespace std;

// Class to store process details
class Process {

public:

    int id;         // Process ID
    int arrival;    // Arrival Time
    int burst;      // Original Burst Time
    int remaining;  // Remaining Burst Time
    int completion; // Completion Time
    int turnaround; // Turnaround Time
    int waiting;    // Waiting Time
};

// Class for Preemptive SJF Scheduling
class SJFPreemptive {

private:

    Process p[100]; // Array of processes
    int n;          // Number of processes

    // Arrays for Gantt Chart
    int ganttProcess[200];
    int ganttTime[200];

    int ganttIndex = 0;

public:

    // Function to input process details
    void inputProcesses() {

        cout << "Enter number of processes: ";
        cin >> n;

        // Input details for each process
        for (int i = 0; i < n; i++) {

            p[i].id = i + 1;

            cout << "\nEnter details for Process P"
                 << p[i].id << endl;

            cout << "Arrival Time: ";
            cin >> p[i].arrival;

            cout << "Burst Time: ";
            cin >> p[i].burst;

            // Initially remaining time = burst time
            p[i].remaining = p[i].burst;
        }
    }

    // Function to calculate Preemptive SJF
    void calculateSJF() {

        int currentTime = 0;
        int completedCount = 0;

        int previousProcess = -1;

        // Store starting time
        ganttTime[0] = 0;

        // Run until all processes finish
        while (completedCount < n) {

            int shortest = -1;
            int minimumBurst = INT_MAX;

            // Find process with shortest remaining time
            for (int i = 0; i < n; i++) {

                // Process must:
                // 1. Already arrive
                // 2. Still have remaining time
                if (p[i].arrival <= currentTime &&
                    p[i].remaining > 0) {

                    // Select shortest remaining time
                    if (p[i].remaining < minimumBurst) {

                        minimumBurst = p[i].remaining;
                        shortest = i;
                    }
                }
            }

            // If no process has arrived
            if (shortest == -1) {

                currentTime++;
            }

            else {

                // Add new process to Gantt Chart
                if (previousProcess != p[shortest].id) {

                    ganttProcess[ganttIndex] =
                        p[shortest].id;

                    ganttIndex++;

                    ganttTime[ganttIndex - 1] =
                        currentTime;

                    previousProcess =
                        p[shortest].id;
                }

                // Execute for 1 unit time
                p[shortest].remaining--;

                currentTime++;

                // If process finishes
                if (p[shortest].remaining == 0) {

                    completedCount++;

                    // Completion Time
                    p[shortest].completion =
                        currentTime;

                    // Turnaround Time = CT - AT
                    p[shortest].turnaround =
                        p[shortest].completion -
                        p[shortest].arrival;

                    // Waiting Time = TAT - BT
                    p[shortest].waiting =
                        p[shortest].turnaround -
                        p[shortest].burst;
                }
            }
        }

        // Store final ending time
        ganttTime[ganttIndex] = currentTime;
    }

    // Function to display Gantt Chart
    void displayGanttChart() {

        cout << "\n\n========== GANTT CHART ==========\n\n";

        // Top line
        for (int i = 0; i < ganttIndex; i++) {
            cout << "-------";
        }

        cout << "-" << endl;

        // Process IDs
        for (int i = 0; i < ganttIndex; i++) {

            cout << "|  P"
                 << ganttProcess[i]
                 << "  ";
        }

        cout << "|" << endl;

        // Bottom line
        for (int i = 0; i < ganttIndex; i++) {
            cout << "-------";
        }

        cout << "-" << endl;

        // Time values
        for (int i = 0; i <= ganttIndex; i++) {

            cout << setw(7)
                 << ganttTime[i];
        }

        cout << endl;
    }

    // Function to display process table
    void displayTable() {

        float totalWT = 0;
        float totalTAT = 0;

        cout << "\n========== PREEMPTIVE SJF TABLE ==========\n\n";

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
                 << setw(10)
                 << ("P" + to_string(p[i].id))

                 << setw(10)
                 << p[i].arrival

                 << setw(10)
                 << p[i].burst

                 << setw(10)
                 << p[i].completion

                 << setw(10)
                 << p[i].turnaround

                 << setw(10)
                 << p[i].waiting
                 << endl;

            // Add totals
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

    // Create object
    SJFPreemptive obj;

    // Call functions
    obj.inputProcesses();
    obj.calculateSJF();
    obj.displayGanttChart();
    obj.displayTable();

    return 0;
}