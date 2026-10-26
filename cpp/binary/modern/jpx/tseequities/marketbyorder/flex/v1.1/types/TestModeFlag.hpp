#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {


// Indicates production or test
struct TestModeFlag {

    static constexpr auto name = "Test Mode Flag";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr TestModeFlag()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TestModeFlag(const std::uint8_t &value)
     : value{ value } {}

    // get value of TestModeFlag field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
