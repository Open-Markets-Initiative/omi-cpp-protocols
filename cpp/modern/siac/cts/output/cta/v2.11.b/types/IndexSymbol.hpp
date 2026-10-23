#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace siac::cts::output::cta::v2_11_b {


// Contains the Index symbol. Left justified, space-filled
struct IndexSymbol {

    static constexpr auto name = "Index Symbol";
    static constexpr std::size_t size = 11;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr IndexSymbol()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IndexSymbol(const type &value)
     : value{ value } {}

    // get value of IndexSymbol field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field
    [[nodiscard]] std::size_t length() const {
        std::size_t index = 0;
        for (; index < size; ++index) {
            if (value[index] == ' ') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
