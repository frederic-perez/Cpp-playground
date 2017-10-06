#include <iostream>

#include "enum-class-iteration.h"

void
enums::ExamplesOfEnumClassIteration() {
  using namespace enums;
  std::cout
    << "all_defined_planets.size() = " << all_defined_planets.size() << "\n"
    << "count_defined<Planet>() = " << count_defined<Planet>() << std::endl;
  for (const auto planet : all_defined_planets)
    for (const auto opposite : all_defined_opposites)
      std::cout << "planet as size_t: " << static_cast<size_t>(planet)
                << ", opposite as size_t: " << static_cast<size_t>(opposite)
                << std::endl;
}
