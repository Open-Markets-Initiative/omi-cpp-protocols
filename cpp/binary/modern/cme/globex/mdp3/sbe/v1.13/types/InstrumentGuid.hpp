#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// External unique instrument ID
struct InstrumentGuid {

    static constexpr const char* name = "Instrument Guid";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;
static const type no_value = 18446744073709551615ULL;

    // default constructor
    constexpr InstrumentGuid()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit InstrumentGuid(const std::uint64_t value)
     : value{ value } {}

    // get value of InstrumentGuid field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
