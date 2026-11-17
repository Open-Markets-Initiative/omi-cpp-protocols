// Siac.Cts.Output.Cta.v2.11.b: types/MarketStatusMessageType.hpp
#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// Identifies the type of Market Status message
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
