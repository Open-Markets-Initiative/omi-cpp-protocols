#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

// This field is only populated when securityStatus = A and this security is listed on this exchange
struct SsrTriggeringVolume {

    static constexpr const char* name = "Ssr Triggering Volume";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr SsrTriggeringVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SsrTriggeringVolume(const std::uint32_t value)
     : value{ value } {}

    // get value of SsrTriggeringVolume field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
