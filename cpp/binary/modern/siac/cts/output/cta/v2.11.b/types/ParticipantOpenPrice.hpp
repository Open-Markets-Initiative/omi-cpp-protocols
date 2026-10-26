#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Participant first qualifying price paid during the trading day. Has implied 6 decimal places
struct ParticipantOpenPrice {

    static constexpr const char* name = "Participant Open Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr ParticipantOpenPrice()
     : value{ 0 } {}

    // constructor for ParticipantOpenPrice field
    constexpr explicit ParticipantOpenPrice(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of ParticipantOpenPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of ParticipantOpenPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
