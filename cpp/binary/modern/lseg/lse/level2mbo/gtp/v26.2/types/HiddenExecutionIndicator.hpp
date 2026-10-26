#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::lse::level2mbo::gtp::v26_2 {


// For London Stock Exchange, during continuous trading and CPX session, 1[2] will be sent for execution of visible[hidden] quantities. For London Stock Exchange Auction Trades, 0 will be sent indicating 'Not Applicable' (N/A).
struct HiddenExecutionIndicator {

    static constexpr auto name = "Hidden Execution Indicator";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr HiddenExecutionIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit HiddenExecutionIndicator(const std::uint8_t &value)
     : value{ value } {}

    // get value of HiddenExecutionIndicator field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
