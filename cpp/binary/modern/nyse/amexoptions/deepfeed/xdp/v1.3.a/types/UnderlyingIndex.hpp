#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// The unique ID of the symbol in the Series Index message
struct UnderlyingIndex {

    static constexpr const char* name = "Underlying Index";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr UnderlyingIndex()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UnderlyingIndex(const std::uint32_t value)
     : value{ value } {}

    // get value of UnderlyingIndex field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
