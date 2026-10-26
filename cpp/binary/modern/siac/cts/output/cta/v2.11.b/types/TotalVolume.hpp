#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Contains Total Volume of shares traded in a security either on a Consolidated or an individual Participant basis at the time it is disseminated
struct TotalVolume {

    static constexpr const char* name = "Total Volume";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr TotalVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TotalVolume(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of TotalVolume field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
