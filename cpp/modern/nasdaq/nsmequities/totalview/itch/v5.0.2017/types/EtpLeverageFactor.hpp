#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

// Tracks the integral relationship of the ETP to the underlying index. Example: If the underlying Index increases by a value of 1 and the ETP’s Leverage factor is 3, indicates the ETF will increase/decrease (see Inverse) by 3. Note: Leverage Factor of 1 indicates the ETP is NOT leveraged. This field is used for LULD Tier I price band calculation purposes.
struct EtpLeverageFactor {

    static constexpr const char* name = "Etp Leverage Factor";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr EtpLeverageFactor()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit EtpLeverageFactor(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of EtpLeverageFactor field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
