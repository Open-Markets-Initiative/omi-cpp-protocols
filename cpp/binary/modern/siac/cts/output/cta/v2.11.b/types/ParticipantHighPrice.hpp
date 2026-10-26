#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Participant highest price paid during the trading day. Has implied 6 decimal places
struct ParticipantHighPrice {

    static constexpr const char* name = "Participant High Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr ParticipantHighPrice()
     : value{ 0 } {}

    // constructor for ParticipantHighPrice field
    constexpr explicit ParticipantHighPrice(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of ParticipantHighPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of ParticipantHighPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
