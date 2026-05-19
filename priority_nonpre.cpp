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
    int priority;   // Priority
    int completion; // Completion Time
    int turnaround; // Turnaround Time
    int waiting;    // Waiting Time
    bool completed; // Check completion
};

// Class for Non-Preemptive Priority Scheduling
class PriorityNonPreemptive {

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

            cout << "Priority: ";
            cin >> p[i].priority;

            p[i].completed = false;
        }
    }

    // Function to calculate scheduling
    void calculatePriority() {

        int currentTime = 0;
        int completedCount = 0;

        // Starting time
        ganttTime[0] = 0;

        // Run until all processes complete
        while (completedCount < n) {

            int highest = -1;
            int highestPriority = INT_MAX;

            // Find highest priority process
            for (int i = 0; i < n; i++) {

                if (p[i].arrival <= currentTime &&
                    p[i].completed == false) {

                    // Smaller number = higher priority
                    if (p[i].priority <
                        highestPriority) {

                        highestPriority =
                            p[i].priority;

                        highest = i;
                    }
                }
            }

            // If no process arrived
            if (highest == -1) {

                currentTime++;
            }

            else {

                // Add to Gantt Chart
                ganttProcess[ganttIndex] =
                    p[highest].id;

                ganttTime[ganttIndex] =
                    currentTime;

                ganttIndex++;

                // Execute full burst time
                currentTime =
                    currentTime +
                    p[highest].burst;

                // Completion Time
                p[highest].completion =
                    currentTime;

                // Turnaround Time
                p[highest].turnaround =
                    p[highest].completion -
                    p[highest].arrival;

                // Waiting Time
                p[highest].waiting =
                    p[highest].turnaround -
                    p[highest].burst;

                // Mark completed
                p[highest].completed = true;

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

        cout << "\n========== NON PREEMPTIVE PRIORITY TABLE ==========\n\n";

        cout << left
             << setw(10) << "Process"
             << setw(10) << "AT"
             << setw(10) << "BT"
             << setw(10) << "Priority"
             << setw(10) << "CT"
             << setw(10) << "TAT"
             << setw(10) << "WT"
             << endl;

        // Print details
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

    PriorityNonPreemptive obj;

    obj.inputProcesses();

    obj.calculatePriority();

    obj.displayGanttChart();

    obj.displayTable();

    return 0;
}