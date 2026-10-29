#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {


// Denotes the Nasdaq market system that generated the original trade report message
struct MarketCenter {

    static constexpr auto name = "Market Center";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MarketCenter()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketCenter(const char &value)
     : value{ value } {}

    // get value of MarketCenter field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
