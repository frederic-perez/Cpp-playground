#include <fstream>
#include <ios>
#include <string>
#if defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
#  include <unistd.h>
#endif

#include "spy.h"

#if defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
// Code based on
// https://stackoverflow.com/questions/669438/how-to-get-memory-usage-at-run-time-in-c
//
void
spy::process_memory_usage(size_t& vm_usage, size_t& resident_set)
{
  // 'file' stat seems to give the most reliable results
  //
  std::ifstream stat_stream("/proc/self/stat", std::ios_base::in);

  // dummy vars for leading entries in stat that we don't care about
  //
  std::string pid, comm, state, ppid, pgrp, session, tty_nr;
  std::string tpgid, flags, minflt, cminflt, majflt, cmajflt;
  std::string utime, stime, cutime, cstime, priority, nice;
  std::string O, itrealvalue, starttime;

  // the two fields we want
  //
  unsigned long vsize;
  long rss;

  stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr >> tpgid >> flags >> minflt >> cminflt
    >> majflt >> cmajflt >> utime >> stime >> cutime >> cstime >> priority >> nice >> O >> itrealvalue >> starttime
    >> vsize >> rss; // don't care about the rest

  stat_stream.close();

  vm_usage = vsize / 102;
  const long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
  resident_set = static_cast<unsigned long>(rss) * static_cast<unsigned long>(page_size_kb);
}
#endif