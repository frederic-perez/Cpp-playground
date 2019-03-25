#ifndef CPP_PLAYGROUND_CONVERT_OFF_TO_PLY_H
#define CPP_PLAYGROUND_CONVERT_OFF_TO_PLY_H

#include <string>

namespace io {

void
convert_ASCII_OFF_to_binary_PLY(
  const std::string& filename_off,
  const std::string& filename_ply);

} // namespace io

#endif // CPP_PLAYGROUND_CONVERT_OFF_TO_PLY_H
