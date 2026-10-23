#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Represents the last price for that security either on a Consolidated or an individual Participant basis at the time it is disseminated. Has implied 6 decimal places
struct LastPrice {

    static constexpr const char* name = "Last Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr LastPrice()
     : value{ 0 } {}

    // constructor for LastPrice field
    constexpr explicit LastPrice(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of LastPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of LastPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
