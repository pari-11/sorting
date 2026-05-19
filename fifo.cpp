#include <iostream>
using namespace std;

class FIFO
{
    int pages[50];      // page reference string
    int frames[20];     // memory frames

public:

    void solve()
    {
        int n, f;

        cout << "Enter number of pages: ";
        cin >> n;

        cout << "Enter page reference string:\n";

        for(int i = 0; i < n; i++)
        {
            cin >> pages[i];
        }

        cout << "Enter number of frames: ";
        cin >> f;

        // initialize frames as empty
        for(int i = 0; i < f; i++)
        {
            frames[i] = -1;
        }

        int pageFault = 0;

        // points to next replacement position
        int front = 0;

        // process every page
        for(int i = 0; i < n; i++)
        {
            int found = 0;

            // CHECK PAGE HIT
            for(int j = 0; j < f; j++)
            {
                if(frames[j] == pages[i])
                {
                    found = 1;
                    break;
                }
            }

            // PAGE FAULT
            if(found == 0)
            {
                // replace using FIFO
                frames[front] = pages[i];

                // move front forward
                front = (front + 1) % f;

                pageFault++;
            }

            // display frames
            cout << "\nAfter page " << pages[i] << " : ";

            for(int j = 0; j < f; j++)
            {
                if(frames[j] != -1)
                    cout << frames[j] << " ";
                else
                    cout << "- ";
            }
        }

        cout << "\n\nTotal Page Faults = " << pageFault;
    }
};

int main()
{
    FIFO obj;

    obj.solve();

    return 0;
}