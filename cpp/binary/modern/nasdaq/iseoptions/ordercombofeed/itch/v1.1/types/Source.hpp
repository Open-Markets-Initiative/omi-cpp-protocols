#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {


// Identifies the source of the Strategy, valid for the trading day
struct Source {

    static constexpr auto name = "Source";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr Source()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Source(const std::uint8_t &value)
     : value{ value } {}

    // get value of Source field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
