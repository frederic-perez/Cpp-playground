#include <array>
#include <fstream>
#include <iostream>
#include <sstream>

#if defined(_MSC_VER)
  #include <iso646.h> // not
#endif

#include "convert-ASCII-PLY-to-binary-PLY.h"

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
  std::string& texture_filename,
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
  if (word_1 != "format" or word_2 != "ascii" or word_3 != "1.0") {
    return outputErrorAndReturnFalse("Expected `format ascii 1.0`");
  }

  getline_and_update(file_in, iss);
  iss >> word_1 >> word_2 >> texture_filename;
  if (word_1 != "comment" or word_2 != "TextureFile") {
    return outputErrorAndReturnFalse("Expected `comment TextureFile <texture_filename>`");
  }

  getline_and_update(file_in, iss);
  iss >> word_1 >> word_2 >> num_points;
  if (word_1 != "element" or word_2 != "vertex") {
    return outputErrorAndReturnFalse("Expected `element vertex <n>`");
  }

  const std::array<char, 3> axes{ { 'x', 'y', 'z' } };
  for (const auto axis : axes) {
    getline_and_update(file_in, iss);
    char c;
    iss >> word_1 >> word_2 >> c;
    if (word_1 != "property" or word_2 != "float" or c != axis) {
      return outputErrorAndReturnFalse(std::string("Expected `property float ") + std::to_string(c) + "`");
    }
  }

  const std::array<std::string, 3> n_axes{ { "nx", "ny", "nz" } };
  for (const auto& n_axis : n_axes) {
    getline_and_update(file_in, iss);
    iss >> word_1 >> word_2 >> word_3;
    if (word_1 != "property" or word_2 != "float" or word_3 != n_axis) {
      return outputErrorAndReturnFalse(std::string("Expected `property float ") + n_axis + "`");
    }
  }

  const std::array<std::string, 2> textures{ { "texture_u", "texture_v" } };
  for (const auto& texture : textures) {
    getline_and_update(file_in, iss);
    iss >> word_1 >> word_2 >> word_3;
    if (word_1 != "property" or word_2 != "float" or word_3 != texture) {
      return outputErrorAndReturnFalse(std::string("Expected `property float ") + texture + "`");
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

void
save_ply_header(
  std::ofstream& file_out,
  const std::string& texture_filename,
  int num_points,
  int num_faces)
{
  file_out << "ply\n";

  unsigned int an_int = 1;
  const auto* const ptr = reinterpret_cast<char*>(&an_int);
  file_out << "format "
    << (ptr[0] == 1 ? "binary_little_endian" : "binary_big_endian") << " 1.0\n";

  file_out
    << "comment TextureFile " << texture_filename << '\n'
    << "element vertex " << num_points << '\n'
    << "property float x\n"
    << "property float y\n"
    << "property float z\n"
    << "property float nx\n"
    << "property float ny\n"
    << "property float nz\n"
    << "property float texture_u\n"
    << "property float texture_v\n"
    << "element face " << num_faces << '\n'
    << "property list uchar int vertex_indices\n"
    << "end_header\n";
}

} // namespace

void
io::convert_ASCII_PLY_to_binary_PLY(
  const std::string& filename_in,
  const std::string& filename_out)
{
  std::clog << __func__ << " starts..." << std::endl;

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

  std::string texture_filename;
  int num_points = 0, num_faces = 0;
  const bool succeeded =
    read_ply_header(file_in, texture_filename, num_points, num_faces);
  if (not succeeded) {
    std::cerr << "Could not parse the header from file `" << filename_in << "`. Exiting...\n";
    return;
  }
  if (num_points < 1 or num_faces < 1) {
    std::cerr << "File `" << filename_in << "` has no points or no faces. Exiting...\n";
    return;
  }

  save_ply_header(file_out, texture_filename, num_points, num_faces);

  float point_n_uv[3 + 3 + 2];
  for (int i = 0; i < num_points; ++i) {
    file_in
      >> point_n_uv[0] >> point_n_uv[1] >> point_n_uv[2] // x, y, z
      >> point_n_uv[3] >> point_n_uv[4] >> point_n_uv[5] // nx, ny, nz
      >> point_n_uv[6] >> point_n_uv[7];                 // u, v
    file_out.write(reinterpret_cast<char*>(&point_n_uv), sizeof(point_n_uv));
  }

  size_t num_vertices;
  int index;
  char tempBuf[128];
  for (int i = 0; i < num_faces; ++i) {
    file_in >> num_vertices;
    file_out.write(reinterpret_cast<const char*>(&num_vertices), sizeof(unsigned char));
    for (size_t j = 0; j < num_vertices; ++j) {
      file_in >> index;
      file_out.write(reinterpret_cast<char*>(&index), sizeof(int));
    }
    // Clear out any face color data by reading up to
    // the newline. 128 is probably considerably more
    // space than necessary, but better safe than
    // sorry.
    file_in.getline(tempBuf, 128);
  }

  file_in.close();
  file_out.close();

  std::clog << __func__ << " finished" << std::endl;
}
