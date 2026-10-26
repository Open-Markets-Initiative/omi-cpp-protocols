#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {


// mDUpdateAction
struct MdUpdateAction {

    static constexpr auto name = "Md Update Action";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr MdUpdateAction()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdUpdateAction(const std::uint8_t &value)
     : value{ value } {}

    // get value of MdUpdateAction field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
