#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// Number of legs in complex symbol. 2 - 12
struct NoOfLegs {

    static constexpr const char* name = "No Of Legs";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr NoOfLegs()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NoOfLegs(const std::uint16_t value)
     : value{ value } {}

    // get value of NoOfLegs field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
