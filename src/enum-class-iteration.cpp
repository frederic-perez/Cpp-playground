#include <cassert> // TODO: Use Boost instead of the good old <cassert>
#include <iostream>

#include "enum-class-iteration.h"

namespace enums {

#undef FPCX_TRY_NOT_ENUM_CLASS_AND_INT_20171009
#if defined(FPCX_TRY_NOT_ENUM_CLASS_AND_INT_20171009)
enum NotEnumClass { foo, bar, undefined };
static constexpr std::array<const char*, count_defined<NotEnumClass>()>
  text_not_enum_class{{ "foo", "bar" }};
  // static_assert > compilation error (in count_defined<NotEnumClass>())

const size_t num_defined_in_int = count_defined<int>(); // ditto
#endif

//
// Planet
//
  
static constexpr std::array<const char*, count_defined<Planet>()>
  text_planet{{
    "Mercury",
    "Venus",
    "Earth",
    "Mars",
    "Jupiter",
    "Saturn",
    "Uranus",
    "Neptune"
}};
static_assert(text_planet.back() != nullptr, "Bad array--check commas!");

std::string as_string(Planet input) {
  return
    input == decltype(input)::undefined ?
    "undefined" :
    text_planet.at(static_cast<size_t>(input));
}

Planet as_planet(const std::string& enum_value_str) {
  using result_type = Planet;
  for (size_t i = 0; i < text_planet.size(); ++i)
    if (text_planet[i] == enum_value_str)
      return static_cast<result_type>(i);
  return result_type::undefined;
}

//
// Opposite
//
  
static constexpr std::array<const char*, count_defined<Opposite>()>
  text_opposite{{
    "yin",
    "yang"
  }};
static_assert(text_opposite.back() != nullptr, "Bad array--check commas!");

std::string as_string(Opposite input) {
return
  input == decltype(input)::undefined ?
  "undefined" :
  text_opposite.at(static_cast<size_t>(input));
}

Opposite as_opposite(const std::string& enum_value_str) {
  using result_type = Opposite;
  for (size_t i = 0; i < text_opposite.size(); ++i)
    if (text_opposite[i] == enum_value_str)
      return static_cast<result_type>(i);
  return result_type::undefined;
}

} // namespace enum

void
enums::ExamplesOfEnumClassIteration() {
  using namespace enums;
  std::cout
    << "all_defined_planets.size() = " << all_defined_planets.size() << "\n"
    << "count_defined<Planet>() = " << count_defined<Planet>() << std::endl;
  for (const auto planet : all_defined_planets)
    for (const auto opposite : all_defined_opposites) {
      const std::string planet_str = as_string(planet);
      const std::string opposite_str = as_string(opposite);
      assert(planet == as_planet(planet_str)); // TODO: Use Boost here
      assert(opposite == as_opposite(opposite_str)); // TODO: Use Boost here
      std::cout << "planet as string: " << planet_str
                << ", opposite as string: " << opposite_str
                << std::endl;
    }
}
