#pragma once

#include <cstddef>

namespace siac::opra::output::obi::v6_2 {


// Short Equity and Index Quote Message Type
struct ShortEquityAndIndexQuoteMessageType {

    static constexpr auto name = "Short Equity And Index Quote Message Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ShortEquityAndIndexQuoteMessageType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ShortEquityAndIndexQuoteMessageType(const char &value)
     : value{ value } {}

    // get value of ShortEquityAndIndexQuoteMessageType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
