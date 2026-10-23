#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g {

// Unique identifier for this Cross Trade.
struct CrossId {

    static constexpr const char* name = "Cross Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr CrossId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CrossId(const std::uint32_t value)
     : value{ value } {}

    // get value of CrossId field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
