#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Tracks the integral relationship of the ETP to the underlying index
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
