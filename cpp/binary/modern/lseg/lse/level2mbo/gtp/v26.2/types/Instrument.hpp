#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// GTP Instrument identifier.
struct Instrument {

    static constexpr const char* name = "Instrument";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr Instrument()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Instrument(const std::uint64_t value)
     : value{ value } {}

    // get value of Instrument field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
