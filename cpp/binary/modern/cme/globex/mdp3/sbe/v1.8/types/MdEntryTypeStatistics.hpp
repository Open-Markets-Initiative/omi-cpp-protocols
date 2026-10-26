#pragma once

#include <cstddef>

namespace cme::mdp3::v8 {


// Market Data entry type
struct MdEntryTypeStatistics {

    static constexpr auto name = "Md Entry Type Statistics";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MdEntryTypeStatistics()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdEntryTypeStatistics(const char &value)
     : value{ value } {}

    // get value of MdEntryTypeStatistics field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
