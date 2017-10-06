#include <iostream>

#include "enum-class-iteration.h"

void
enums::ExamplesOfEnumClassIteration() {
  using namespace enums;
  std::cout
    << "all_planets.size() = " << all_planets.size() << "\n"
    << "count<Planet>() = " << count<Planet>() << std::endl;
  for (const auto planet : all_planets)
    for (const auto opposite : all_opposites)
      std::cout << "planet as size_t: " << static_cast<size_t>(planet)
                << ", opposite as size_t: " << static_cast<size_t>(opposite)
                << std::endl;
}
