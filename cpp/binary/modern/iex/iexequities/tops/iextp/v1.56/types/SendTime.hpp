#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::tops::iextp::v1_56 {


// Send time of segment
struct SendTime {

    static constexpr auto name = "Send Time";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;

    // default constructor
    constexpr SendTime()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SendTime(const std::uint64_t &value)
     : value{ value } {}

    // get value of SendTime field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
