#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Leg Security ID
struct LegSecurityId {

    static constexpr const char* name = "Leg Security Id";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr LegSecurityId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegSecurityId(const std::int32_t value)
     : value{ value } {}

    // get value of LegSecurityId field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
