#include <iostream>
using namespace std;

class LRU
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

        // initialize frames with -1
        for(int i = 0; i < f; i++)
        {
            frames[i] = -1;
        }

        int pageFault = 0;

        for(int i = 0; i < n; i++)
        {
            int found = 0;

            // CHECK IF PAGE ALREADY EXISTS
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

                // FIRST CHECK EMPTY FRAME
                for(int j = 0; j < f; j++)
                {
                    if(frames[j] == -1)
                    {
                        index = j;
                        break;
                    }
                }

                // IF NO EMPTY FRAME -> APPLY LRU
                if(index == -1)
                {
                    int leastRecent = i;
                    int lruIndex;

                    for(int j = 0; j < f; j++)
                    {
                        int k;

                        // search backward
                        for(k = i - 1; k >= 0; k--)
                        {
                            if(frames[j] == pages[k])
                            {
                                break;
                            }
                        }

                        // smaller k = used longer ago
                        if(k < leastRecent)
                        {
                            leastRecent = k;
                            lruIndex = j;
                        }
                    }

                    index = lruIndex;
                }

                // REPLACE PAGE
                frames[index] = pages[i];

                pageFault++;
            }

            // DISPLAY FRAMES
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
    LRU obj;
    obj.solve();

    return 0;
}