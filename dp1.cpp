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

// Dining Philosopher class
class DiningPhilosopher
{
    Semaphore chopstick[5];

public:

    // Constructor
    DiningPhilosopher()
        : chopstick{Semaphore(1), Semaphore(1),
                     Semaphore(1), Semaphore(1),
                     Semaphore(1)}
    {
    }

    // Philosopher function
    void eat(int id)
    {
        int left = id;
        int right = (id + 1) % 5;

        cout << "Philosopher "
             << id
             << " is thinking\n";

        // Pick left chopstick
        if(!chopstick[left].wait())
        {
            cout << "Left chopstick not available\n";
            return;
        }

        cout << "Philosopher "
             << id
             << " picked left chopstick "
             << left << endl;

        // Pick right chopstick
        if(!chopstick[right].wait())
        {
            cout << "Right chopstick not available\n";

            // Release left chopstick
            chopstick[left].signal();

            return;
        }

        cout << "Philosopher "
             << id
             << " picked right chopstick "
             << right << endl;

        // Eating
        cout << "Philosopher "
             << id
             << " is eating\n";

        // Release chopsticks
        chopstick[left].signal();
        chopstick[right].signal();

        cout << "Philosopher "
             << id
             << " released chopsticks\n";
    }
};

int main()
{
    DiningPhilosopher obj;

    obj.eat(0);
    obj.eat(1);
    obj.eat(2);
    obj.eat(3);
    obj.eat(4);

    return 0;
}