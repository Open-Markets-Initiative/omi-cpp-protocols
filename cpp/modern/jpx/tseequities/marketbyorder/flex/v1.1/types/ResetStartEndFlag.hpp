#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {


// When TSE needs to reset all distributed data, this indicates the start or end of the process
struct ResetStartEndFlag {

    static constexpr auto name = "Reset Start End Flag";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr ResetStartEndFlag()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ResetStartEndFlag(const std::uint8_t &value)
     : value{ value } {}

    // get value of ResetStartEndFlag field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
