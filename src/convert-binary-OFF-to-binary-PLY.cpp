#include <fstream>
#include <iostream>
#include <sstream>

#if defined(_MSC_VER)
  #include <iso646.h> // not
#endif

#include "convert-binary-OFF-to-binary-PLY.h"

namespace {

void
save_ply_header(std::ofstream& file_out, int num_points, int num_faces)
{
  file_out << "ply\n";

  unsigned int an_int = 1;
  const auto* const ptr = reinterpret_cast<char*>(&an_int);
  file_out << "format "
    << (ptr[0] == 1 ? "binary_little_endian" : "binary_big_endian") << " 1.0\n";

  file_out
    << "element vertex " << num_points << "\n"
    << "property float x\n" 
    << "property float y\n"
    << "property float z\n"
    << "element face " << num_faces << "\n"
    << "property list uchar int vertex_indices\n"
    << "end_header\n";
}

} // namespace

void
io::convert_binary_OFF_to_binary_PLY(
  const std::string& filename_in_off,
  const std::string& filename_out_ply)
{
  std::clog << __func__ << " starts..." << std::endl;

  std::ostringstream oss;

  // From the main page http://www.holmes3d.net/graphics/offfiles/, (c) Ryan Holmes
  // there is the link to http://www.holmes3d.net/graphics/offfiles/OFFLoading.txt
  // from which we base the code of this function

  std::ifstream file_in(filename_in_off, std::ios::in | std::ios::binary);
  if (not file_in.is_open()) {
    std::cerr << "Could not open file `" << filename_in_off << "`. Exiting...\n";
    return;
  }

  std::ofstream file_out(filename_out_ply, std::ios::out | std::ios::binary);
  if (not file_out.is_open()) {
    std::cerr << "Could not open file `" << filename_out_ply << "`. Exiting...\n";
    return;
  }

  std::string line;
  getline(file_in, line);
  std::istringstream iss(line);
  std::string word_1st, word_2nd;
  iss >> word_1st >> word_2nd;
  if (word_1st != "OFF" || word_2nd != "BINARY") {
    std::cerr << "File `" << filename_in_off << "` does not start with `OFF BINARY`. Exiting...\n";
    return;
  }

  oss << word_1st << ' ' << word_2nd << std::endl;

  int num_points, num_faces, num_edges;
  file_in.read(reinterpret_cast<char*>(&num_points), sizeof(num_points));
  file_in.read(reinterpret_cast<char*>(&num_faces), sizeof(num_faces));
  file_in.read(reinterpret_cast<char*>(&num_edges), sizeof(num_edges));

  if (num_points < 1 || num_faces < 1) {
    std::cerr << "File `" << filename_in_off << "` has no points or no faces. Exiting...\n";
    return;
  }

  oss << num_points << ' ' << num_faces << ' ' << num_edges << std::endl;

  save_ply_header(file_out, num_points, num_faces);

  float point[3];
  for (int i = 0; i < num_points; ++i) {
    file_in.read(reinterpret_cast<char*>(&point), 3*sizeof(float));
    oss << point[0] << ' ' << point[1] << ' ' << point[2] << std::endl;
    file_out.write(reinterpret_cast<char*>(&point), 3*sizeof(float));
  }

  int num_vertices, index;
  for (int i = 0; i < num_faces; ++i) {
    file_in.read(reinterpret_cast<char*>(&num_vertices), sizeof(num_vertices));
    oss << "<<" << i << ">> " << num_vertices << ' ';
    file_out.write(reinterpret_cast<const char*>(&num_vertices), sizeof(unsigned char));
    for (int j = 0; j < num_vertices; ++j) {
      file_in.read(reinterpret_cast<char*>(&index), sizeof(index));
      if (!file_in) {
        std::cerr << "Error: When i = " << i << ", only " << file_in.gcount()
          << " elements could be read -- Exiting...\n";
        return;
      }
      oss << index << ' ';
      file_out.write(reinterpret_cast<char*>(&index), sizeof(index));
    }
    oss << std::endl;
  }

  file_in.close();
  file_out.close();

  if (const bool spy = false) {
    std::clog << "Contents of input file was found to be as follows:\n" << oss.str();
  }

  std::clog << __func__ << " finished" << std::endl;
}
