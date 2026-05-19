#include <iostream>
using namespace std;

class Optimal
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
                int index = -1;

                // CHECK EMPTY FRAME
                for(int j = 0; j < f; j++)
                {
                    if(frames[j] == -1)
                    {
                        index = j;
                        break;
                    }
                }

                // IF NO EMPTY FRAME -> APPLY OPTIMAL
                if(index == -1)
                {
                    int farthest = -1;
                    int replaceIndex;

                    // check every frame page
                    for(int j = 0; j < f; j++)
                    {
                        int k;

                        // search FORWARD
                        for(k = i + 1; k < n; k++)
                        {
                            if(frames[j] == pages[k])
                            {
                                break;
                            }
                        }

                        // if page never comes again
                        if(k == n)
                        {
                            replaceIndex = j;
                            break;
                        }

                        // page used farthest in future
                        if(k > farthest)
                        {
                            farthest = k;
                            replaceIndex = j;
                        }
                    }

                    index = replaceIndex;
                }

                // replace page
                frames[index] = pages[i];

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
    Optimal obj;
    obj.solve();

    return 0;
}