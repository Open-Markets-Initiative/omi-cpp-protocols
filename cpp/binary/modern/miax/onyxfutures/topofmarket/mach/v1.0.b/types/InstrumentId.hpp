#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// Unique ID assigned by MIAX Futures Onyx
struct InstrumentId {

    static constexpr const char* name = "Instrument Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr InstrumentId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit InstrumentId(const std::uint32_t value)
     : value{ value } {}

    // get value of InstrumentId field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
