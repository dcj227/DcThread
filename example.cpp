#include <iostream>

#include "dcthread.h"
#include <unistd.h>

class ExampleThread : public DcThread {
public:

private:
    void Run() {
        while(IsRunning()) {
            std::cout << "hello world." << std::endl;
            usleep(100 * 1000);
        }
    };
};

int main(int argc, char** args) {
    ExampleThread example;
    example.Start(); 

    sleep(1);
    example.Stop();
    sleep(5);

    return 0;
}
