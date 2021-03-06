#include <cassert> // TODO: Use Boost instead of the good old <cassert>
#include <iostream>

#include <boost/assert.hpp>

#include "enum-class-iteration+.h"

namespace enums {

#undef FPCX_TRY_NOT_ENUM_CLASS_AND_INT_20171009
#if defined(FPCX_TRY_NOT_ENUM_CLASS_AND_INT_20171009)
enum NotEnumClass { foo, bar, undefined };
static constexpr std::array<const char*, count_defined<NotEnumClass>()> text_not_enum_class{{"foo", "bar"}};
// static_assert > compilation error (in count_defined<NotEnumClass>())

const size_t num_defined_in_int = count_defined<int>(); // ditto
#endif

//
// Planet
//

static constexpr std::array text_planet{
  "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"};
static_assert(text_planet.size() == count_defined<Planet>(), "Bad array: wrong size");

auto
as_string(Planet input)
-> std::string
{
  return input == decltype(input)::undefined ? "undefined" : text_planet.at(static_cast<size_t>(input));
}

constexpr auto
as_planet(const std::string& enum_value_str)
-> Planet
{
  using result_type = Planet;
  for (size_t i = 0; i < text_planet.size(); ++i) {
    if (text_planet[i] == enum_value_str) {
      return static_cast<result_type>(i);
    }
  }
  return result_type::undefined;
}

//
// Opposite
//

static constexpr std::array text_opposite{"yin", "yang"};
static_assert(text_opposite.size() == count_defined<Opposite>(), "Bad array: wrong size");

auto
as_string(Opposite input)
-> std::string
{
  return input == decltype(input)::undefined ? "undefined" : text_opposite.at(static_cast<size_t>(input));
}

constexpr auto
as_opposite(const std::string& enum_value_str)
-> Opposite
{
  using result_type = Opposite;
  for (size_t i = 0; i < text_opposite.size(); ++i) {
    if (text_opposite[i] == enum_value_str) {
      return static_cast<result_type>(i);
    }
  }
  return result_type::undefined;
}

} // namespace enums

#if defined(_WIN64)
using uint = unsigned int;
#endif

void
enums::ExamplesOfEnumClassAsIntegral()
{
  auto planet = Planet::Earth;
  std::cout << "planet = Planet::Earth as string: " << as_string(planet)
            << "; static_cast<uint>(as_integral(planet)): " << static_cast<uint>(as_integral(planet)) << std::endl;
  planet = Planet::undefined;
  std::cout << "planet = Planet::undefined as string: " << as_string(planet)
            << "; static_cast<uint>(as_integral(planet)): " << static_cast<uint>(as_integral(planet)) << '\n'
            << std::endl;
}

void
enums::ExamplesOfEnumClassIteration()
{
  using namespace std::string_literals;

  std::cout << "all_defined_planets.size() = " << all_defined_planets.size() << "\n"
            << "count_defined<Planet>() = " << count_defined<Planet>() << std::endl;
  for (const auto planet : all_defined_planets) {
    const std::string planet_str = as_string(planet);
    if (planet != as_planet(planet_str))
      throw "Problem using planet"s;
    std::cout << "planet as string: " << planet_str << std::endl;
  }
  std::cout << std::endl;

  std::cout << "all_defined_opposites.size() = " << all_defined_opposites.size() << "\n"
    << "count_defined<Opposite>() = " << count_defined<Opposite>() << std::endl;
  for (const auto opposite : all_defined_opposites) {
    const std::string opposite_str = as_string(opposite);
    if (opposite != as_opposite(opposite_str))
      throw "Problem using opposite"s;
    std::cout << "opposite as string: " << opposite_str << std::endl;
  }
}
