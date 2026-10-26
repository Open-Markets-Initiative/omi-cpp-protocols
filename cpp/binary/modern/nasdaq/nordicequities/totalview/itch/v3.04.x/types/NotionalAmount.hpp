#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Notional amount if specified
struct NotionalAmount {

    static constexpr const char* name = "Notional Amount";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 5;
    static constexpr double denominator = 100000;
    using type = std::uint64_t;

    // default constructor
    constexpr NotionalAmount()
     : value{ 0 } {}

    // constructor for NotionalAmount field
    constexpr explicit NotionalAmount(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of NotionalAmount field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of NotionalAmount field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
