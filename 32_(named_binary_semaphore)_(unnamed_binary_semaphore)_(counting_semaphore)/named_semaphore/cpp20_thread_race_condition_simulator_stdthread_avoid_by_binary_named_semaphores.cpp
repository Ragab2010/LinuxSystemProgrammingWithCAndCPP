#include <iostream>
#include <thread>
#include <semaphore>

int counter = 0;  // Global variable
std::binary_semaphore mutex(1);  // Binary semaphore for synchronization

void increment(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        mutex.acquire();  // Acquire mutex
        counter++;
        mutex.release();  // Release mutex
    }
}

void decrement(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        mutex.acquire();  // Acquire mutex
        counter--;
        mutex.release();  // Release mutex
    }
}

int main() {
    int num_iterations = 100000;  // Number of iterations per thread
    std::cout << "Two threads:" << std::endl;
    std::cout << "   One thread increment: " << num_iterations << std::endl;
    std::cout << "Second thread decrement: " << num_iterations << std::endl;
    std::cout << "The correct counter value: 0" << std::endl;
    std::thread thread1(increment, num_iterations);
    std::thread thread2(decrement, num_iterations);

    thread1.join();
    thread2.join();

    std::cout << "Final counter value: " << counter << std::endl;

    return 0;
}
