#include <iostream>

#include <chrono>
#include <thread>

auto main(int argc, char** argv) -> int {
  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "called" << std::endl;
  }
}