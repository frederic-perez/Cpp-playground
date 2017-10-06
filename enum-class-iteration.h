#pragma once

#include <array>

namespace enums {

template <class T>
constexpr
size_t
min() {
	return static_cast<size_t>(T::min);
}

template <class T>
constexpr
size_t
max() {
	return static_cast<size_t>(T::max);
}

template <class T>
constexpr
size_t
count_defined() { // Note: This works for consecutive enum values; if not > Specialize!
	return max<T>() - min<T>() + 1;
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
  min = Mercury,
  max = Neptune,
  undefined
};

enum class Opposite : uint8_t {
  yin,
  yang,
  min = yin,
  max = yang,
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
static_assert(all_defined_planets.front() == Planet::min, "static_assert failed: Bad array--check min");
static_assert(all_defined_planets.back() == Planet::max, "static_assert failed: Bad array--check max");

constexpr std::array<Opposite, count_defined<Opposite>()>
  all_defined_opposites{{ Opposite::yin, Opposite::yang }};
static_assert(all_defined_opposites.front() == Opposite::min, "static_assert failed: Bad array--check min");
static_assert(all_defined_opposites.back() == Opposite::max, "static_assert failed: Bad array--check max");

void ExamplesOfEnumClassIteration();

} // namespace enums
