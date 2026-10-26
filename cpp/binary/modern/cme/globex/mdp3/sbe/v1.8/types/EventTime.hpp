#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v8 {


// Date and Time of instument Activation or Expiration event sent as number of nanoseconds since Unix epoch
struct EventTime {

    static constexpr auto name = "Event Time";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;

    // default constructor
    constexpr EventTime()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit EventTime(const std::uint64_t &value)
     : value{ value } {}

    // get value of EventTime field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
