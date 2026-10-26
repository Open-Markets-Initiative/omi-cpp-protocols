#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Unique Instrument ID as qualified by the exchange per tag 305-UnderlyingSecurityIDSource
struct UnderlyingSecurityId {

    static constexpr const char* name = "Underlying Security Id";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr UnderlyingSecurityId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UnderlyingSecurityId(const std::int32_t value)
     : value{ value } {}

    // get value of UnderlyingSecurityId field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
