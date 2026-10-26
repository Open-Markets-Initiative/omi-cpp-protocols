#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g {

// Default value is 0. If securityStatus = G or I, then this field is the Indication High Price.
struct Price2 {

    static constexpr const char* name = "Price 2";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Price2()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Price2(const std::uint32_t value)
     : value{ value } {}

    // get value of Price2 field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
