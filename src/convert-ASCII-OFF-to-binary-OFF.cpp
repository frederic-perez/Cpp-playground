#include <array>
#include <fstream>
#include <iostream>
#include <sstream>

#if defined(_MSC_VER)
#  include <iso646.h> // not
#endif

#include "convert-ASCII-OFF-to-binary-OFF.h"

void
io::convert_ASCII_OFF_to_binary_OFF(const std::string& filename_in, const std::string& filename_out)
{
  std::clog << __func__ << " starts..." << std::endl;

  std::ostringstream oss;

  // From the main page http://www.holmes3d.net/graphics/offfiles/, (c) Ryan Holmes
  // there is the link to http://www.holmes3d.net/graphics/offfiles/OFFLoading.txt
  // from which we base the code of this function

  std::ifstream file_in(filename_in);
  if (not file_in.is_open()) {
    std::cerr << "Could not open file `" << filename_in << "`. Exiting...\n";
    return;
  }

  std::ofstream file_out(filename_out, std::ios::out | std::ios::binary);
  if (not file_out.is_open()) {
    std::cerr << "Could not open file `" << filename_out << "`. Exiting...\n";
    return;
  }

  std::string word;
  file_in >> word;
  if (word != "OFF") {
    std::cerr << "File `" << filename_in << "` does not start with `OFF`. Exiting...\n";
    return;
  }

  oss << word << std::endl;

  file_out << "OFF BINARY\n";

  int num_points;
  int num_faces;
  int num_edges;
  file_in >> num_points >> num_faces >> num_edges;

  if (num_points < 1 || num_faces < 1) {
    std::cerr << "File `" << filename_in << "` has no points or no faces. Exiting...\n";
    return;
  }

  oss << num_points << ' ' << num_faces << ' ' << num_edges << std::endl;

  file_out.write(reinterpret_cast<char*>(&num_points), sizeof(int));
  file_out.write(reinterpret_cast<char*>(&num_faces), sizeof(int));
  file_out.write(reinterpret_cast<char*>(&num_edges), sizeof(int));

  std::array<float, 3> point;
  for (int i = 0; i < num_points; ++i) {
    file_in >> point[0] >> point[1] >> point[2];
    oss << point[0] << ' ' << point[1] << ' ' << point[2] << std::endl;
    file_out.write(reinterpret_cast<char*>(&point), sizeof(point));
  }

  int num_vertices;
  int index;
  std::string rest_of_line;
  for (int i = 0; i < num_faces; ++i) {
    file_in >> num_vertices;
    oss << "<<" << i << ">> " << num_vertices << ' ';
    file_out.write(reinterpret_cast<const char*>(&num_vertices), sizeof(num_vertices));
    for (int j = 0; j < num_vertices; ++j) {
      file_in >> index;
      oss << index << ' ';
      file_out.write(reinterpret_cast<char*>(&index), sizeof(index));
      if (file_out.bad()) {
        std::cerr << "Error: When i = " << i << " and j = " << j << ", writing to `" << filename_out
                  << "` failed -- Exiting...\n";
        return;
      }
    }
    oss << std::endl;

    getline(file_in, rest_of_line);
  }

  file_in.close();
  if (!file_in) {
    std::cerr << "Error: Reading from file `" << filename_in << "` failed";
  }

  file_out.close();
  if (!file_out) {
    std::cerr << "Error: Writing to file `" << filename_out << "` failed";
  }

  if (const bool spy = false) {
    std::clog << "Contents of input file was found to be as follows:\n" << oss.str();
  }

  std::clog << __func__ << " finished" << std::endl;
}
