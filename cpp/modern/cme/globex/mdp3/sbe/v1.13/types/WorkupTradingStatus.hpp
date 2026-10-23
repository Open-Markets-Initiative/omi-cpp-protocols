#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {


// Identifies the trading status applicable to the instrument
struct WorkupTradingStatus {

    static constexpr auto name = "Workup Trading Status";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr WorkupTradingStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit WorkupTradingStatus(const std::uint8_t &value)
     : value{ value } {}

    // get value of WorkupTradingStatus field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
