#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Broken date Instrument Globex Security ID
struct BrokenDateSecurityId {

    static constexpr const char* name = "Broken Date Security Id";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr BrokenDateSecurityId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BrokenDateSecurityId(const std::int32_t value)
     : value{ value } {}

    // get value of BrokenDateSecurityId field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
