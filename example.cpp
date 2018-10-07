#include <iostream>
#include <unistd.h>
#include <signal.h>
#include "dcthread.h"

class ExampleThread : public DcThread {
public:
    void PrintName() {
        std::cout << "thread name: " << "example" << std::endl;
    }

private:
    void Run() {
        while(IsRunning()) {
            std::cout << "hello world." << std::endl;
            usleep(1000 * 1000);
        }
    };
};

ExampleThread example;

void HandleSIGINT() {
    example.PrintName();
    example.Stop();
}

void CatchSignal(int sign) {
    switch (sign) {
        case SIGINT:
            HandleSIGINT();
            break;
        default:
            break;
    }
}

int RegisteSIGINT() {
    //注册信号
    if (signal(SIGINT, CatchSignal) == SIG_ERR) {
        return -1;
    }
    return 0;
}


int main(int argc, char** args) {
    RegisteSIGINT();

    example.Start(); 


    sleep(1000);
    example.Stop();
    sleep(5);

    return 0;
}
