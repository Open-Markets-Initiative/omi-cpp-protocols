#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Venue from which market data is received for the instrument.
struct SourceVenue {

    static constexpr const char* name = "Source Venue";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr SourceVenue()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SourceVenue(const std::uint16_t value)
     : value{ value } {}

    // get value of SourceVenue field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
