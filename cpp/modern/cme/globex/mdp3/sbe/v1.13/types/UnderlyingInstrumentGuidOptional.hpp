#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Underlying GUID. For Repo specials populated with individual instrument GUID of the underlying security
struct UnderlyingInstrumentGuidOptional {

    static constexpr const char* name = "Underlying Instrument Guid Optional";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;
static const type no_value = 18446744073709551615ULL;

    // default constructor
    constexpr UnderlyingInstrumentGuidOptional()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UnderlyingInstrumentGuidOptional(const std::uint64_t value)
     : value{ value } {}

    // get value of UnderlyingInstrumentGuidOptional field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
