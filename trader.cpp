#include "receiver.h"
using namespace std;

int main() {

    Receiver rcv;
    sleep(5);
    string message = rcv.readIML();
    cout << message;
    return 0;
}
