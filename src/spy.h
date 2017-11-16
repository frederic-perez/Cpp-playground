#ifndef CPP_PLAYGROUND_SPY_H
#define CPP_PLAYGROUND_SPY_H

#include <cstddef> // size_t

#define SpyLine \
  std::cerr << "@@@@ " << __FILE__ << ':' << __func__ << ":L" << __LINE__ \
    << '\n';

namespace spy {

void
process_memory_usage(size_t& vm_usage, size_t& resident_set);

} // namespace spy

#endif // CPP_PLAYGROUND_SPY_H
