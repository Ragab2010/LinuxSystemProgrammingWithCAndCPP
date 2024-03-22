#include <iostream>
#include <thread>
#include <mutex>

int counter = 0;  // Global variable

void increment(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        counter++;
    }
}

void decrement(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        counter--;
    }
}

int main() {
    int num_iterations = 100000;  // Number of iterations per thread
        std::cout << "two threads:"<<std::endl;
    std::cout<<"   one thread increment: "<< num_iterations<<std::endl;
    std::cout<<"second thread decrement: "<< num_iterations<<std::endl;
    std::cout << "the Correct counter value: 0 "<< std::endl;
    std::thread thread1(increment, num_iterations);
    std::thread thread2(decrement, num_iterations);

    thread1.join();
    thread2.join();

    std::cout << "Final counter value: " << counter << std::endl;

    return 0;
}
