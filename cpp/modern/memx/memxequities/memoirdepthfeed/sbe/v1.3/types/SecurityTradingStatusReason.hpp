#pragma once

#include <cstddef>

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {


// SecurityTradingStatusReason
struct SecurityTradingStatusReason {

    static constexpr auto name = "Security Trading Status Reason";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SecurityTradingStatusReason()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityTradingStatusReason(const char &value)
     : value{ value } {}

    // get value of SecurityTradingStatusReason field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
