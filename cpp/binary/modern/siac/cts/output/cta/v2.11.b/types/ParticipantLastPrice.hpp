#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Participant last price. Has implied 6 decimal places
struct ParticipantLastPrice {

    static constexpr const char* name = "Participant Last Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr ParticipantLastPrice()
     : value{ 0 } {}

    // constructor for ParticipantLastPrice field
    constexpr explicit ParticipantLastPrice(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of ParticipantLastPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of ParticipantLastPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
