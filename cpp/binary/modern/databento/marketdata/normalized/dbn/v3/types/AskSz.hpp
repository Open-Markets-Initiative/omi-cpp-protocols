#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {

// The ask size
struct AskSz {

    static constexpr const char* name = "Ask Sz";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr AskSz()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AskSz(const std::uint32_t value)
     : value{ value } {}

    // get value of AskSz field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
