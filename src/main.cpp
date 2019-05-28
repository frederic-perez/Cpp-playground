// --

#include <array>
#include <iostream>

#include "convert-ASCII-OFF-to-binary-OFF.h"
#include "convert-ASCII-OFF-to-binary-PLY.h"
#include "convert-ASCII-PLY-to-binary-PLY.h"
#include "convert-binary-OFF-to-binary-PLY.h"
#include "convert-binary-PLY-to-ASCII-OFF.h"
#include "enum-class-iteration++.h"
#include "spy.h"

#undef FPCX_JUST_ASCII_OFF_TO_BINARY_PLY_20190410
#if defined(FPCX_JUST_ASCII_OFF_TO_BINARY_PLY_20190410)

int
main(int argc, char* argv[])
{
  if (argc != 3) {
    std::cerr << "Error: Wrong number of parameters\n"
              << "Usage: <progname> <filename-ASCII.off> <filename-binary.ply>\n";
    return EXIT_FAILURE;
  }
  const std::string filename_in = argv[1];
  const std::string filename_out = argv[2];
  // io::convert_ASCII_OFF_to_binary_OFF(filename_in, filename_out);
  io::convert_ASCII_OFF_to_binary_PLY(filename_in, filename_out);
  // io::convert_ASCII_PLY_to_binary_PLY(filename_in, filename_out);
  return EXIT_SUCCESS;
}

#else

int
main(int, char*[])
{
  std::cout << "Hello, Cpp-playground!\n" << std::endl;

  enums::ExamplesOfEnumClassAsIntegral();
  enums::ExamplesOfEnumClassIteration();
  std::cout << std::endl;

#  if defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
  size_t vm, rss;
  spy::process_memory_usage(vm, rss);
  std::cout << "Memory usage: vm=" << vm << "; rss=" << rss << '\n' << std::endl;
#  endif

  const std::array<std::string, 3> filename_roots{{"boxcube", "dodecahedron", "icosahedron"}};
  for (const auto& filename_root : filename_roots) {
    std::clog << "Dealing with `" << filename_root << "`:" << std::endl;

    const std::string filename_in_ASCII_OFF = filename_root + "-ASCII.off";
    const std::string filename_out_from_ASCII_OFF_to_binary_PLY = filename_root + "--from-ASCII-OFF--binary.ply";
    io::convert_ASCII_OFF_to_binary_PLY(filename_in_ASCII_OFF, filename_out_from_ASCII_OFF_to_binary_PLY);

    const std::string filename_out_from_ASCII_OFF_to_binary_OFF = filename_root + "--from-ASCII-OFF--binary.off";
    io::convert_ASCII_OFF_to_binary_OFF(filename_in_ASCII_OFF, filename_out_from_ASCII_OFF_to_binary_OFF);

    const std::string filename_out_from_binary_OFF_to_binary_PLY = filename_root + "--from-binary-OFF--binary.ply";
    io::convert_binary_OFF_to_binary_PLY(
      filename_out_from_ASCII_OFF_to_binary_OFF, filename_out_from_binary_OFF_to_binary_PLY);

    const std::string filename_out_from_binary_PLY_to_ASCII_OFF = filename_root + "--from-binary-PLY--ASCII.off";
    io::convert_binary_PLY_to_ASCII_OFF(
      filename_out_from_ASCII_OFF_to_binary_PLY, filename_out_from_binary_PLY_to_ASCII_OFF);

    std::clog << std::endl;
  }

  std::cout << "Bye, Cpp-playground!" << std::endl;
  return EXIT_SUCCESS;
}

#endif

// -- eof
