#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Related Instrument GUID
struct RelatedInstrumentGuid {

    static constexpr const char* name = "Related Instrument Guid";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;
static const type no_value = 18446744073709551615ULL;

    // default constructor
    constexpr RelatedInstrumentGuid()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RelatedInstrumentGuid(const std::uint64_t value)
     : value{ value } {}

    // get value of RelatedInstrumentGuid field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
