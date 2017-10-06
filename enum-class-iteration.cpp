#include <iostream>

#include "enum-class-iteration.h"

void
tools::ExamplesOfEnumClassIteration() {
  size_t number_of_combinations = 0;
  std::cout << "tools::all_planets.size() = "
            << tools::all_planets.size() << "\n"
            << "tools::count<tools::Planet>() = "
            << tools::count<tools::Planet>() << std::endl;
  for (auto planet : tools::all_planets)
    for (auto opposite : tools::all_opposites) {
      std::cout << "planet as size_t: " << static_cast<size_t>(planet)
                << ", opposite as size_t: " << static_cast<size_t>(opposite)
                << std::endl;
      ++number_of_combinations;
    }
  std::cout << "number_of_combinations = " << number_of_combinations
            << std::endl;
}
