#pragma once

#include <cstddef>

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {


// SecurityTradingStatus
struct SecurityTradingStatus {

    static constexpr auto name = "Security Trading Status";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SecurityTradingStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityTradingStatus(const char &value)
     : value{ value } {}

    // get value of SecurityTradingStatus field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
