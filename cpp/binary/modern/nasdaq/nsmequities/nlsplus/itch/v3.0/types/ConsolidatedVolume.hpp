#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Reflects the volume for the Issue Symbol as reported on the consolidated market data feed at the time the trade message was generated
struct ConsolidatedVolume {

    static constexpr const char* name = "Consolidated Volume";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr ConsolidatedVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ConsolidatedVolume(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of ConsolidatedVolume field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
