#pragma once

#include <cstddef>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {


// ‘B’ = Bid ‘A’ = Offer (Ask) ‘ ’ (blank) = not set (hidden)
struct Side {

    static constexpr auto name = "Side";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Side()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Side(const char &value)
     : value{ value } {}

    // get value of Side field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
