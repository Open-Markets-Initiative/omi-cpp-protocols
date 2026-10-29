#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_10 {

// Contains Total Volume of shares traded in a security either on a Consolidated or an individual Participant basis at the time it is disseminated
struct TotalVolumeShort {

    static constexpr const char* name = "Total Volume Short";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TotalVolumeShort()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TotalVolumeShort(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of TotalVolumeShort field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
