#pragma once

#include <array>

namespace enums {

template <class T>
constexpr
size_t
count_defined() { 
  // Note: This works for 
  // 1. consecutive enum values, starting with "zero"; if not > Specialize, and
  // 2. `undefined` must be the last value of the enum class
	return static_cast<size_t>(T::undefined);
}

enum class Planet : uint8_t {
  Mercury,
  Venus,
  Earth,
  Mars,
  Jupiter,
  Saturn,
  Uranus,
  Neptune,
  undefined
};

enum class Opposite : uint8_t {
  yin,
  yang,
  undefined
};

constexpr std::array<Planet, count_defined<Planet>()>
  all_defined_planets{{
    Planet::Mercury,
    Planet::Venus,
    Planet::Earth,
    Planet::Mars,
    Planet::Jupiter,
    Planet::Saturn,
    Planet::Uranus,
    Planet::Neptune
  }};
static_assert(all_defined_planets.back() != static_cast<Planet>(0), "static_assert failed: Bad array--check contents to satisfy correct size");

constexpr std::array<Opposite, count_defined<Opposite>()>
  all_defined_opposites{{
    Opposite::yin,
    Opposite::yang
  }};
static_assert(all_defined_opposites.back() != static_cast<Opposite>(0), "static_assert failed: Bad array--check contents to satisfy correct size");

void ExamplesOfEnumClassIteration();

} // namespace enums
