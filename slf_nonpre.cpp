#include <iostream>
#include <iomanip>
#include <climits>
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
    bool completed; // Check if process finished
};

// Class for Non-Preemptive SJF Scheduling
class SJFNonPreemptive {

private:

    Process p[100];
    int n;

    // Gantt Chart arrays
    int ganttProcess[100];
    int ganttTime[100];

    int ganttIndex = 0;

public:

    // Input function
    void inputProcesses() {

        cout << "Enter number of processes: ";
        cin >> n;

        for (int i = 0; i < n; i++) {

            p[i].id = i + 1;

            cout << "\nEnter details for Process P"
                 << p[i].id << endl;

            cout << "Arrival Time: ";
            cin >> p[i].arrival;

            cout << "Burst Time: ";
            cin >> p[i].burst;

            p[i].completed = false;
        }
    }

    // Function to calculate Non-Preemptive SJF
    void calculateSJF() {

        int currentTime = 0;
        int completedCount = 0;

        // Starting time
        ganttTime[0] = 0;

        // Run until all processes finish
        while (completedCount < n) {

            int shortest = -1;
            int minimumBurst = INT_MAX;

            // Find shortest burst among arrived processes
            for (int i = 0; i < n; i++) {

                if (p[i].arrival <= currentTime &&
                    p[i].completed == false) {

                    if (p[i].burst < minimumBurst) {

                        minimumBurst = p[i].burst;
                        shortest = i;
                    }
                }
            }

            // If no process has arrived
            if (shortest == -1) {

                currentTime++;
            }

            else {

                // Add process to Gantt Chart
                ganttProcess[ganttIndex] =
                    p[shortest].id;

                ganttTime[ganttIndex] =
                    currentTime;

                ganttIndex++;

                // Execute FULL burst time
                currentTime =
                    currentTime +
                    p[shortest].burst;

                // Completion Time
                p[shortest].completion =
                    currentTime;

                // Turnaround Time
                p[shortest].turnaround =
                    p[shortest].completion -
                    p[shortest].arrival;

                // Waiting Time
                p[shortest].waiting =
                    p[shortest].turnaround -
                    p[shortest].burst;

                // Mark completed
                p[shortest].completed = true;

                completedCount++;
            }
        }

        // Final ending time
        ganttTime[ganttIndex] = currentTime;
    }

    // Display Gantt Chart
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

    // Display Table
    void displayTable() {

        float totalWT = 0;
        float totalTAT = 0;

        cout << "\n========== NON PREEMPTIVE SJF TABLE ==========\n\n";

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

            totalWT += p[i].waiting;
            totalTAT += p[i].turnaround;
        }

        // Averages
        cout << "\nAverage Waiting Time = "
             << totalWT / n;

        cout << "\nAverage Turnaround Time = "
             << totalTAT / n << endl;
    }
};

int main() {

    SJFNonPreemptive obj;

    obj.inputProcesses();

    obj.calculateSJF();

    obj.displayGanttChart();

    obj.displayTable();

    return 0;
}