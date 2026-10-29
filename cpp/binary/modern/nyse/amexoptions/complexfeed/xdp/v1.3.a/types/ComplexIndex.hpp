#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

// The unique ID of the symbol in the Complex Index msg
struct ComplexIndex {

    static constexpr const char* name = "Complex Index";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ComplexIndex()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ComplexIndex(const std::uint32_t value)
     : value{ value } {}

    // get value of ComplexIndex field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
