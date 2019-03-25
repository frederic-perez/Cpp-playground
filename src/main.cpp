// --

#include <array>
#include <iostream>

#include "convert-off-to-ply.h"
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

  const std::array<std::string, 3> filename_roots{{
    "boxcube", "dodecahedron", "icosahedron"
  }};
  for (const auto& filename_root : filename_roots) {
    const std::string filename_in_off = filename_root + ".off";
    const std::string filename_out_ply = filename_root + ".ply";
    io::convert_ASCII_OFF_to_binary_PLY(filename_in_off, filename_out_ply);
  }

  std::cout << "Bye, Cpp-playground!" << std::endl;
  return EXIT_SUCCESS;
}

// -- eof
