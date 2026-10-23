#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cme::mdp3::v8 {


// Unit of measure for the products' original contract size. This will be populated for all products listed on CME Globex
struct UnitOfMeasure {

    static constexpr auto name = "Unit Of Measure";
    static constexpr std::size_t size = 30;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr UnitOfMeasure()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UnitOfMeasure(const type &value)
     : value{ value } {}

    // get value of UnitOfMeasure field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field
    [[nodiscard]] std::size_t length() const {
        std::size_t index = 0;
        for (; index < size; ++index) {
            if (value[index] == '\0') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
