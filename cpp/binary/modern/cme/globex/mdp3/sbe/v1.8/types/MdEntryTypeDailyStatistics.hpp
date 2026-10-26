#pragma once

#include <cstddef>

namespace cme::mdp3::v8 {


// Market Data entry type
struct MdEntryTypeDailyStatistics {

    static constexpr auto name = "Md Entry Type Daily Statistics";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MdEntryTypeDailyStatistics()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdEntryTypeDailyStatistics(const char &value)
     : value{ value } {}

    // get value of MdEntryTypeDailyStatistics field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
