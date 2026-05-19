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
    int priority;   // Priority

    int completion; // Completion Time
    int turnaround; // Turnaround Time
    int waiting;    // Waiting Time
};

// Class for Preemptive Priority Scheduling
class PriorityPreemptive {

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

            cout << "Priority: ";
            cin >> p[i].priority;

            // Initially remaining time = burst time
            p[i].remaining = p[i].burst;
        }
    }

    // Function to calculate Preemptive Priority
    void calculatePriority() {

        int currentTime = 0;
        int completedCount = 0;

        int previousProcess = -1;

        // Store starting time
        ganttTime[0] = 0;

        // Run until all processes finish
        while (completedCount < n) {

            int highest = -1;
            int bestPriority = INT_MAX;

            // Find highest priority process
            for (int i = 0; i < n; i++) {

                // Process must:
                // 1. Already arrive
                // 2. Still have remaining time
                if (p[i].arrival <= currentTime &&
                    p[i].remaining > 0) {

                    // Lower number = higher priority
                    if (p[i].priority <
                        bestPriority) {

                        bestPriority =
                            p[i].priority;

                        highest = i;
                    }
                }
            }

            // If no process has arrived
            if (highest == -1) {

                currentTime++;
            }

            else {

                // Add new process to Gantt Chart
                if (previousProcess !=
                    p[highest].id) {

                    ganttProcess[ganttIndex] =
                        p[highest].id;

                    ganttIndex++;

                    ganttTime[ganttIndex - 1] =
                        currentTime;

                    previousProcess =
                        p[highest].id;
                }

                // Execute for 1 unit time
                p[highest].remaining--;

                currentTime++;

                // If process finishes
                if (p[highest].remaining == 0) {

                    completedCount++;

                    // Completion Time
                    p[highest].completion =
                        currentTime;

                    // Turnaround Time = CT - AT
                    p[highest].turnaround =
                        p[highest].completion -
                        p[highest].arrival;

                    // Waiting Time = TAT - BT
                    p[highest].waiting =
                        p[highest].turnaround -
                        p[highest].burst;
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

        cout << "\n========== PREEMPTIVE PRIORITY TABLE ==========\n\n";

        cout << left
             << setw(10) << "Process"
             << setw(10) << "AT"
             << setw(10) << "BT"
             << setw(10) << "PRI"
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
                 << p[i].priority

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
    PriorityPreemptive obj;

    // Call functions
    obj.inputProcesses();
    obj.calculatePriority();
    obj.displayGanttChart();
    obj.displayTable();

    return 0;
}