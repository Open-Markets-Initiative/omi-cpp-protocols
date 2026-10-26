#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {


// Source of the Clean Price
struct MdStreamId {

    static constexpr auto name = "Md Stream Id";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 255;

    // default constructor
    constexpr MdStreamId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdStreamId(const std::uint8_t &value)
     : value{ value } {}

    // get value of MdStreamId field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
