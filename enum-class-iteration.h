#pragma once

#include <array>

namespace tools {

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
count() { // Note: This works for consecutive enum values; if not > Specialize!
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
  max = Neptune
};

enum class Opposite : uint8_t {
  yin,
  yang,
  min = yin,
  max = yang  
};

//static 
constexpr std::array<Planet, count<Planet>()>
  all_planets{{
    Planet::Mercury,
    Planet::Venus,
    Planet::Earth,
    Planet::Mars,
    Planet::Jupiter,
    Planet::Saturn,
    Planet::Uranus,
    Planet::Neptune
  }};
static_assert(all_planets.front() == Planet::min, "static_assert failed: Bad array--check min");
static_assert(all_planets.back() == Planet::max, "static_assert failed: Bad array--check max");

//static 
constexpr std::array<Opposite, count<Opposite>()>
  all_opposites{{ Opposite::yin, Opposite::yang }};
static_assert(all_opposites.front() == Opposite::min, "static_assert failed: Bad array--check min");
static_assert(all_opposites.back() == Opposite::max, "static_assert failed: Bad array--check max");

void ExamplesOfEnumClassIteration();

} // namespace tools
