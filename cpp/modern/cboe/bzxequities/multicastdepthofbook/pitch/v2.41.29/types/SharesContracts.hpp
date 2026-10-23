#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29 {

// Cumulative number of shares/contracts executed during the auction or CMC match
struct SharesContracts {

    static constexpr const char* name = "Shares Contracts";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr SharesContracts()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SharesContracts(const std::uint32_t value)
     : value{ value } {}

    // get value of SharesContracts field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
