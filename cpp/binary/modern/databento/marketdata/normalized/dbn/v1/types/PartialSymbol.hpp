#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace databento::marketdata::normalized::dbn::v1 {


// One of the symbols that did not resolve for at least one day in the query time range
struct PartialSymbol {

    static constexpr auto name = "Partial Symbol";
    static constexpr std::size_t size = 22;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr PartialSymbol()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PartialSymbol(const type &value)
     : value{ value } {}

    // get value of PartialSymbol field
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
