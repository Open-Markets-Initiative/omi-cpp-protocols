// Databento.MarketData.Normalized.Dbn.v3: types/UnitOfMeasure.hpp
#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace databento::marketdata::normalized::dbn::v3 {


// The unit of measure
struct UnitOfMeasure {

    static constexpr auto name = "Unit Of Measure";
    static constexpr std::size_t size = 31;

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

    // runtime length of field: its characters up to the fill after the last of them, so a space
    // or a null inside the text is kept
    [[nodiscard]] std::size_t length() const {
        std::size_t index = size;
        for (; index > 0; --index) {
            if (value[index - 1] != '\0') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
