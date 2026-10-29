#pragma once

#include <cstddef>
#include <cstdint>

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// Number of messages in packet
struct Count {

    static constexpr const char* name = "Count";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr Count()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Count(const std::uint16_t value)
     : value{ value } {}

    // get value of Count field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
