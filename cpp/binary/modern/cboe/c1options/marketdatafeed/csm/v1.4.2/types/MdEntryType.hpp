// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/MdEntryType.hpp
#pragma once

#include <cstddef>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {


// Side of book for this entry.
struct MdEntryType {

    static constexpr auto name = "Md Entry Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MdEntryType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdEntryType(const char &value)
     : value{ value } {}

    // get value of MdEntryType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
