#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// secondaryOrderID
struct SecondaryOrderId {

    static constexpr const char* name = "Secondary Order Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr SecondaryOrderId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecondaryOrderId(const std::uint64_t value)
     : value{ value } {}

    // get value of SecondaryOrderId field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
