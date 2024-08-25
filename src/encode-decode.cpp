#include <fstream>
#include <iostream>

#include "encode-decode.hpp"

void
io::encode(const std::string& filename_in, const std::string& filename_out)
{
  std::clog << __func__ << " starts..." << std::endl;

  std::ifstream file_in(filename_in, std::ios::in | std::ios::binary);
  if (not file_in.is_open()) {
    std::cerr << "Could not open file `" << filename_in << "`. Exiting...\n";
    return;
  }

  std::ofstream file_out(filename_out, std::ios::out | std::ios::binary);
  if (not file_out.is_open()) {
    std::cerr << "Could not open file `" << filename_out << "`. Exiting...\n";
    return;
  }

  char byte;
  while (file_in.get(byte)) {
    byte = -byte;
    file_out.put(byte);
  }

  file_in.close();
  file_out.close();

  std::clog << __func__ << " finished" << std::endl;
}

void
io::decode(const std::string& filename_in, const std::string& filename_out)
{
  std::clog << __func__ << " starts..." << std::endl;

  std::ifstream file_in(filename_in, std::ios::in | std::ios::binary);
  if (not file_in.is_open()) {
    std::cerr << "Could not open file `" << filename_in << "`. Exiting...\n";
    return;
  }

  std::ofstream file_out(filename_out, std::ios::out | std::ios::binary);
  if (not file_out.is_open()) {
    std::cerr << "Could not open file `" << filename_out << "`. Exiting...\n";
    return;
  }

  char byte;
  while (file_in.get(byte)) {
    byte = -byte;
    file_out.put(byte);
  }

  file_in.close();
  file_out.close();

  std::clog << __func__ << " finished" << std::endl;
}
