#include <array>
#include <fstream>
#include <iostream>

#if defined(_MSC_VER)
#  include <iso646.h> // not
#endif

#include "convert-ASCII-OFF-to-binary-PLY.h"

namespace {

void
save_ply_header(std::ofstream& file_out, size_t num_points, size_t num_faces)
{
  file_out << "ply\n";

  unsigned int an_int = 1;
  const auto* const ptr = reinterpret_cast<char*>(&an_int);
  file_out << "format " << (ptr[0] == 1 ? "binary_little_endian" : "binary_big_endian") << " 1.0\n";

  file_out << "element vertex " << num_points << "\n"
           << "property float x\n"
           << "property float y\n"
           << "property float z\n"
           << "element face " << num_faces << "\n"
           << "property list uchar int vertex_indices\n"
           << "end_header\n";
}

} // namespace

void
io::convert_ASCII_OFF_to_binary_PLY(const std::string& filename_in_off, const std::string& filename_out_ply)
{
  std::clog << __func__ << " starts..." << std::endl;

  // From the main page http://www.holmes3d.net/graphics/offfiles/, (c) Ryan Holmes
  // there is the link to http://www.holmes3d.net/graphics/offfiles/OFFLoading.txt
  // from which we base the code of this function

  std::ifstream file_in(filename_in_off);
  if (not file_in.is_open()) {
    std::cerr << "Could not open file `" << filename_in_off << "`. Exiting...\n";
    return;
  }

  std::ofstream file_out(filename_out_ply, std::ios::out | std::ios::binary);
  if (not file_out.is_open()) {
    std::cerr << "Could not open file `" << filename_out_ply << "`. Exiting...\n";
    return;
  }

  std::string word;
  file_in >> word;
  if (word != "OFF") {
    std::cerr << "File `" << filename_in_off << "` does not start with `OFF`. Exiting...\n";
    return;
  }

  size_t num_points;
  size_t num_faces;
  size_t num_edges;
  file_in >> num_points >> num_faces >> num_edges;

  if (num_points < 1 || num_faces < 1) {
    std::cerr << "File `" << filename_in_off << "` has no points or no faces. Exiting...\n";
    return;
  }

  save_ply_header(file_out, num_points, num_faces);

  std::array<float, 3> point;
  for (size_t i = 0; i < num_points; ++i) {
    file_in >> point[0] >> point[1] >> point[2];
    file_out.write(reinterpret_cast<char*>(&point), sizeof point);
  }

  size_t num_vertices;
  int index;
  constexpr size_t one_two_eight = 128;
  std::array<char, one_two_eight> tempBuf;
  for (size_t i = 0; i < num_faces; ++i) {
    file_in >> num_vertices;
    file_out.write(reinterpret_cast<const char*>(&num_vertices), sizeof(unsigned char));
    for (size_t j = 0; j < num_vertices; ++j) {
      file_in >> index;
      file_out.write(reinterpret_cast<char*>(&index), sizeof index);
    }
    // Clear out any face color data by reading up to
    // the newline. 128 is probably considerably more
    // space than necessary, but better safe than
    // sorry.
    file_in.getline(tempBuf.data(), one_two_eight);
  }

  file_in.close();
  file_out.close();

  std::clog << __func__ << " finished" << std::endl;
}
