#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// eventID
struct EventId {

    static constexpr const char* name = "Event Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr EventId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit EventId(const std::uint32_t value)
     : value{ value } {}

    // get value of EventId field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
