#pragma once

#include <cstddef>

namespace iex::iexequities::tops::snap::v1_6 {


// Trading status identifier
struct TradingStatus {

    static constexpr auto name = "Trading Status";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr TradingStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradingStatus(const char &value)
     : value{ value } {}

    // get value of TradingStatus field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
