// CppUtility.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "spdlog/spdlog.h"

#include "utl/ProcessUtility.h"
#include "objects/TestObject.h"

int main()
{
    spdlog::info("Welcome to spdlog!");
    spdlog::error("Some error message with arg: {}", 1);

    spdlog::warn("Easy padding in numbers like {:08d}", 12);
    spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    spdlog::info("Support for floats {:03.2f}", 1.23456);
    spdlog::info("Positional args are {1} {0}..", "too", "supported");
    spdlog::info("{:<30}", "left aligned");

    spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    spdlog::debug("This message should be displayed..");

    // change log pattern
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

    // Compile time log levels
    // define SPDLOG_ACTIVE_LEVEL to desired level
    SPDLOG_TRACE("Some trace message with param {}", 42);
    SPDLOG_DEBUG("Some debug message");

    auto baseline = GetCurrentMemoryUsage();
    std::cout << "Base memory usage = " << std::to_string(baseline) << '\n';

    auto* comp = new ComplicatedObject[100000];
    for (int i = 0; i < 100000; ++i) {
        auto x = comp[i].CalculateTruth();
    }
    auto current = GetCurrentMemoryUsage();
    std::cout << "Sizeof() operator = " << std::to_string(sizeof(comp[0])) << '\n';
    std::cout << "Memory usage      = " << std::to_string(current) << '\n' << "-------------------------------------\n";
    std::cout << "Allocated size: " << std::to_string(current - baseline) << '\n' << '\n';

    auto* comp2 = new ComplicatedObject[100000];
    auto current2 = GetCurrentMemoryUsage();
    for (int i = 0; i < 100000; ++i) {
        auto x = comp2[i].CalculateTruth();
    }
    std::cout << "Sizeof() operator = " << std::to_string(sizeof(comp2[0])) << '\n';
    std::cout << "Memory usage      = " << std::to_string(current2) << '\n' << "-------------------------------------\n";
    std::cout << "Allocated size: " << std::to_string(current2 - current) << '\n';

    /* {
      auto newmem = new char[1024 * 100 * 100];
      memset(newmem, 1, static_cast<size_t>(1024 * 100 * 100));
      auto current = GetCurrentMemoryUsage();
      auto peak = GetMaximumMemoryUsage();
      std::cout << "Current After large allocation " << std::to_string(current) << '\n';
      std::cout << "Peak After large allocation    " << std::to_string(peak) << '\n';
      delete[] newmem;
  }
  {
      auto newmem = new char[1024 * 1 * 100];
      memset(newmem, 1, static_cast<size_t>(1024 * 100 * 1));
      auto current = GetCurrentMemoryUsage();
      auto peak = GetMaximumMemoryUsage();
      std::cout << "Current After small allocation " << std::to_string(current) << '\n';
      std::cout << "Peak After small allocation    " << std::to_string(peak) << '\n';
      delete[] newmem;
  }*/

  /*for (int i = 0; i < 100; ++i) {
      auto* newmem = new char[1024*100];
      memset(newmem, 1, static_cast<size_t>(1024*100));
      auto size = getCurrentRSS();
      std::cout << "Base usage = " << std::to_string(baseline) << " Current memory usage = " << std::to_string(size) << '\n';
  }*/
}