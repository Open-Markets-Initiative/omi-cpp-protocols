#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::millennium::level2::mitch::v11_9 {


// The type of the Cross/BTF Order.
struct CrossType {

    static constexpr auto name = "Cross Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 0;

    // default constructor
    constexpr CrossType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CrossType(const std::uint8_t &value)
     : value{ value } {}

    // get value of CrossType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
