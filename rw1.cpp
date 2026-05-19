/* input.txt

(No input needed)

*/

#include <iostream>
using namespace std;

// Semaphore class
class Semaphore
{
    int value;

public:

    // Constructor
    Semaphore(int v)
    {
        value = v;
    }

    // wait() function
    bool wait()
    {
        if(value > 0)
        {
            value--;
            return true;
        }

        return false;
    }

    // signal() function
    void signal()
    {
        value++;
    }
};

// Reader Writer class
class ReaderWriter
{
    Semaphore mutex;
    Semaphore wrt;

    int readCount;
    int data;

public:

    // Constructor
    ReaderWriter() : mutex(1), wrt(1)
    {
        readCount = 0;
        data = 0;
    }

    // Reader function
    void reader(int id)
    {
        // Lock mutex
        if(!mutex.wait())
        {
            cout << "Reader " << id
                 << " waiting for mutex\n";

            return;
        }

        // Increase reader count
        readCount++;

        // First reader blocks writer
        if(readCount == 1)
        {
            if(!wrt.wait())
            {
                cout << "Reader " << id
                     << " waiting for writer\n";

                readCount--;

                mutex.signal();

                return;
            }
        }

        // Release mutex
        mutex.signal();

        // Reading section
        cout << "Reader " << id
             << " is reading data = "
             << data << endl;
    }

    // Stop reading
    void stopReading(int id)
    {
        mutex.wait();

        readCount--;

        cout << "Reader " << id
             << " finished reading\n";

        // Last reader allows writer
        if(readCount == 0)
        {
            wrt.signal();
        }

        mutex.signal();
    }

    // Writer function
    void writer(int id, int value)
    {
        // Lock writer
        if(!wrt.wait())
        {
            cout << "Writer " << id
                 << " waiting\n";

            return;
        }

        cout << "Writer " << id
             << " is writing\n";

        // Update data
        data = value;

        cout << "New data = "
             << data << endl;
    }

    // Stop writing
    void stopWriting(int id)
    {
        wrt.signal();

        cout << "Writer " << id
             << " finished writing\n";
    }
};

int main()
{
    ReaderWriter obj;

    // Readers start
    obj.reader(1);
    obj.reader(2);

    // Reader 1 exits
    obj.stopReading(1);

    // Writer tries
    obj.writer(1, 10);

    // Last reader exits
    obj.stopReading(2);

    // Writer writes again
    obj.writer(1, 10);

    obj.stopWriting(1);

    // Another reader
    obj.reader(3);

    obj.stopReading(3);

    return 0;
}