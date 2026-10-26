#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v15_0 {


// Copy of DSCP from IP protocol header
struct Dscp {

    static constexpr auto name = "DSCP";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 0xFF;
static const type maximum_value = 254;
static const type minimum_value = 0;

    // default constructor
    constexpr Dscp()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Dscp(const std::uint8_t &value)
     : value{ value } {}

    // get value of Dscp field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
