#pragma once

#include <cstddef>
#include <cstdint>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {


// Length in bytes of the Tag Data including the Message Type byte
struct TagLength {

    static constexpr auto name = "Tag Length";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr TagLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TagLength(const std::uint8_t &value)
     : value{ value } {}

    // get value of TagLength field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
