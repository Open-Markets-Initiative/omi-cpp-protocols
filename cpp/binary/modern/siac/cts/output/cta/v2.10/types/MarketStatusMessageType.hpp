#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_10 {


// Market Status message type
struct MarketStatusMessageType {

    static constexpr auto name = "Market Status Message Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MarketStatusMessageType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketStatusMessageType(const char &value)
     : value{ value } {}

    // get value of MarketStatusMessageType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
