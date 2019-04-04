#include <array>
#include <fstream>
#include <iostream>
#include <sstream>

#if defined(_MSC_VER)
  #include <iso646.h> // not
#endif

#include "convert-binary-PLY-to-ASCII-OFF.h"

namespace {

bool
outputErrorAndReturnFalse(const std::string& message)
{
  std::cerr << "Error: " << message << " -- Exiting...\n";
  return false;
}

void
getline_and_update(
  std::ifstream& file_in,
  std::istringstream& iss)
{
  std::string line;
  // '- This object can't be static to allow parallel calls to `read_ply_header`
  getline(file_in, line);
  iss.clear();
  iss.str(line);
}

bool
read_ply_header(
  std::ifstream& file_in,
  int& num_points,
  int& num_faces)
{
  std::istringstream iss;
  getline_and_update(file_in, iss);
  std::string word_1, word_2, word_3, word_4, word_5;
  iss >> word_1;
  if (word_1 != "ply" && word_1 != "PLY") {
    return outputErrorAndReturnFalse("Expected `ply` or `PLY` keyword.");
  }

  getline_and_update(file_in, iss);
  iss >> word_1 >> word_2 >> word_3;
  if (word_1 != "format" or word_2 != "binary_little_endian" or word_3 != "1.0") {
    return outputErrorAndReturnFalse("Expected `format binary_little_endian 1.0`");
  }

  getline_and_update(file_in, iss);
  iss >> word_1 >> word_2 >> num_points;
  if (word_1 != "element" or word_2 != "vertex") {
    return outputErrorAndReturnFalse("Expected `element vertex <n>`");
  }

  const std::array<char, 3> axes{ {'x', 'y', 'z'} };
  for (const auto axis : axes) {
    getline_and_update(file_in, iss);
    char c;
    iss >> word_1 >> word_2 >> c;
    if (word_1 != "property" or word_2 != "float" or c != axis) {
      return outputErrorAndReturnFalse(std::string("Expected `property float ") + std::to_string(c) + "`");
    }
  }

  getline_and_update(file_in, iss);
  iss >> word_1 >> word_2 >> num_faces;
  if (word_1 != "element" or word_2 != "face") {
    return outputErrorAndReturnFalse("Expected `element face <n>`");
  }

  getline_and_update(file_in, iss);
  iss >> word_1 >> word_2 >> word_3 >> word_4 >> word_5;
  if (word_1 != "property" or word_2 != "list" or word_3 != "uchar" or word_4 != "int" or word_5 != "vertex_indices") {
    return outputErrorAndReturnFalse("Expected `property list uchar int vertex_indices`");
  }

  getline_and_update(file_in, iss);
  iss >> word_1;
  if (word_1 != "end_header") {
    return outputErrorAndReturnFalse("Expected `end_header`");
  }

  return true;
}

} // namespace

void
io::convert_binary_PLY_to_ASCII_OFF(
  const std::string& filename_in_ply,
  const std::string& filename_out_off)
{
  std::clog << __func__ << " starts..." << std::endl;

  std::ostringstream oss;

  std::ifstream file_in(filename_in_ply, std::ios::in | std::ios::binary);
  if (not file_in.is_open()) {
    std::cerr << "Could not open file `" << filename_in_ply << "`. Exiting...\n";
    return;
  }

  std::ofstream file_out(filename_out_off, std::ios::out);
  if (not file_out.is_open()) {
    std::cerr << "Could not open file `" << filename_out_off << "`. Exiting...\n";
    return;
  }

  int num_points = 0, num_faces = 0, num_edges = 0;
  const bool succeeded = read_ply_header(file_in, num_points, num_faces);
  if (not succeeded) {
    std::cerr << "Could not parse the header from file `" << filename_in_ply << "`. Exiting...\n";
    return;
  }
  if (num_points < 1 or num_faces < 1) {
    std::cerr << "File `" << filename_in_ply << "` has no points or no faces. Exiting...\n";
    return;
  }

  oss << "<<<snipped header>>>" << std::endl;

  file_out << "OFF" << std::endl;
  file_out << num_points << ' ' << num_faces << ' ' << num_edges << std::endl;

  float point[3];
  for (int i = 0; i < num_points; ++i) {
    file_in.read(reinterpret_cast<char*>(&point), sizeof(point));
    if (!file_in) {
      std::cerr << "Error: When i = " << i << ", only " << file_in.gcount()
        << " elements could be read -- Exiting...\n";
      return;
    }
    oss << point[0] << ' ' << point[1] << ' ' << point[2] << std::endl;
    file_out << point[0] << ' ' << point[1] << ' ' << point[2] << std::endl;
  }

  unsigned char num_vertices_uc;
  int num_vertices, index;
  for (int i = 0; i < num_faces; ++i) {
    file_in.read(reinterpret_cast<char*>(&num_vertices_uc), sizeof(unsigned char));
    num_vertices = static_cast<int>(num_vertices_uc);
    oss << "<<" << i << ">> " << num_vertices << ' ';
    file_out << num_vertices << ' ';
    for (int j = 0; j < num_vertices; ++j) {
      file_in.read(reinterpret_cast<char*>(&index), sizeof(index));
      if (!file_in) {
        std::cerr << "Error: When i = " << i << ", only " << file_in.gcount()
          << " elements could be read -- Exiting...\n";
        return;
      }
      oss << index;
      file_out << index;
      if (index < num_faces - 1) {
        oss << ' ';
        file_out << ' ';
      }
    }
    oss << std::endl;
    file_out << std::endl;
  }

  file_in.close();
  file_out.close();

  if (const bool spy = false) {
    std::clog << "Contents of input file was found to be as follows:\n" << oss.str();
  }

  std::clog << __func__ << " finished" << std::endl;
}
