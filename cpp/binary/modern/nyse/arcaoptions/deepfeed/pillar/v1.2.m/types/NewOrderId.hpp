#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// The new Order ID of the replacement order
struct NewOrderId {

    static constexpr const char* name = "New Order Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr NewOrderId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NewOrderId(const std::uint64_t value)
     : value{ value } {}

    // get value of NewOrderId field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
