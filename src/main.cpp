#include <array>
#include <iostream>
#include <string>

#include "convert-ASCII-OFF-to-binary-OFF.hpp"
#include "convert-ASCII-OFF-to-binary-PLY.hpp"
#include "convert-ASCII-PLY-to-binary-PLY.hpp"
#include "convert-binary-OFF-to-binary-PLY.hpp"
#include "convert-binary-PLY-to-ASCII-OFF.hpp"
#include "encode-decode.hpp"
#include "spy.hpp"

#undef FPCX_JUST_ASCII_OFF_TO_BINARY_PLY_20190410
#if defined(FPCX_JUST_ASCII_OFF_TO_BINARY_PLY_20190410)

auto
main(int argc, char* argv[])
-> int
{
  if (argc != 3) {
    std::cerr << "Error: Wrong number of parameters\n"
              << "Usage: <progname> <filename-ASCII-in.off> <filename-binary-out.ply>\n";
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

auto
main(int, char*[])
-> int
{
  std::cout << "Hello, Cpp-playground!\n" << std::endl;

#  if defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
  size_t vm, rss;
  spy::process_memory_usage(vm, rss);
  std::cout << "Memory usage: vm=" << vm << "; rss=" << rss << '\n' << std::endl;
#  endif

  using namespace std::string_literals;
  const std::array filename_roots{"boxcube"s, "dodecahedron"s, "icosahedron"s};
  for (const auto& filename_root : filename_roots) {
    std::clog << "Dealing with `" << filename_root << "`:" << std::endl;

    const auto filename_in_ASCII_OFF = filename_root + "-ASCII.off";
    const auto filename_out_from_ASCII_OFF_to_binary_PLY = filename_root + "--from-ASCII-OFF--binary.ply";
    io::convert_ASCII_OFF_to_binary_PLY(filename_in_ASCII_OFF, filename_out_from_ASCII_OFF_to_binary_PLY);

    const auto filename_out_from_ASCII_OFF_to_binary_OFF = filename_root + "--from-ASCII-OFF--binary.off";
    io::convert_ASCII_OFF_to_binary_OFF(filename_in_ASCII_OFF, filename_out_from_ASCII_OFF_to_binary_OFF);

    const auto filename_out_from_binary_OFF_to_binary_PLY = filename_root + "--from-binary-OFF--binary.ply";
    io::convert_binary_OFF_to_binary_PLY(
      filename_out_from_ASCII_OFF_to_binary_OFF, filename_out_from_binary_OFF_to_binary_PLY);

    const auto filename_out_from_binary_PLY_to_ASCII_OFF = filename_root + "--from-binary-PLY--ASCII.off";
    io::convert_binary_PLY_to_ASCII_OFF(
      filename_out_from_ASCII_OFF_to_binary_PLY, filename_out_from_binary_PLY_to_ASCII_OFF);

    const auto filename_out_from_ASCII_OFF_to_binary_PLY_encoded = filename_out_from_ASCII_OFF_to_binary_PLY + ".enc";
    io::encode(filename_out_from_ASCII_OFF_to_binary_PLY, filename_out_from_ASCII_OFF_to_binary_PLY_encoded);
    const auto filename_out_from_ASCII_OFF_to_binary_PLY_decoded = filename_out_from_ASCII_OFF_to_binary_PLY_encoded + ".dec";
    io::decode(filename_out_from_ASCII_OFF_to_binary_PLY_encoded, filename_out_from_ASCII_OFF_to_binary_PLY_decoded);

    std::clog << std::endl;
  }

  std::cout << "Bye, Cpp-playground!" << std::endl;
  return EXIT_SUCCESS;
}

#endif
