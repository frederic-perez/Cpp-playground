// --

#include <iostream>

#include "enum-class-iteration++.h"
#include "spy.h"

int
main(int /*argc*/, char* /*argv*/[])
{
  std::cout << "Hello, Cpp-playground!\n" << std::endl;

  enums::ExamplesOfEnumClassAsIntegral();
  enums::ExamplesOfEnumClassIteration();
  std::cout << std::endl;

#if defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
  size_t vm, rss;
  spy::process_memory_usage(vm, rss);
  std::cout << "Memory usage: vm=" << vm << "; rss=" << rss << '\n'
    << std::endl;
#endif

  std::cout << "Bye, Cpp-playground!" << std::endl;
  return EXIT_SUCCESS;
}

// -- eof
