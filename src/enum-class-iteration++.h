#ifndef CPP_PLAYGROUND_ENUM_CLASS_ITERATION_H
#define CPP_PLAYGROUND_ENUM_CLASS_ITERATION_H

#include <array>
#include <string>
#include <type_traits> // std::underlying_type

namespace enums {

// From https://stackoverflow.com/questions/14589417/can-an-enum-class-be-converted-to-the-underlying-type
//
// as_integral -- begin
//
template <typename E>
constexpr auto
as_integral(E e) -> typename std::underlying_type<E>::type
{
  return static_cast<typename std::underlying_type<E>::type>(e);
}
//
// as integral -- end

// From https://stackoverflow.com/questions/26936640/how-to-implement-is-enum-class-type-trait
//
// is_enum_class -- begin
//
template <typename T, typename V = void>
struct test : std::false_type {};

template <typename T>
struct test<T, decltype((void)+T{})> : std::true_type {};

template <typename T>
using is_enum_class = std::integral_constant<bool, !test<T>::value && std::is_enum<T>::value>;
//
// is_enum_class -- end

template <class T>
constexpr auto
count_defined()
-> size_t
{
  // Note: This works for
  // 1. consecutive enum values, starting with "zero"; if not > Specialize, and
  // 2. `undefined` must be the last value of the enum class
  static_assert(is_enum_class<T>::value, "static_assert failed: Bad type--T should be an enum class");
  return static_cast<size_t>(T::undefined);
}

enum class Planet : uint8_t { Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptune, undefined };
auto as_string(Planet) -> std::string;
auto as_planet(const std::string&) -> Planet;

constexpr std::array<Planet, count_defined<Planet>()> all_defined_planets{{Planet::Mercury,
                                                                           Planet::Venus,
                                                                           Planet::Earth,
                                                                           Planet::Mars,
                                                                           Planet::Jupiter,
                                                                           Planet::Saturn,
                                                                           Planet::Uranus,
                                                                           Planet::Neptune}};
static_assert(
  all_defined_planets.back() != static_cast<Planet>(0),
  "static_assert failed: Bad array--check contents to satisfy correct size");

enum class Opposite : uint8_t { yin, yang, undefined };
auto as_string(Opposite) -> std::string;
auto as_opposite(const std::string&) -> Opposite;

constexpr std::array<Opposite, count_defined<Opposite>()> all_defined_opposites{{Opposite::yin, Opposite::yang}};
static_assert(
  all_defined_opposites.back() != static_cast<Opposite>(0),
  "static_assert failed: Bad array--check contents to satisfy correct size");

void ExamplesOfEnumClassAsIntegral();
void ExamplesOfEnumClassIteration();

} // namespace enums

#endif // CPP_PLAYGROUND_ENUM_CLASS_ITERATION_H
