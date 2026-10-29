#pragma once

#include <cstddef>

namespace nasdaq::psxequities::totalview::itch::v5_0 {


// Indicates Listing market or listing market tier for the issue
struct MarketCategory {

    static constexpr auto name = "Market Category";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MarketCategory()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketCategory(const char &value)
     : value{ value } {}

    // get value of MarketCategory field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
