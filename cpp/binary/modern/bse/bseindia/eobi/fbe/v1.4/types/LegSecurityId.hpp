#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {

// Instrument identifier of the leg security.
struct LegSecurityId {

    static constexpr const char* name = "Leg Security Id";
    static constexpr std::size_t size =  8;
    using type = std::int64_t;

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
