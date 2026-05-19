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

// Producer Consumer class
class ProducerConsumer
{
    Semaphore empty;
    Semaphore full;
    Semaphore mutex;

    int buffer[5];
    int in;
    int out;
    int size;

public:

    // Constructor
    ProducerConsumer() : empty(5), full(0), mutex(1)
    {
        in = 0;
        out = 0;
        size = 5;
    }

    // Producer function
    void produce(int item)
    {
        // Check empty space
        if(!empty.wait())
        {
            cout << "Buffer Full\n";
            return;
        }

        // Lock buffer
        mutex.wait();

        // Insert item
        buffer[in] = item;

        cout << "Produced : "
             << item << endl;

        // Move in pointer
        in = (in + 1) % size;

        // Unlock buffer
        mutex.signal();

        // Increase full count
        full.signal();
    }

    // Consumer function
    void consume()
    {
        // Check full slots
        if(!full.wait())
        {
            cout << "Buffer Empty\n";
            return;
        }

        // Lock buffer
        mutex.wait();

        // Remove item
        int item = buffer[out];

        cout << "Consumed : "
             << item << endl;

        // Move out pointer
        out = (out + 1) % size;

        // Unlock buffer
        mutex.signal();

        // Increase empty count
        empty.signal();
    }
};

int main()
{
    ProducerConsumer obj;

    // Producing items
    obj.produce(10);
    obj.produce(20);
    obj.produce(30);

    // Consuming items
    obj.consume();
    obj.consume();

    // More production
    obj.produce(40);

    // More consumption
    obj.consume();
    obj.consume();

    return 0;
}