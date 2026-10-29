#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {


// refMsgType
struct RefMsgType {

    static constexpr auto name = "Ref Msg Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr RefMsgType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RefMsgType(const std::uint8_t &value)
     : value{ value } {}

    // get value of RefMsgType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
