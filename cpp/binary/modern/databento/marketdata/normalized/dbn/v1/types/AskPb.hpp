#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {

// The publisher ID indicating the venue containing the best ask
struct AskPb {

    static constexpr const char* name = "Ask Pb";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr AskPb()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AskPb(const std::uint16_t value)
     : value{ value } {}

    // get value of AskPb field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
