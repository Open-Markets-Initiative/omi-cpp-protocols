#pragma once

#include <cstddef>

namespace jnx::jnxequities::pts::ouch::v1_11 {


// Cash margin type of order
struct CashMarginType {

    static constexpr auto name = "Cash Margin Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr CashMarginType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CashMarginType(const char &value)
     : value{ value } {}

    // get value of CashMarginType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
