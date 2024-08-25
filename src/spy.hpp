#ifndef CPP_PLAYGROUND_SPY_HPP
#define CPP_PLAYGROUND_SPY_HPP

#include <cstddef> // size_t

#define SpyLine std::cerr << "@@@@ " << __FILE__ << ':' << __func__ << ":L" << __LINE__ << '\n';

namespace spy {

#if defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
void process_memory_usage(size_t& vm_usage, size_t& resident_set);
#endif

} // namespace spy

#endif // CPP_PLAYGROUND_SPY_H
