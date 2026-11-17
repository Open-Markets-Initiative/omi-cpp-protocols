// Databento.MarketData.Normalized.Dbn.v3: types/Sequence.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {

// The message sequence number assigned at the venue
struct Sequence {

    static constexpr const char* name = "Sequence";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Sequence()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Sequence(const std::uint32_t value)
     : value{ value } {}

    // get value of Sequence field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
