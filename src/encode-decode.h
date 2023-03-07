#ifndef CPP_PLAYGROUND_ENCODE_DECODE_H
#define CPP_PLAYGROUND_ENCODE_DECODE_H

#include <string>

namespace io {

void encode(const std::string& filename_in, const std::string& filename_out);
void decode(const std::string& filename_in, const std::string& filename_out);

} // namespace io

#endif
