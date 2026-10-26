#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Underlying Instrument GUID. Collateral security identifier in REF Data API services
struct UnderlyingInstrumentGuid {

    static constexpr const char* name = "Underlying Instrument Guid";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr UnderlyingInstrumentGuid()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UnderlyingInstrumentGuid(const std::uint64_t value)
     : value{ value } {}

    // get value of UnderlyingInstrumentGuid field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
