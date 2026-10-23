#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v13_0 {

// 
struct LegSecurityId {

    static constexpr const char* name = "Leg Security Id";
    static constexpr std::size_t size =  8;
    using type = std::int64_t;
static const type no_value = 0x8000000000000000;
static const type maximum_value = 9223372036854775807;
static const type minimum_value = -9223372036854775807;

    // default constructor
    constexpr LegSecurityId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegSecurityId(const std::int64_t value)
     : value{ value } {}

    // get value of LegSecurityId field
    [[nodiscard]] std::int64_t get() const {
        return value;
    }

  protected:
    std::int64_t value;
};
}
