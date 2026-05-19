#include <iostream>
#include <iomanip>

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

// Class for Round Robin Scheduling
class RoundRobin {

private:

    Process p[100]; // Array of processes
    int n;          // Number of processes

    int timeQuantum; // Time Quantum

    // Arrays for Gantt Chart
    int ganttProcess[200];
    int ganttTime[200];

    int ganttIndex = 0;

public:

    // Function to input process details
    void inputProcesses() {

        cout << "Enter number of processes: ";
        cin >> n;

        cout << "Enter Time Quantum: ";
        cin >> timeQuantum;

        // Input details for each process
        for (int i = 0; i < n; i++) {

            p[i].id = i + 1;

            cout << "\nEnter details for Process P"
                 << p[i].id << endl;

            cout << "Arrival Time: ";
            cin >> p[i].arrival;

            cout << "Burst Time: ";
            cin >> p[i].burst;

            // Initially remaining = burst
            p[i].remaining = p[i].burst;
        }
    }

    // Function to calculate Round Robin
    void calculateRoundRobin() {

        int currentTime = 0;

        int completedCount = 0;

        // Store starting time
        ganttTime[0] = 0;

        // Run until all processes complete
        while (completedCount < n) {

            bool processExecuted = false;

            // Traverse all processes repeatedly
            for (int i = 0; i < n; i++) {

                // Process must:
                // 1. Already arrive
                // 2. Still have remaining time
                if (p[i].arrival <= currentTime &&
                    p[i].remaining > 0) {

                    processExecuted = true;

                    // Add process to Gantt Chart
                    ganttProcess[ganttIndex] =
                        p[i].id;

                    ganttIndex++;

                    ganttTime[ganttIndex - 1] =
                        currentTime;

                    // ==========================
                    // IF REMAINING TIME IS MORE
                    // THAN TIME QUANTUM
                    // ==========================
                    if (p[i].remaining >
                        timeQuantum) {

                        // Execute for time quantum
                        currentTime +=
                            timeQuantum;

                        // Reduce remaining time
                        p[i].remaining -=
                            timeQuantum;
                    }

                    // ==========================
                    // LAST EXECUTION OF PROCESS
                    // ==========================
                    else {

                        // Execute remaining time
                        currentTime +=
                            p[i].remaining;

                        // Remaining becomes 0
                        p[i].remaining = 0;

                        completedCount++;

                        // Completion Time
                        p[i].completion =
                            currentTime;

                        // Turnaround Time = CT - AT
                        p[i].turnaround =
                            p[i].completion -
                            p[i].arrival;

                        // Waiting Time = TAT - BT
                        p[i].waiting =
                            p[i].turnaround -
                            p[i].burst;
                    }
                }
            }

            // If no process available
            if (!processExecuted) {

                currentTime++;
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

        cout << "\n========== ROUND ROBIN TABLE ==========\n\n";

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
    RoundRobin obj;

    // Call functions
    obj.inputProcesses();

    obj.calculateRoundRobin();

    obj.displayGanttChart();

    obj.displayTable();

    return 0;
}