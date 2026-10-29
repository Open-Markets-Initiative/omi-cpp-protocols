#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// Used With Trade Corrections To Reference Previously Reported Executions
struct OrigTradeNumber {

    static constexpr const char* name = "Orig Trade Number";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0;

    // default constructor
    constexpr OrigTradeNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OrigTradeNumber(const std::uint32_t value)
     : value{ value } {}

    // get value of OrigTradeNumber field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
